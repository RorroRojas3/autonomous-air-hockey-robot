#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "ringbuf.h"
#include "uart_driver_mp.h"

unsigned int uart_rx_skipped;

typedef struct {
	tRingBufObject		in_buf;
	tRingBufObject		out_buf;
	unsigned int 		status;
	unsigned int		skipped_rx;
}UART_PORT;

UART_PORT	uart_ports[UART_N_PORTS];

volatile unsigned int uart_status_tx;
volatile unsigned int uart_status_rx;
unsigned char uart_escaped_buf;


static int uart_port_no_tx(void);
static void uart_port_init(void);


void uart_init_hw(unsigned int channel, unsigned long baud, int interrupt_mode)
{
	unsigned long base;
	unsigned long periph;

	unsigned long base_pin;
	unsigned long periph_pin;
	unsigned long pin_mask;
	unsigned long pin_tx;
	unsigned long pin_rx;
	unsigned long int_id;

	switch(channel)
	{
	case 0: // UART 0
		base = UART0_BASE;
		periph = SYSCTL_PERIPH_UART0;

		base_pin = GPIO_PORTA_BASE;
		periph_pin = SYSCTL_PERIPH_GPIOA;

		pin_mask = GPIO_PIN_0 | GPIO_PIN_1;
		pin_rx = GPIO_PA0_U0RX;
		pin_tx = GPIO_PA1_U0TX;

		int_id = INT_UART0;
		break;
    case 1: // UART 1
        //
		base = UART1_BASE;
		periph = SYSCTL_PERIPH_UART1;

		base_pin = GPIO_PORTB_BASE;
		periph_pin = SYSCTL_PERIPH_GPIOB;

		pin_mask = GPIO_PIN_0 | GPIO_PIN_1;
		pin_rx = GPIO_PB0_U1RX;
		pin_tx = GPIO_PB1_U1TX;

		int_id = INT_UART1;
        break;
     
	default:
		return;
	}

    /* Enable the peripherals used */
    MAP_SysCtlPeripheralEnable(periph);
    MAP_SysCtlPeripheralEnable(periph_pin);

    /* Set GPIO A0 and A1 as UART pins. */
    MAP_GPIOPinConfigure(pin_rx);
    MAP_GPIOPinConfigure(pin_tx);
    MAP_GPIOPinTypeUART(base_pin, pin_mask);

    /* Configure the UART for baud, 8-N-1 operation. */
    MAP_UARTConfigSetExpClk(base, MAP_SysCtlClockGet(), baud,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
            UART_CONFIG_PAR_NONE));

    // Enable FIFO
    MAP_UARTFIFOEnable(base);

    // Set the UART to interrupt whenever the TX FIFO is almost empty or
    // when TX FIFO is almost more than half full
    MAP_UARTFIFOLevelSet(base, UART_FIFO_TX1_8, UART_FIFO_RX6_8);

    // We are configured for buffered output so enable the master interrupt
    // for this UART and the receive interrupts.  We don't actually enable the
    // transmit interrupt in the UART itself until some data has been placed
    // in the transmit buffer.
    //
    MAP_UARTIntDisable(base, 0xFFFFFFFF);
    
    if (interrupt_mode == UART_INTERRUPT_MODE)
    {
        MAP_UARTIntEnable(base, UART_INT_RX | UART_INT_RT);
        MAP_IntEnable(int_id);
    }
    /* Enable UART */
    MAP_UARTEnable(base);
}

static
void uart_intr_init(void)
{
	// statically initialized
}

void uart_bare_init(void)
{
    uart_init_hw(0, UART_BAUD_RATE, UART_POLL_MODE);
}

void uart_bare_putchar(char c)
{
    MAP_UARTCharPut(UART0_BASE, (unsigned char) c);
}

void uart_init(void)
{
	// interrupt handler init
	uart_intr_init();

	// Software init
	uart_status_tx = UART_STATUS_UNINITED;
	uart_status_rx = UART_STATUS_UNINITED;
	uart_rx_skipped = 0;
	uart_escaped_buf = 0;
	uart_port_init();

	// Hardware init
	uart_init_hw(0, UART_BAUD_RATE, UART_INTERRUPT_MODE);
    
    /* try to connect */
    MAP_UARTCharPutNonBlocking(UART0_BASE, UART_CMD_SYNC);
    MAP_UARTCharPutNonBlocking(UART0_BASE, UART_CMD_SYNC);
}

