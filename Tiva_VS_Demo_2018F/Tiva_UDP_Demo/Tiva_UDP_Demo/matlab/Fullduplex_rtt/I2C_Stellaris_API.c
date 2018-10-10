//*****************************************************************************
//
// I2C_Stellaris_API.c - Stellaris I2C Master Driver.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// AUTHOR: JOERG QUINTEN
// E2E-NICKNAME: aBUGSworstnightmare
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/i2c.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
//#include "utils/uartstdio.h"
#include "I2C_Stellaris_API.h"

typedef struct
{
    unsigned long ulI2CBase;
    unsigned long ulI2CPeriph;
    //
    unsigned long ulSCLPinBase;
    unsigned long ulSCLPinPeriph;
    unsigned long ulSCLPinMask;
    unsigned long ulSCLPinI2CConfig;
    //
    unsigned long ulSDAPinBase;
    unsigned long ulSDAPinPeriph;
    unsigned long ulSDAPinMask;
    unsigned long ulSDAPinI2CConfig;
}I2C_HW_INFO, *I2C_HW_INFO_PTR;

const I2C_HW_INFO I2C_HW_INFO_TABLE[I2C_N_CONTROLLER] = { 
                      { I2C0_MASTER_BASE, 
                        SYSCTL_PERIPH_I2C0,
                        //
                        GPIO_PORTB_BASE,
                        SYSCTL_PERIPH_GPIOB,
                        GPIO_PIN_2,
                        GPIO_PB2_I2C0SCL,
                        //
                        GPIO_PORTB_BASE,
                        SYSCTL_PERIPH_GPIOB,
                        GPIO_PIN_3,
                        GPIO_PB3_I2C0SDA},
                        
                      { I2C1_MASTER_BASE, 
                        SYSCTL_PERIPH_I2C1,
                        //
                        GPIO_PORTA_BASE,
                        SYSCTL_PERIPH_GPIOA,
                        GPIO_PIN_6,
                        GPIO_PA6_I2C1SCL,
                        //
                        GPIO_PORTA_BASE,
                        SYSCTL_PERIPH_GPIOA,
                        GPIO_PIN_7,
                        GPIO_PA7_I2C1SDA},
                        
                      { I2C2_MASTER_BASE, 
                        SYSCTL_PERIPH_I2C2,
                        //
                        GPIO_PORTE_BASE,
                        SYSCTL_PERIPH_GPIOE,
                        GPIO_PIN_4,
                        GPIO_PE4_I2C2SCL,
                        //
                        GPIO_PORTE_BASE,
                        SYSCTL_PERIPH_GPIOE,
                        GPIO_PIN_5,
                        GPIO_PE5_I2C2SDA},
                        
                      { I2C3_MASTER_BASE, 
                        SYSCTL_PERIPH_I2C3,
                        //
                        GPIO_PORTB_BASE,
                        SYSCTL_PERIPH_GPIOD,
                        GPIO_PIN_0,
                        GPIO_PD0_I2C3SCL,
                        //
                        GPIO_PORTB_BASE,
                        SYSCTL_PERIPH_GPIOD,
                        GPIO_PIN_1,
                        GPIO_PD1_I2C3SDA}
};

unsigned long I2C_last_config[I2C_N_CONTROLLER] = {0};

static int I2CFindInfoByBase(unsigned long ulI2CBase);
static void I2CConfigPin(int i, unsigned long mode);
static long I2CWaitWhileMasterBusy(unsigned long ulI2CBase, long ulTimeout);
static void I2CStateRecovery(unsigned long ulI2CBase);
static void I2CErrorRecovery(unsigned long ulI2CBase);


