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
#include "uartx_driver.h"

tRingBufObject	uartx_tx_buf;
tRingBufObject	uartx_rx_buf;

unsigned int uartx_rx_skipped = 0;


static
void uartx_buffer_init(void)
{
	// statically allocate buffer
	static unsigned char uartx_tx_buf_data[UARTX_TX_BUF_SIZE];
	static unsigned char uartx_rx_buf_data[UARTX_RX_BUF_SIZE];

	RingBufInit(&uartx_tx_buf, uartx_tx_buf_data, UARTX_TX_BUF_SIZE);
	RingBufInit(&uartx_rx_buf, uartx_rx_buf_data, UARTX_RX_BUF_SIZE);

	uartx_rx_skipped = 0;
}

void uartx_init(unsigned long baud)
{
	// Software init
	uartx_buffer_init();

	// Hardware init
    uart_init_hw(1, baud, UART_INTERRUPT_MODE);
}


static
void uartx_fill_tx_fifo(unsigned long base, tRingBufObject* tx_buf)
{
	MAP_UARTIntDisable(base, UART_INT_TX);
    while(!RingBufEmpty(tx_buf) && MAP_UARTSpaceAvail(base))
    {
        MAP_UARTCharPutNonBlocking(base, RingBufReadOne(tx_buf));
    }
    MAP_UARTIntEnable(base, UART_INT_TX);
}

static
void uartx_fetch_rx_fifo(unsigned long base, tRingBufObject* rx_buf)
{
    while(!RingBufFull(rx_buf) && MAP_UARTCharsAvail(base))
    {
    	RingBufWriteOne(rx_buf, MAP_UARTCharGetNonBlocking(base));
    }
}

static
void uartx_general_intr(unsigned long base, tRingBufObject* tx_buf, tRingBufObject* rx_buf)
{
    unsigned long ulInts;

    // Get and clear the current interrupt source(s)
    ulInts = MAP_UARTIntStatus(base, true);
    MAP_UARTIntClear(base, ulInts);

    // Are we being interrupted because the TX FIFO has space available?
    if(ulInts & UART_INT_TX)
    {
        // Move as many bytes as we can into the transmit FIFO.
    	uartx_fill_tx_fifo(base, tx_buf);
     
        // If the tx buffer is empty, turn off the transmit interrupt.
        if(RingBufEmpty(tx_buf))
        {
            MAP_UARTIntDisable(base, UART_INT_TX);
        }
    }

    // Are we being interrupted due to a received character?
    if(ulInts & (UART_INT_RX | UART_INT_RT))
    {
        // Get all the available characters from the UART.
    	uartx_fetch_rx_fifo(base, rx_buf);

    	// prevent further RX interrupt as the buffer is full
    	while(MAP_UARTIntStatus(base, true) & UART_INT_RX)
    	{
    		MAP_UARTCharGetNonBlocking(base);
    		++uartx_rx_skipped;
    	}
    }
}

void UART1IntHandler(void)
{
	uartx_general_intr(UART1_BASE, &uartx_tx_buf, &uartx_rx_buf);
}

int uartx_read_one(unsigned char* buf)
{
    tBoolean bIntsOff;
    int ret = 0;

	bIntsOff = MAP_IntMasterDisable();

	if (RingBufEmpty(&uartx_rx_buf))
	{
		ret = 0;
	}else
	{
		*buf = RingBufReadOne(&uartx_rx_buf);
		ret = 1;
	}

    if(!bIntsOff)
    {
        MAP_IntMasterEnable();
    }
	return ret;
}


int uartx_write_one(unsigned char* buf)
{
    tBoolean bIntsOff;
    int ret = 0;

	bIntsOff = MAP_IntMasterDisable();

	if (RingBufFull(&uartx_tx_buf))
	{
		ret = 0;
	}else
	{
		RingBufWriteOne(&uartx_tx_buf, *buf);
		uartx_fill_tx_fifo(UARTX_BASE, &uartx_tx_buf);
		ret = 1;
	}

    if(!bIntsOff)
    {
        MAP_IntMasterEnable();
    }
	return ret;
}

int uartx_read_pending()
{
    return (int)RingBufUsed(&uartx_rx_buf);
}

int uartx_write_pending()
{
    return (int)RingBufUsed(&uartx_tx_buf);
}