// require uart_status_tx != uninited
static
void uart_fill_tx_fifo(unsigned long base)
{
	int i;
	unsigned char c;

	MAP_UARTIntDisable(base, UART_INT_TX);

	if ((uart_escaped_buf & UART_CMD_PORT) == UART_CMD_PORT  &&  MAP_UARTSpaceAvail(base))
	{
		// esc pending
		MAP_UARTCharPutNonBlocking(base, uart_escaped_buf);
		uart_escaped_buf = 0; // unset esc
	}

	for (i=0;i<UART_N_PORTS;++i)
	{
		if (uart_ports[i].status == PORT_STATUS_INITED)
		{
			while(MAP_UARTSpaceAvail(base) && ((uart_escaped_buf & UART_CMD_PORT) == UART_CMD_PORT || !RingBufEmpty(&(uart_ports[i].out_buf))))
			{

				if ((uart_escaped_buf & UART_CMD_PORT) == UART_CMD_PORT)
				{
					// esc pending
					MAP_UARTCharPutNonBlocking(base, uart_escaped_buf);
					uart_escaped_buf = 0; // unset esc
					continue;
				}

				if ((uart_status_tx & UART_STATUS_PORT_MASK) != i)
				{
					uart_status_tx = UART_CMD_PORT + i;
					MAP_UARTCharPutNonBlocking(base, uart_status_tx);
				}else
				{
					c = RingBufReadOne(&(uart_ports[i].out_buf));
					if ((c & UART_CMD_PORT) == UART_CMD_PORT)
					{
						// need esc
						MAP_UARTCharPutNonBlocking(base, UART_CMD_ESC);
						uart_escaped_buf = c; // set esc
					}else
					{
						MAP_UARTCharPutNonBlocking(base, c);
					}
				}
			}
		}
	}
    MAP_UARTIntEnable(base, UART_INT_TX);
}

// require uart_status_rx = [0xe0~0xe9 or 0xf0~0xf9]
static
void uart_fetch_rx_fifo(unsigned long base)
{
	int port;
	unsigned char c;
    while(MAP_UARTCharsAvail(base))
    {
		port = uart_status_rx & UART_STATUS_PORT_MASK;
		if (uart_ports[port].status == PORT_STATUS_INITED)
		{
			if ((uart_status_rx & UART_CMD_PORT) == 0xE0)  // previously esc set
	    	{
				RingBufWriteOne(&(uart_ports[port].in_buf), MAP_UARTCharGetNonBlocking(base));
				uart_status_rx |= ~UART_STATUS_ESC_MASK & 0xFF; // unset esc
	    	}else
	    	{
	    		c = MAP_UARTCharGetNonBlocking(base);
	    		if ((c & UART_CMD_PORT) != UART_CMD_PORT)
	    		{
	    			// normal char
	    			RingBufWriteOne(&(uart_ports[port].in_buf), c);
	    		}else
	    		{
	    			if ((c & UART_STATUS_PORT_MASK) == 0xF)
	    			{
	    				// got a 0xFF, set escape
	    				uart_status_rx &= UART_STATUS_ESC_MASK;
	    			}else if ((c & UART_STATUS_PORT_MASK) < UART_N_PORTS)
	    			{
	    				uart_status_rx = c;
	    			}
	    		}
	    	}
		}else
		{
			MAP_UARTCharGetNonBlocking(base); // skip char
		}
    }
}