//*****************************************************************************
//
//! Configures pin(s) for use as SCL by the I2C peripheral.
//!
//! \param ulPort is the base address of the GPIO port.
//! \param ucPins is the bit-packed representation of the pin(s).
//!
//! The I2C pins must be properly configured for the I2C peripheral to function
//! correctly.  This function provides the proper configuration for the SCL
//! pin(s).
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note This function should only be used for Blizzard-class devices.  It
//! cannot be used to turn any pin into an I2C SCL pin; it only configures an
//! I2C SCL pin for proper operation.  Devices with flexible pin muxing also
//! require a GPIOPinConfigure() function call.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOPinTypeI2CSCL(unsigned long ulPort, unsigned char ucPins)
{
    //
    // Check the arguments.
    //
    ASSERT(MAP_GPIOBaseValid(ulPort));

    //
    // Make the pin(s) be peripheral controlled.
    //
    MAP_GPIODirModeSet(ulPort, ucPins, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for open-drain operation with a weak pull-up.
    //
    // BLIZZARD CLASS only
    MAP_GPIOPadConfigSet(ulPort, ucPins, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
//! \internal
//! Checks a I2C master base address.
//!
//! \param ulI2CBase is the base address of the I2C Master module.
//!
//! This function determines if a I2C master module base address is valid.
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static tBoolean
I2CMasterBaseValid(unsigned long ulI2CBase)
{
	return(	(ulI2CBase == I2C0_MASTER_BASE) || (ulI2CBase == I2C1_MASTER_BASE) ||
			(ulI2CBase == I2C2_MASTER_BASE) || (ulI2CBase == I2C3_MASTER_BASE));
}
#endif

int I2CFindInfoByBase(unsigned long ulI2CBase)
{
    int i;
    for (i=0; i<I2C_N_CONTROLLER;++i)
    {
        if (ulI2CBase==I2C_HW_INFO_TABLE[i].ulI2CBase)
        {
            break;
        }
    }
    return (i==I2C_N_CONTROLLER)?-1:i;
}

void I2CConfigPin(int i, unsigned long mode)
{
    //
    // I2C0 is used with PortB[3:2].  The actual port and
    // pins used may be different on your part, consult the data sheet for
    // more information.  GPIO port B needs to be enabled so these pins can
    // be used.
    //
    MAP_SysCtlPeripheralEnable(I2C_HW_INFO_TABLE[i].ulSCLPinPeriph);
    MAP_SysCtlPeripheralEnable(I2C_HW_INFO_TABLE[i].ulSDAPinPeriph);
    
    if (mode == I2C_PIN_I2C)
    {
        //
        // Select the I2C function for these pins.  This function will also
        // configure the GPIO pins for I2C operation, setting them to
        // open-drain operation with weak pull-ups.  Consult the data sheet
        // to see which functions are allocated per pin.
        //
        MAP_GPIOPinTypeI2CSCL(I2C_HW_INFO_TABLE[i].ulSCLPinBase, I2C_HW_INFO_TABLE[i].ulSCLPinMask);	//	special I2CSCL treatment for M4F devices
        MAP_GPIOPinTypeI2C(I2C_HW_INFO_TABLE[i].ulSDAPinBase, I2C_HW_INFO_TABLE[i].ulSDAPinMask);

        //
        // Configure the pin muxing for I2C0 functions on port B2 and B3.
        // This step is not necessary if your part does not support pin muxing.
        //
        MAP_GPIOPinConfigure(I2C_HW_INFO_TABLE[i].ulSCLPinI2CConfig);
        MAP_GPIOPinConfigure(I2C_HW_INFO_TABLE[i].ulSDAPinI2CConfig);
    }else //I2C_PIN_GPIO
    {
        //GPIO Overide
        MAP_GPIOPinTypeGPIOOutputOD(I2C_HW_INFO_TABLE[i].ulSCLPinBase, I2C_HW_INFO_TABLE[i].ulSCLPinMask);	
        MAP_GPIOPinTypeGPIOInput(I2C_HW_INFO_TABLE[i].ulSDAPinBase, I2C_HW_INFO_TABLE[i].ulSDAPinMask);
        MAP_GPIOPinConfigure(I2C_HW_INFO_TABLE[i].ulSCLPinI2CConfig & (~0xF));
        MAP_GPIOPinConfigure(I2C_HW_INFO_TABLE[i].ulSDAPinI2CConfig & (~0xF)); 
    }
}

//*****************************************************************************
//
//! Initializes and enables the specified I2C block.
//!
//! \param ulI2CBase is the I2C peripheral to be used.
//! \param ulI2C400kbps defines the normal (100kbps) or fast (400kbps) I2C mode.
//!
//! This function enables the specified I2C block and sets it up to run at
//! the either 100kbps or 400kbps.  If the \e ulI2C400kbps is false, the I2C will
//! run at 100kbps and if true, then the I2C will run at 400kbps.  The
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return None.
//
//*****************************************************************************
void I2CSetup(unsigned long ulI2CBase, unsigned int ulInitOption)
{
    int i;
    //
    // Check the arguments.
    //
	ASSERT(I2CMasterBaseValid(ulI2CBase));
    
    i = I2CFindInfoByBase(ulI2CBase);
    
    if (i<0) return; // cannot find
    
    I2C_last_config[i] = ulInitOption | I2C_INIT_PIN | I2C_INIT_LOGIC;
    
    if (ulInitOption | I2C_INIT_PIN)
    {
        I2CConfigPin(i, I2C_PIN_I2C);
    }
    if (ulInitOption | I2C_INIT_LOGIC)
    {
        if (ulInitOption | I2C_INIT_RESET)
        {
            MAP_SysCtlPeripheralReset(I2C_HW_INFO_TABLE[i].ulI2CPeriph);
        }
        //
        // The I2C0 peripheral must be enabled before use.
        //
        MAP_SysCtlPeripheralEnable(I2C_HW_INFO_TABLE[i].ulI2CPeriph);

        //
        // Enable and initialize the I2C0 master module.
        //
        MAP_I2CMasterInitExpClk(I2C_HW_INFO_TABLE[i].ulI2CBase, MAP_SysCtlClockGet(), (ulInitOption | I2C_INIT_400Kbps)!=0);
    }

}
// ulTimeout in number of bit time (  less than 0 means wait forever
// Return 0 if not timeout, 1 if timeout
long I2CWaitWhileMasterBusy(unsigned long ulI2CBase, long ulTimeout)
{
    if (ulTimeout<0)
    {
        while(MAP_I2CMasterBusy(ulI2CBase));
        return 0; // always not timeout
    }else
    {
        //x  assuming 400kbps, it will be approximately 1/400e3=2.5us
        //x  assuming the loop is approximately 10 cycles
        ulTimeout*=I2C_WAIT_UNIT; 
        while(MAP_I2CMasterBusy(ulI2CBase) && ulTimeout--)
        {
        };
        return (ulTimeout==-1);
    }
}

void I2CStateRecovery(unsigned long ulI2CBase)
{
    unsigned long line;
    int i;
    int n;
    
    line = MAP_I2CMasterLineStateGet(ulI2CBase);
    
    i = I2CFindInfoByBase(ulI2CBase);
    if (i<0) return;
    
    switch(line)
    {
    case 1: // SDA low, SCL high, slave stuck because of missing SCL    
        I2CConfigPin(i, I2C_PIN_GPIO);
        n = 10;
        while( MAP_GPIOPinRead(I2C_HW_INFO_TABLE[i].ulSDAPinBase, 
                           I2C_HW_INFO_TABLE[i].ulSDAPinMask) ==0  && n>0)
        {
            MAP_GPIOPinWrite(I2C_HW_INFO_TABLE[i].ulSCLPinBase, 
                           I2C_HW_INFO_TABLE[i].ulSCLPinMask,0 );
            // wait one bit of time
            MAP_SysCtlDelay(MAP_SysCtlClockGet()/400000); 
            MAP_GPIOPinWrite(I2C_HW_INFO_TABLE[i].ulSCLPinBase, 
                           I2C_HW_INFO_TABLE[i].ulSCLPinMask,
                           I2C_HW_INFO_TABLE[i].ulSCLPinMask );
            // wait another bit of time
            MAP_SysCtlDelay(MAP_SysCtlClockGet()/400000);
            n--;
        }
        if (n)
        {
            //it works! fixed it !
            I2CConfigPin(i, I2C_PIN_I2C);
        }else
        {
            I2CErrorRecovery(ulI2CBase);
        }
        break;
    case 3: // SDA high, SCL high
        if (MAP_I2CMasterErr(ulI2CBase) | I2C_MASTER_ERR_ARB_LOST)
        {
            I2CErrorRecovery(ulI2CBase);
        }
    default:
        //do nothing
        break;
    }

}
void I2CErrorRecovery(unsigned long ulI2CBase)
{
    int i;
    i = I2CFindInfoByBase(ulI2CBase);
    I2CSetup(ulI2CBase, (I2C_last_config[i] & (~ I2C_INIT_PIN)) | I2C_INIT_RESET);
    //MAP_I2CMasterDisable(ulI2CBase);
}

//*****************************************************************************
//
//! Reads the I2C slave register.
//!
//! \param ulI2CBase is the base for the I2C module.
//! \param ucSlaveAdress is the 7-bit address of the slave to be addressed.
//! \param ucReg is the register to read from.
//!
//! This function initiates a read from the slave device.
//! The ulI2CBase parameter is the I2C modules master base address.
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return Register value in an unsigned long format.  Note that 0 will be
//! returned if there is ever an error, 1 if there was not.
//
//*****************************************************************************
unsigned long
I2CRegRead(unsigned long ulI2CBase, unsigned char ucSlaveAdress, unsigned char ucReg, unsigned char* pucValue)
{
    unsigned long ulRegValue = 0;

	//
	// Check the arguments.
	//
	ASSERT(I2CMasterBaseValid(ulI2CBase));

    //MAP_I2CMasterEnable(ulI2CBase);
    
	//
	// Wait until master module is done transferring.
	//
	if (I2CWaitWhileMasterBusy(ulI2CBase, I2C_WAIT_DEFAULT))
    {
        I2CStateRecovery(ulI2CBase);
        return 0;
    }

    //
    // Tell the master module what address it will place on the bus when
    // writing to the slave.
    //
    MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucSlaveAdress, 0);

    //
    // Place the command to be sent in the data register.
    //
    MAP_I2CMasterDataPut(ulI2CBase, ucReg);

    //
    // Initiate send of data from the master.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_SINGLE_SEND);

    //
    // Wait until master module is done transferring.
    //
	if (I2CWaitWhileMasterBusy(ulI2CBase, I2C_WAIT_DEFAULT))
    {
        I2CStateRecovery(ulI2CBase);
        return 0;
    }

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        I2CErrorRecovery(ulI2CBase);
        return 0;
    }

    //
    // Tell the master module what address it will place on the bus when
    // reading from the slave.
    //
    MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucSlaveAdress, 1);

    //
    // Tell the master to read data.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //
    // Wait until master module is done receiving.
    //
	if (I2CWaitWhileMasterBusy(ulI2CBase, I2C_WAIT_DEFAULT))
    {
        I2CStateRecovery(ulI2CBase);
        return 0;
    }

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        I2CErrorRecovery(ulI2CBase);
        return 0;
    }

    //
    // Read the data from the master.
    //
    ulRegValue = MAP_I2CMasterDataGet(ulI2CBase);
    
    *pucValue = (unsigned char) ulRegValue;

    //
    // Return the no error
    //
    return 1;
}

