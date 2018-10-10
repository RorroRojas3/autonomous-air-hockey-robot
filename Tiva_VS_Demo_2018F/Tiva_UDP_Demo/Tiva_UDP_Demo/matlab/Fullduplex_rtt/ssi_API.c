#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"

#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "ssi_API.h"

static void init_ssi0_master(unsigned long mode, unsigned long bitrate);

void ssi0_init(void)
{
    init_ssi0_master(SSI_FRF_MOTO_MODE_0, 4*1000*1000); //4 Mbps
    
    // maunal control of ssi
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1); 
}

void ssi0_ss(unsigned long sel)
{
	if (sel)
	{
		ssi0_ss2(1);
	}else
	{
		ssi0_ss2(0);
	}
}

/*
 * 1 ~ 3 to select, 0 to deselect
 *
 * 1: PA3
 * 2: PD0
 * 3: PD1
 */
int ssi0_ss2(unsigned long sel)
{
    static int occupied = 0;
    
    if (occupied && sel) return 0;
    
    if (sel) occupied=1;
    else  occupied=0;
    
    switch(sel)
    {
    case 1:
        MAP_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
        break;
    case 2:
        MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
        break;
    case 3:
        MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);
        break;
    case 0:
    default:
        MAP_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0xFF);
        MAP_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1, 0xFF);
        break;
    }
    return 1;
}


void ssi0_write(unsigned long data)
{
	MAP_SSIDataPut(SSI0_BASE, data);

	while(MAP_SSIBusy(SSI0_BASE))
	{
	}
	MAP_SSIDataGet(SSI0_BASE, &data);
}

void ssi0_read(unsigned long * pdata)
{
	MAP_SSIDataPut(SSI0_BASE, 0x81);

	while(MAP_SSIBusy(SSI0_BASE))
	{
	}
	MAP_SSIDataGet(SSI0_BASE, pdata);
}

static void init_ssi0_master(unsigned long mode, unsigned long bitrate)
{
	unsigned long buf;
    //
    // The SSI0 peripheral must be enabled for use.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    //
    // For this example SSI0 is used with PortA[5:2].  The actual port and pins
    // used may be different on your part, consult the data sheet for more
    // information.  GPIO port A needs to be enabled so these pins can be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for SSI0 functions on port A2, A3, A4, and A5.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    //MAP_GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX);
    MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX);

    //
    // Configure the GPIO settings for the SSI pins.  This function also gives
    // control of these pins to the SSI hardware.  Consult the data sheet to
    // see which functions are allocated per pin.
    // The pins are assigned as follows:
    //      PA5 - SSI0Tx
    //      PA4 - SSI0Rx
    //      PA3 - SSI0Fss
    //      PA2 - SSI0CLK
    // TODO: change this to select the port/pin you are using.
    //
    MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | //GPIO_PIN_3 |
                   GPIO_PIN_2);

    //
    // Configure and enable the SSI port for SPI master mode.  Use SSI0,
    // system clock supply, idle clock level low and active low clock in
    // freescale SPI mode, master mode, 1MHz SSI frequency, and 8-bit data.
    // For SPI mode, you can set the polarity of the SSI clock when the SSI
    // unit is idle.  You can also configure what clock edge you want to
    // capture data on.  Please reference the datasheet for more information on
    // the different SPI modes.
    //
    MAP_SSIConfigSetExpClk(SSI0_BASE, MAP_SysCtlClockGet(), mode,
                       SSI_MODE_MASTER, bitrate, 8);

    //
    // Enable the SSI0 module.
    //
    MAP_SSIEnable(SSI0_BASE);

    ssi0_ss(0);

    //
    // Read any residual data from the SSI port.  This makes sure the receive
    // FIFOs are empty, so we don't read any unwanted junk.  This is done here
    // because the SPI SSI mode is full-duplex, which allows you to send and
    // receive at the same time.  The SSIDataGetNonBlocking function returns
    // "true" when data was returned, and "false" when no data was returned.
    // The "non-blocking" function checks if there is any data in the receive
    // FIFO and does not "hang" if there isn't.
    //
    while(MAP_SSIDataGetNonBlocking(SSI0_BASE, &buf))
    {
    }
}