static
void uart_general_intr(unsigned long base)
{
    unsigned long ulInts;
    unsigned char c;

    //
    // Get and clear the current interrupt source(s)
    //
    ulInts = MAP_UARTIntStatus(base, true);
    MAP_UARTIntClear(base, ulInts);

    //
    // Are we being interrupted because the TX FIFO has space available?
    //
    if(ulInts & UART_INT_TX)
    {
    	if ((uart_status_tx & UART_CMD_PORT) == UART_CMD_PORT)
    	{
			// Move as many bytes as we can into the transmit FIFO.
			uart_fill_tx_fifo(base);

			// If the tx buffer is empty, turn off the transmit interrupt.
			if(uart_port_no_tx())
			{
				MAP_UARTIntDisable(base, UART_INT_TX);
			}
    	}else
        {
    		// not possible
    		// if uart_status_tx == uninited, tx int would be disabled
    		MAP_UARTIntDisable(base, UART_INT_TX);
    	}
    }

    //
    // Are we being interrupted due to a received character?
    //
    if(ulInts & (UART_INT_RX | UART_INT_RT))
    {
    	if (uart_status_rx >= UART_CMD_PORT && uart_status_rx < UART_CMD_PORT+UART_N_PORTS ||
    			uart_status_rx >= (UART_STATUS_ESC_MASK & UART_CMD_PORT) &&
    			uart_status_rx < (UART_STATUS_ESC_MASK & UART_CMD_PORT)+UART_N_PORTS)
    	{
			//
			// Get all the available characters from the UART.
			//
			uart_fetch_rx_fifo(base);

			//
			// prevent further RX interrupt as the buffer is full
			//
			while(MAP_UARTIntStatus(base, true) & UART_INT_RX)
			{
				MAP_UARTCharGetNonBlocking(base);
				++uart_rx_skipped;
			}
    	}else if (uart_status_rx == UART_STATUS_INITED) {
    		c = MAP_UARTCharGetNonBlocking(base);
    		if ((c & UART_STATUS_PORT_MASK) < UART_N_PORTS)
    		{
    			uart_status_rx = c;
    		}
    	}else if (uart_status_rx == UART_STATUS_UNINITED) {
    		if (MAP_UARTCharGetNonBlocking(base) == UART_CMD_SYNC)
    		{
    			uart_status_rx = UART_STATUS_INITED;
    			uart_status_tx = UART_STATUS_INITED;
    		}else
    		{
    			MAP_UARTCharPutNonBlocking(base, UART_CMD_SYNC);
    		}
    	}
    }
}

void UART0IntHandler(void)
{
	uart_general_intr(UART0_BASE);
}

void uart_port_init(void)
{
	int i;
	for (i=0; i<UART_N_PORTS; ++i)
	{
		uart_ports[i].status = PORT_STATUS_UNINITED;
		uart_ports[i].skipped_rx = 0;
	}
}

int uart_port_open( unsigned int port,
					unsigned char* in_buf, unsigned int in_buf_size,
					unsigned char* out_buf, unsigned int out_buf_size)
{
	if (uart_ports[port].status == PORT_STATUS_UNINITED)
	{
		RingBufInit(&(uart_ports[port].in_buf), in_buf, in_buf_size);
		RingBufInit(&(uart_ports[port].out_buf), out_buf, out_buf_size);
		uart_ports[port].status = PORT_STATUS_INITED;
		return 1;
	}else
	{
		return 0;
	}
}

int uart_port_close(unsigned int port)
{
	if (uart_ports[port].status == PORT_STATUS_INITED)
	{
		uart_ports[port].status = PORT_STATUS_UNINITED;
		uart_ports[port].skipped_rx = 0;
		return 1;
	}else
	{
		return 0;
	}
}

int uart_port_read_one(unsigned int port, unsigned char *buf)
{
    tBoolean bIntsOff;
    int ret = 0;

	bIntsOff = MAP_IntMasterDisable();

	if (RingBufEmpty(&(uart_ports[port].in_buf)))
	{
		ret = 0;
	}else
	{
		*buf = RingBufReadOne(&(uart_ports[port].in_buf));
		ret = 1;
	}

    if(!bIntsOff)
    {
        MAP_IntMasterEnable();
    }
	return ret;
}

int uart_port_read_pending(unsigned int port)
{
    if  (uart_ports[port].status == PORT_STATUS_INITED)
    {
        return (int)RingBufUsed(&(uart_ports[port].in_buf));
    }else
    {
        return -1;
    }
}

int uart_port_write_one(unsigned int port, unsigned char *buf)
{
    tBoolean bIntsOff;
    int ret = 0;

	bIntsOff = MAP_IntMasterDisable();

	if (RingBufFull(&(uart_ports[port].out_buf)))
	{
		ret = 0;
	}else
	{
		RingBufWriteOne(&(uart_ports[port].out_buf), *buf);
		uart_fill_tx_fifo(UART0_BASE);
		ret = 1;
	}

    if(!bIntsOff)
    {
        MAP_IntMasterEnable();
    }
	return ret;
}

int uart_port_write_pending(unsigned int port)
{
    if  (uart_ports[port].status == PORT_STATUS_INITED)
    {
        return (int)RingBufUsed(&(uart_ports[port].out_buf));
    }else
    {
        return -1;
    }
}

static
int uart_port_no_tx(void)
{
	int i;
	if (uart_escaped_buf)
	{
		return 0;
	}
	for (i=0; i<UART_N_PORTS; ++i)
	{
		if (uart_ports[i].status == PORT_STATUS_INITED &&
				!RingBufEmpty(&(uart_ports[i].out_buf))  )
		{
			return 0;
		}
	}
	return 1;
}