//*****************************************************************************
//
//! Writes to the specified I2C slave register.
//!
//! \param ulI2CBase is the base for the I2C module.
//! \param ucSlaveAdress is the 7-bit address of the slave to be addressed.
//! \param ucReg is the register to write data to.
//! \param ucValue is the 8-bit data to be written.
//!
//! This function initiates a read from the I2C slave device.
//! The ulI2CBase parameter is the I2C modules master base address.
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return Register value in an unsigned long format.  Note that 0 will be
//! returned if there is ever an error, 1 if there was not.
//
//*****************************************************************************
unsigned long
I2CRegWrite(unsigned long ulI2CBase, unsigned char ucSlaveAdress,
		 unsigned char ucReg, unsigned char ucValue)
{
	//
	// Check the arguments.
	//
	ASSERT(I2CMasterBaseValid(ulI2CBase));

	//
	// Wait until master module is done transferring.
	//
	while(MAP_I2CMasterBusy(ulI2CBase))
	{
	};

    //
    // Tell the master module what address it will place on the bus when
    // writing to the slave.
    //
    MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucSlaveAdress, 0);

    //
    // Place the command to be sent in the data register.
    //
    MAP_I2CMasterDataPut(ulI2CBase, ucReg);

    //
    // Initiate send of data from the master.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    //
    // Wait until master module is done transferring.
    //
    while(MAP_I2CMasterBusy(ulI2CBase))
    {
    };

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        return 0;
    }

    //
    // Place the value to be sent in the data register.
    //
    MAP_I2CMasterDataPut(ulI2CBase, ucValue);

    //
    // Initiate send of data from the master.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_BURST_SEND_CONT);

    //
    // Wait until master module is done transferring.
    //
    while(MAP_I2CMasterBusy(ulI2CBase))
    {
    };

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        return 0;
    }

    //
    // Initiate send of data from the master.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_BURST_SEND_FINISH);

    //
    // Wait until master module is done transferring.
    //
    while(MAP_I2CMasterBusy(ulI2CBase))
    {
    };

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        return 0;
    }

    //
    // Return 1 if there is no error.
    //
    return 1;
}


//*****************************************************************************
//
//! Reads one/multiple bytes of data from an I2C slave device.
//!
//! \param ulI2CBase is the base for the I2C module.
//! \param ucSlaveAdress is the 7-bit address of the slave to be addressed.
//! \param ucReg is the register to start reading from.
//! \param cReadData is a pointer to the array to store the data.
//! \param uiSize is the number of bytes to read from the slave.
//!
//! This function reads one/multiple bytes of data from an I2C slave device.
//! The ulI2CBase parameter is the I2C modules master base address.
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return 0 if there was an error or 1 if there was not.
//
//*****************************************************************************
unsigned long
I2CReadData(unsigned long ulI2CBase, unsigned char ucSlaveAdress,
		unsigned char ucReg, char* cReadData, unsigned int uiSize)
{
	unsigned int uibytecount;		// local variable used for byte counting/state determination
	int MasterOptionCommand;		// used to assign the commands for MAP_I2CMasterControl() function

	//
	// Check the arguments.
	//
	ASSERT(I2CMasterBaseValid(ulI2CBase));

    //MAP_I2CMasterEnable(ulI2CBase);
    
	//
	// Wait until master module is done transferring.
	//
	if (I2CWaitWhileMasterBusy(ulI2CBase, I2C_WAIT_DEFAULT))
    {
        I2CStateRecovery(ulI2CBase);
        return 0;
    }

    //
    // Tell the master module what address it will place on the bus when
    // writing to the slave.
    //
    MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucSlaveAdress, 0);

    //
    // Place the command to be sent in the data register.
    //
    MAP_I2CMasterDataPut(ulI2CBase, ucReg);

    //
    // Initiate send of data from the master.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_SINGLE_SEND);

    //
    // Wait until master module is done transferring.
    //
	if (I2CWaitWhileMasterBusy(ulI2CBase, I2C_WAIT_DEFAULT))
    {
        I2CStateRecovery(ulI2CBase);
        return 0;
    }

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        I2CErrorRecovery(ulI2CBase);
        return 0;
    }


	//
	// Tell the master module what address it will place on the bus when
	// reading from the slave.
	//
	MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucSlaveAdress, true);

	//
	// Start with BURST with more than one byte to write
	//
	MasterOptionCommand = I2C_MASTER_CMD_BURST_RECEIVE_START;


	for(uibytecount = 0; uibytecount < uiSize; uibytecount++)
	{
		//
		// The second and intermittent byte has to be read with CONTINUE control word
		//
		if(uibytecount == 1)
			MasterOptionCommand = I2C_MASTER_CMD_BURST_RECEIVE_CONT;

		//
		// The last byte has to be send with FINISH control word
		//
		if(uibytecount == uiSize - 1)
			MasterOptionCommand = I2C_MASTER_CMD_BURST_RECEIVE_FINISH;

		//
		// Re-configure to SINGLE if there is only one byte to read
		//
		if(uiSize == 1)
			MasterOptionCommand = I2C_MASTER_CMD_SINGLE_RECEIVE;

		//
		// Initiate read of data from the slave.
		//
		MAP_I2CMasterControl(ulI2CBase, MasterOptionCommand);

		//
		// Wait until master module is done reading.
		//
        if (I2CWaitWhileMasterBusy(ulI2CBase, I2C_WAIT_DEFAULT))
        {
            I2CStateRecovery(ulI2CBase);
            return 0;
        }

		//
        // Check for errors.
        //
        if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
        {
            I2CErrorRecovery(ulI2CBase);
            return 0;
        }

        //
        // Move byte from register
        //
		cReadData[uibytecount] = MAP_I2CMasterDataGet(ulI2CBase);
	}

	// send number of received bytes
	return uibytecount;
}

//*****************************************************************************
//
//! Writes one/multiple bytes of data to an I2C slave device.
//! Ensure to use auto-increment options on some devices
//! (Control Registers, refer to data sheet).
//! I.e. store related command in the first position of your data array.
//!
//! \param ulI2CBase is the base for the I2C module.
//! \param ucSlaveAdress is the 7-bit address of the slave to be addressed.
//! \param ucReg is the register to start writing to.
//! \param cSendData is a pointer to the array to be send.
//! \param uiSize is the number of bytes to send from array cSendData[].
//!
//! This function writes multiple bytes of data an I2C slave device.
//! The ulI2CBase parameter is the I2C modules master base address.
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return 0 if there was an error or 1 if there was not.
//
//*****************************************************************************
unsigned long
I2CWriteData(unsigned long ulI2CBase, unsigned char ucSlaveAdress,
		unsigned char ucReg, const char* cSendData, unsigned int uiSize)
{
	unsigned int uibytecount;		// local variable used for byte counting/state determination
	int MasterOptionCommand;		// used to assign the commands for MAP_I2CMasterControl() function

	//
	// Check the arguments.
	//
	ASSERT(I2CMasterBaseValid(ulI2CBase));

	//
	// Wait until master module is done transferring.
	//
	while(MAP_I2CMasterBusy(ulI2CBase))
	{
	};

    //
    // Tell the master module what address it will place on the bus when
    // writing to the slave.
    //
    MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucSlaveAdress, false);

    //
    // Place the value to be sent in the data register.
    //
    MAP_I2CMasterDataPut(ulI2CBase, ucReg);

    //
    // Initiate send of data from the master.
    //
    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_BURST_SEND_START);

    //
    // Wait until master module is done transferring.
    //
    while(MAP_I2CMasterBusy(ulI2CBase))
    {
    };

    //
    // Check for errors.
    //
    if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
    {
        return 0;
    }

	//
	// Start with CONT for more than one byte to write
	//
	MasterOptionCommand = I2C_MASTER_CMD_BURST_SEND_CONT;


	for(uibytecount = 0; uibytecount < uiSize; uibytecount++)
	{
		//
		// The second and intermittent byte has to be send with CONTINUE control word
		//
		if(uibytecount == 1)
			MasterOptionCommand = I2C_MASTER_CMD_BURST_SEND_CONT;

		//
		// The last byte has to be send with FINISH control word
		//
		if(uibytecount == uiSize - 1)
			MasterOptionCommand = I2C_MASTER_CMD_BURST_SEND_FINISH;

		//
		// Re-configure to SINGLE if there is only one byte to write
		//
		if(uiSize == 1)
			MasterOptionCommand = I2C_MASTER_CMD_SINGLE_SEND;

		//
		// Send data byte
		//
		MAP_I2CMasterDataPut(ulI2CBase, cSendData[uibytecount]);

		//
		// Initiate send of data from the master.
		//
		MAP_I2CMasterControl(ulI2CBase, MasterOptionCommand);

		//
		// Wait until master module is done transferring.
		//
		while(MAP_I2CMasterBusy(ulI2CBase))
		{
		};

		//
        // Check for errors.
        //
        if(MAP_I2CMasterErr(ulI2CBase) != I2C_MASTER_ERR_NONE)
        {
            return 0;
        }
	}

    //
    // Return 1 if there is no error.
    //
    return 1;
}

//*****************************************************************************
//
//! Probes the selected I2C bus for available slave devices
//!
//! \param ulI2CBase is the base for the I2C module.
//!
//! This function scans the selected I2C bus for available I2C slave device.
//! The ulI2CBase parameter is the I2C modules master base address.
//! \e ulI2CBase parameter can be one of the following values:
//!
//! - \b I2C0_MASTER_BASE
//! - \b I2C1_MASTER_BASE
//! - \b I2C2_MASTER_BASE
//! - \b I2C3_MASTER_BASE
//!
//! \return 0 if there was an error or 1 if there was not.
//
//*****************************************************************************
unsigned long
I2CBusScan(unsigned long ulI2CBase)
{
#if 0
	unsigned char ucProbeAdress;
	unsigned long ucerrorstate;

	//
	// Check the arguments.
	//
	ASSERT(I2CMasterBaseValid(ulI2CBase));

	//
	// Wait until master module is done transferring.
	//
	while(MAP_I2CMasterBusy(ulI2CBase))
	{
	};

	//
	// I2C Addresses are 7-bit values
	// probe the address range of 0 to 127 to find I2C slave devices on the bus
	//
	for (ucProbeAdress = 0; ucProbeAdress < 127; ucProbeAdress++)
	{
	    //
	    // Tell the master module what address it will place on the bus when
	    // writing to the slave.
	    //
		MAP_I2CMasterSlaveAddrSet(ulI2CBase, ucProbeAdress, false);
	    MAP_SysCtlDelay(50000);

	    //
	    // Place the command to be sent in the data register.
	    //
	    MAP_I2CMasterDataPut(ulI2CBase, 0x00);

	    //
	    // Initiate send of data from the master.
	    //
	    MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_BURST_SEND_START);

	    //
	    // Make some delay
	    //
	    MAP_SysCtlDelay(500000);

	    //
	    // Read the I2C Master Control/Status (I2CMCS) Register to a local
	    // variable
	    //
	    ucerrorstate = MAP_I2CMasterErr(ulI2CBase);

	    //
	    // Examining the content I2C Master Control/Status (I2CMCS) Register
	    // to see if the ADRACK-Bit (Acknowledge Address) is TRUE (1)
	    // ( 1: The transmitted address was not acknowledged by the slave)
	    //
	    if(ucerrorstate & I2C_MASTER_ERR_ADDR_ACK)
	    {
	    	//
	    	// device at selected address did not acknowledge --> there's no device
	    	// with this address present on the I2C bus
	    	//
	        //
	        // Print a message to Stdio
	        //
	    	//UARTprintf("Address not found: 0x%2x - %3d\n",ucProbeAdress,ucProbeAdress);
		    //
		    // Make some delay
		    //
	    	//MAP_SysCtlDelay(1500000);
	    }

	    //
	    // ( 0: The transmitted address was acknowledged by the slave)
	    //
	    else
	    {
	    	//
	    	// device at selected address acknowledged --> there is a device
	    	// with this address present on the I2C bus
	    	//
	        //
	        // Print a message to Stdio
	        //
	    	UARTprintf("Address found: 0x%2x - %3d\n",ucProbeAdress,ucProbeAdress);

		    //
		    // Make some delay
		    //
	    	MAP_SysCtlDelay(1500000);
	    }
	}

	//
	// End transfer of data from the master.
	//
	MAP_I2CMasterControl(ulI2CBase, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    //
    // Print a message to Stdio
    //
	UARTprintf("I2C Bus-Scan done...\n");

    //
    // Return 1 if there is no error.
    //
    return 1;
#endif
    return 0;
}

