#include <limits.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
//#define PART_LM4F120H5QR
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "I2C_Stellaris_API.h"
#include "ssi_API.h"

#include "stellaris_runtime.h"
#include "reentrance.h"

#include "uart_driver_mp.h"
#include "xprintf.h"

static void tick_handler(void);

//void rt_OneStepM(void);
void rt_OneStep(void);

void system_init(void)
{   
    // safty first
    system_safe();
    
	//init system
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    if (LAZY_STACKING)
    {
        MAP_FPULazyStackingEnable();
    } else {
        MAP_FPUStackingEnable();
    }
    
    // set sys clock 40MHZ
    //MAP_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
    //                    SYSCTL_OSC_MAIN);
    
	// set sys clock 80MHZ
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
	// set sys clock 100MHZ
    //MAP_SysCtlClockSet(SYSCTL_SYSDIV_2 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
    //               SYSCTL_XTAL_16MHZ);
    
	// enable all pins
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   

    //reset visual clue
    led_debug_signal(LED_DEBUG_RESET);
    
    // init uart for debugging
        uart_bare_init();
        xdev_out(uart_bare_putchar);
        
	//Init AD Converter ports
		adc_init();

	//Init PWM
		pwm_init();

	//Init Counter
	//	counter_init(); // disabled because it is not used! Jan 19 2014 

	//Init I2C
        i2c_init();
        
	//Init SPI
        ssi0_init();
        
	// Init GPIO
		gpio_init();

    // Init (more sophisticated) serial
        uart_init();
        
    // Init console
        console_init();
        
    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();
}
void system_reset(void)
{
    system_safe();
    MAP_SysCtlReset();
}
void system_safe(void)
{
    pwm_shutdown();
}

void system_delay_ms(int ms)
{
	MAP_SysCtlDelay(MAP_SysCtlClockGet()/1000 * ms / 3 );
}

void led_debug_signal(int id)
{
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_ALL);
    switch(id)
    {        
    case LED_DEBUG_RESET: //reset

        led_debug_signal(LED_DEBUG_ALL_ON);
        system_delay_ms(200);
        led_debug_signal(LED_DEBUG_ALL_OFF);
        system_delay_ms(100);
        led_debug_signal(LED_DEBUG_ALL_ON);
        system_delay_ms(200);
        led_debug_signal(LED_DEBUG_ALL_OFF);
        system_delay_ms(100);
        break;
        
     case LED_DEBUG_OVERRUN: // overrun
        while(1)
        {
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, LED_BLUE);
            system_delay_ms(100);
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, LED_GREEN);
            system_delay_ms(100);
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, LED_RED);
            system_delay_ms(100);
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, 0);
            system_delay_ms(100);
        }
        //break;
     case LED_DEBUG_REENTRANCE: // re-entrance stack corruption
        while(1)
        {
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, LED_BLUE);
            system_delay_ms(500);
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, 0);
            system_delay_ms(300);
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, LED_RED);
            system_delay_ms(500);
            MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, 0);
            system_delay_ms(300);
        }
        //break;
     case LED_DEBUG_ALL_ON:
        MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, LED_ALL);
        break;     
     case LED_DEBUG_ALL_OFF:
        MAP_GPIOPinWrite(GPIO_PORTF_BASE,  LED_ALL, 0);
        break;
    }
}


////////////////////////////////////////////////////////////////////
//////////////// GPIO SPECIFIC /////////////////////////////////////
////////////////////////////////////////////////////////////////////
void gpio_init()
{
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01; //enable PF0
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
}


////////////////////////////////////////////////////////////////////
/////////////////COUNTER SPECIFIC //////////////////////////////////
////////////////////////////////////////////////////////////////////

const unsigned long COUNTER_BASE_TABLE[]={WTIMER2_BASE, WTIMER2_BASE, WTIMER2_BASE, WTIMER2_BASE};
const unsigned long COUNTER_TIMER_TABLE[]={TIMER_A, TIMER_B, TIMER_A, TIMER_B};

void counter_init()
{
	//Init counter backed by timers
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER2);  //CNT 1 2
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER3);  //CNT 3 4

	// disable before change
	MAP_TimerDisable(WTIMER2_BASE, TIMER_BOTH);
	MAP_TimerDisable(WTIMER3_BASE, TIMER_BOTH);

	// setup mode of operation
	// count up
	MAP_TimerConfigure(WTIMER2_BASE, TIMER_CFG_SPLIT_PAIR |  TIMER_CFG_A_CAP_COUNT |
						TIMER_CFG_B_CAP_COUNT);
	MAP_TimerConfigure(WTIMER3_BASE, TIMER_CFG_SPLIT_PAIR |  TIMER_CFG_A_CAP_COUNT |
						TIMER_CFG_B_CAP_COUNT);

	// setup pin
	//Pin Config
	MAP_GPIOPinTypeTimer(GPIO_PORTD_BASE, 0x0F);  //PD 0 1 2 3

	MAP_GPIOPinConfigure(GPIO_PD0_WT2CCP0);
	MAP_GPIOPinConfigure(GPIO_PD1_WT2CCP1);
	MAP_GPIOPinConfigure(GPIO_PD2_WT3CCP0);
	MAP_GPIOPinConfigure(GPIO_PD3_WT3CCP1);
}

void counter_init_channel(int ch_id)
{
	unsigned long base, timer;

	if (ch_id > 0 && ch_id<=4)
	{
		base = COUNTER_BASE_TABLE[ch_id-1];
		timer = COUNTER_TIMER_TABLE[ch_id-1];
	}else
	{
		return;
	}

	MAP_TimerPrescaleSet(base, timer, USHRT_MAX);
	MAP_TimerLoadSet(base, timer, ULONG_MAX);

	MAP_TimerPrescaleMatchSet(base, timer, 0); //maximum pre-match
	MAP_TimerMatchSet(base, timer, 0); // 32/48 bit counter should never match

	MAP_TimerControlEvent(base, timer, TIMER_EVENT_POS_EDGE);
	MAP_TimerEnable(base, timer);

}

unsigned long long counter_read_channel_pr(int ch_id)
{
	unsigned long base, timer, value_hi, value_lo;
	if (ch_id > 0 && ch_id<=4)
	{
		base = COUNTER_BASE_TABLE[ch_id-1];
		timer = COUNTER_TIMER_TABLE[ch_id-1];
	}else
	{
		return 0;
	}

	do{
		value_hi = MAP_TimerPrescaleGet(base, timer);
		value_lo = MAP_TimerValueGet(base, timer);
	}while(value_hi != MAP_TimerLoadGet(base, timer));

	// in counter mode, prescaler is the high bits
	return 0-((unsigned long long)value_hi<<32 | value_lo);
}
unsigned long counter_read_channel(int ch_id)
{
	unsigned long base, timer;
	if (ch_id > 0 && ch_id<=4)
	{
		base = COUNTER_BASE_TABLE[ch_id-1];
		timer = COUNTER_TIMER_TABLE[ch_id-1];
	}else
	{
		return 0;
	}
	return 0-MAP_TimerValueGet(base, timer);
}

// differential channel used for quadrature interfacing
// TIMER A is the up pulse channel, TIMER_B is the down pulse channel
// since we use down counter here, TIMER_B - TIMER_A
int counter_read_diff(int ch_id)
{
	unsigned long ch_a, ch_b;
	if (ch_id > 0 && ch_id<=4)
	{
		ch_a = ((ch_id-1) & (~1)) +1;
		ch_b = ch_a + 1;
		//timer = COUNTER_TIMER_TABLE[ch_id-1];
	}else
	{
		return 0;
	}

	return counter_read_channel_pr(ch_a) - counter_read_channel_pr(ch_b);
}

//////////////// PWM SPECIFIC //////////////////////////////////////
const unsigned long PWM_BASE_TABLE[]={WTIMER0_BASE, WTIMER0_BASE, WTIMER1_BASE, WTIMER1_BASE,WTIMER5_BASE, WTIMER5_BASE};
const unsigned long PWM_TIMER_TABLE[]={TIMER_A, TIMER_B, TIMER_A, TIMER_B, TIMER_A, TIMER_B};

void pwm_init()
{
    //unlock and enable PD7 as normal pin
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY_DD;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;  //enable PD7
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0; 	 //LOCK again
    
	//Init PWM backed by timers
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);  //PWM 1 2
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);  //PWM 3 4
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER5);  //PWM 5 6

	// disable before change
	MAP_TimerDisable(WTIMER0_BASE, TIMER_BOTH);
	MAP_TimerDisable(WTIMER1_BASE, TIMER_BOTH);
	MAP_TimerDisable(WTIMER5_BASE, TIMER_BOTH);

	// setup mode of operation
	MAP_TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR |  TIMER_CFG_A_PWM |
                   TIMER_CFG_B_PWM);
	MAP_TimerConfigure(WTIMER1_BASE, TIMER_CFG_SPLIT_PAIR |  TIMER_CFG_A_PWM |
                   TIMER_CFG_B_PWM);
	MAP_TimerConfigure(WTIMER5_BASE, TIMER_CFG_SPLIT_PAIR |  TIMER_CFG_A_PWM |
                   TIMER_CFG_B_PWM);

	//Pin Config
	MAP_GPIOPinTypeTimer(GPIO_PORTC_BASE, 0xF0);  //PC 4 5 6 7
	MAP_GPIOPinTypeTimer(GPIO_PORTD_BASE, 0xC0);  //PD 6 7

	MAP_GPIOPinConfigure(GPIO_PC4_WT0CCP0);
	MAP_GPIOPinConfigure(GPIO_PC5_WT0CCP1);
	MAP_GPIOPinConfigure(GPIO_PC6_WT1CCP0);
	MAP_GPIOPinConfigure(GPIO_PC7_WT1CCP1);
	MAP_GPIOPinConfigure(GPIO_PD6_WT5CCP0);
	MAP_GPIOPinConfigure(GPIO_PD7_WT5CCP1);
    
}

void pwm_init_channel(int ch_id, unsigned int freq, int invert, int control)
{
	unsigned long base, timer, load;

	if (ch_id>6 || ch_id<1)
        return;
    
    base = PWM_BASE_TABLE[ch_id-1];
    timer = PWM_TIMER_TABLE[ch_id-1];   

    if (control == PWM_CTRL_ENABLE)
    {
        load = MAP_SysCtlClockGet() / freq -1;//+ 1;

        MAP_TimerLoadSet(base, timer, load);
        MAP_TimerMatchSet(base, timer, 0);
        MAP_TimerControlLevel(base, timer, invert);
        MAP_TimerEnable(base, timer);
    }else
    {
        MAP_TimerDisable(base, timer);
    }
}

//  100% <===> percentX = PWM_PERCENT_MULTIPLIER*100;
void pwm_set_channel(int ch_id, unsigned int percentX)
{
	unsigned long base, timer, load;

	if (ch_id>6 || ch_id<1)
        return;
    
    base = PWM_BASE_TABLE[ch_id-1];
    timer = PWM_TIMER_TABLE[ch_id-1];   
    
    if (percentX>PWM_PERCENT_MULTIPLIER*100)
    {
        percentX = PWM_PERCENT_MULTIPLIER*100;
    }

	load = MAP_TimerLoadGet(base, timer);
	MAP_TimerMatchSet(base, timer, (load / (PWM_PERCENT_MULTIPLIER*100) * percentX )+
								   (load % (PWM_PERCENT_MULTIPLIER*100) * percentX / (PWM_PERCENT_MULTIPLIER*100)));
}


void pwm_set_channel_f(int ch_id, float percent)
{
	unsigned long base, timer, load;

	if (ch_id>6 || ch_id<1)
        return;
    
    base = PWM_BASE_TABLE[ch_id-1];
    timer = PWM_TIMER_TABLE[ch_id-1];   
    
    if (percent>100.0f)
        percent =100.0f;
    else if (percent<0.0f)
        percent =0.0f;
    
    percent /= 100.0f;
    
	load = MAP_TimerLoadGet(base, timer);
	MAP_TimerMatchSet(base, timer, (unsigned long)(((float)load) * percent));
}

//call this once only at initialization
void pwm_set_pd6_clk()
{
	MAP_TimerLoadSet(WTIMER5_BASE, TIMER_A, 15);
	MAP_TimerMatchSet(WTIMER5_BASE, TIMER_A, 7);
	MAP_TimerControlLevel(WTIMER5_BASE, TIMER_A, 0);
	MAP_TimerEnable(WTIMER5_BASE, TIMER_A);
}

void pwm_shutdown()
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	//Ground all PWM pins! 
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, 0xF0);//PC 4 5 6 7
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 0xC0);//PD 6 7
	MAP_GPIOPinWrite(GPIO_PORTC_BASE,  0xF0, 0);//PC 4 5 6 7
    MAP_GPIOPinWrite(GPIO_PORTD_BASE,  0xC0, 0);//PD 6 7
}

//////////////// ADC SPECIFIC //////////////////////////////////////
static int adc_fetched[2];
static unsigned long adc_buffer[2][4];

void adc_init()
{
	// device global initialization
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    system_delay_ms(1); //without this may cause faultISR
	MAP_ADCHardwareOversampleConfigure(ADC0_BASE, 0);
	MAP_ADCSequenceDisable(ADC0_BASE, 0);
    
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    system_delay_ms(1);//without this may cause faultISR
	MAP_ADCHardwareOversampleConfigure(ADC1_BASE, 0);
	MAP_ADCSequenceDisable(ADC1_BASE, 0);

    // 250ksps sample rate
	MAP_SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);

    // pin initialization
	MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, 0x3F); //PE0-PE5 = AIN 0-3 8-9
	MAP_GPIOPinTypeADC(GPIO_PORTB_BASE, 0x30); //PB4-PE5 = AIN 10 11

    // Sample sequence setup
    //ADC0 get AIN 0 1 2 3 at seq-0
	MAP_ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	MAP_ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0);
	MAP_ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1);
	MAP_ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH2);
	MAP_ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH3 | ADC_CTL_IE |    ADC_CTL_END);

    //ADC1 get AIN 8 9 10 11 at seq-0
	MAP_ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	MAP_ADCSequenceStepConfigure(ADC1_BASE, 0, 0, ADC_CTL_CH8);
	MAP_ADCSequenceStepConfigure(ADC1_BASE, 0, 1, ADC_CTL_CH9);
	MAP_ADCSequenceStepConfigure(ADC1_BASE, 0, 2, ADC_CTL_CH10);
	MAP_ADCSequenceStepConfigure(ADC1_BASE, 0, 3, ADC_CTL_CH11 | ADC_CTL_IE |   ADC_CTL_END);

    // Final steps in init
	MAP_ADCSequenceEnable(ADC0_BASE, 0);
	MAP_ADCIntClear(ADC0_BASE, 0);

	MAP_ADCSequenceEnable(ADC1_BASE, 0);
	MAP_ADCIntClear(ADC1_BASE, 0);
}

void adc_trigger()
{
	MAP_ADCIntClear(ADC0_BASE, 0);
	MAP_ADCIntClear(ADC1_BASE, 0);

	adc_fetched[0] = adc_fetched[1] = 0;

	//Trig seq-0 of both adc
	MAP_ADCProcessorTrigger(ADC0_BASE, 0);
	MAP_ADCProcessorTrigger(ADC1_BASE, 0);
}

// ch_id means channel ID is a value from 1-8
// ch_id is not AIN channel value
unsigned int adc_get_channel(int ch_id)
{
	unsigned int value = 0;
	if (ch_id > 0 && ch_id <= 4)
	{
		if (!adc_fetched[0])
		{
			while(!MAP_ADCIntStatus(ADC0_BASE, 0, false))
			{
			}
			MAP_ADCSequenceDataGet(ADC0_BASE, 0, adc_buffer[0]);
			MAP_ADCIntClear(ADC0_BASE, 0);
			adc_fetched[0] = 1;
		}
		value = adc_buffer[0][ch_id-1] & 0xFFF;
	} else if (ch_id > 4 && ch_id <= 8)
	{
		if (!adc_fetched[1])
		{
			while(!MAP_ADCIntStatus(ADC1_BASE, 0, false))
			{
			}
			MAP_ADCSequenceDataGet(ADC1_BASE, 0, adc_buffer[1]);
			MAP_ADCIntClear(ADC1_BASE, 0);
			adc_fetched[1] = 1;
		}
		value = adc_buffer[1][ch_id-5] & 0xFFF;
	}
	return value;
}

unsigned int adc_get_channel_mV(int ch_id)
{
	// assume 3.3v VREF
	return (adc_get_channel(ch_id) * 3300) / 4096;
}

///////////////////////////////////////////////////////////////////////////
//   2
//  I C    Functions 
//
///////////////////////////////////////////////////////////////////////////

void i2c_init(void)
{
	I2CSetup(I2C_DEFAULT, I2C_INIT_PIN|I2C_INIT_LOGIC|I2C_INIT_400Kbps); //true means 400kbps false means 100kbps.
}
void i2c_reset(void)
{
    I2CSetup(I2C_DEFAULT, I2C_INIT_LOGIC|I2C_INIT_RESET|I2C_INIT_400Kbps);
}

int i2c_readbytes(unsigned char dev, unsigned char reg, unsigned int length, unsigned char* data)//, unsigned int timeout=0)
{
	// timeout not yet considered
	int ret;
	ret = (int) I2CReadData(I2C_DEFAULT, dev, reg, (char*)data, length);
	return ret;
}

int i2c_readbyte(unsigned char dev, unsigned char reg, unsigned char* data)//, unsigned int timeout=0)
{
	return i2c_readbytes(dev, reg, 1, data);
}

int i2c_readbits(unsigned char dev, unsigned char reg,  int start, int length, unsigned char *data)//, unsigned int timeout=0)
{
    int ret;
    unsigned char c;
    if ((ret = i2c_readbyte(dev, reg, &c)) != 0) {
        unsigned char mask = ((1 << length) - 1) << (start - length + 1);
        c &= mask;
        c >>= (start - length + 1);
        *data = c;
    }
    return ret;
}

int i2c_writebytes(unsigned char dev, unsigned char reg, unsigned int length, unsigned char* data)
{
	int ret;
	ret = (int)  I2CWriteData(I2C_DEFAULT, dev, reg, (char*)data, length);
	return ret;
}

int i2c_writebyte(unsigned char dev, unsigned char reg, unsigned char data)
{
	//return i2c_writebytes(dev, reg, 1, &data);

	return (int)I2CRegWrite(I2C_DEFAULT, dev, reg,  data);
}

int i2c_writebits(unsigned char dev, unsigned char reg,  int start, int length, unsigned char data)
{
	unsigned char c;
    if (i2c_readbyte(dev, reg, &c) != 0)
    {
        unsigned char mask = ((1 << length) - 1) << (start - length + 1);
        data <<= (start - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        c &= ~(mask); // zero all important bits in existing byte
        c |= data; // combine data with existing byte
        return i2c_writebyte(dev, reg, c);
    } else {
        return 0;
    }
}

int i2c_writebit(unsigned char dev, unsigned char reg, int start, int data) 
{
	unsigned char c;
    if (i2c_readbyte(dev, reg, &c) != 0)
    {
		c = (data != 0) ? (c | (1 << start)) : (c & ~(1 << start));
		return i2c_writebyte(dev, reg, c);
	} else {
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////
//   
//  Console Function
//
///////////////////////////////////////////////////////////////////////////

void console_init()
{
    static  unsigned char in_buf [CONSOLE_N_IN_BUF];
    static  unsigned char out_buf[CONSOLE_N_OUT_BUF];
    
    uart_port_open(CONSOLE_PORT, in_buf, CONSOLE_N_IN_BUF, out_buf, CONSOLE_N_OUT_BUF);
      
    xdev_out(console_putc);
    xprintf("Print Enabled\n");
    //uart_port_write_one(CONSOLE_PORT, (unsigned char *)"1");
}

void console_putc(char c)
{
    uart_port_write_one(CONSOLE_PORT, (unsigned char *)&c);
}

///////////////////////////////////////////////////////////////////////////
//   
//  Systick functions
//
///////////////////////////////////////////////////////////////////////////

void systick_init(float step_size)
{
	MAP_IntPrioritySet(FAULT_SYSTICK, 0xC0);
	MAP_SysTickPeriodSet( MAP_SysCtlClockGet() * step_size );

	systick_intr_enable();

    MAP_SysTickEnable();
}

void systick_intr_enable()
{
	MAP_SysTickIntEnable();
}

void systick_intr_disable()
{
	MAP_SysTickIntDisable();
}


void tick_init(float step_size)
{
    //
    // Enable the timer which runs our application
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Configure the 32-bit periodic timer.
    //
    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, MAP_SysCtlClockGet() * step_size);
    
    //
    // Setup the interrupt for the timer timeout.
    //
    MAP_IntEnable(INT_TIMER0A);
    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    //
    // Enable the timer.
    //
    MAP_TimerEnable(TIMER0_BASE, TIMER_A);

}

void check_overrun()
{
    //
    // If the Timer0A already timeout after the process, there is a overrun
    // condition.
    //
    if (MAP_TimerIntStatus(TIMER0_BASE,false) & TIMER_TIMA_TIMEOUT)
    {
        // over run!! disable timer and stuck here.
        MAP_IntMasterDisable();
        MAP_TimerDisable(TIMER0_BASE, TIMER_A);
        while(1)
        {
          led_debug_signal(1);
        }
    }
}

void SysTickIntHandler(void)
{
    ExitIsrAndRun(tick_handler);
    //tick_handler();
}

void SvcCallHandler(void)
{
    ExitIsrAndRun_SVC();
}


#if TICK_DEBUG
volatile long long tick_count = ~0;
volatile long long tick_pause = ~0;
#endif

void tick_handler(void)
{
#if TICK_DEBUG
    if (++tick_count == tick_pause)
    {
        systick_intr_disable();
        while(tick_count == tick_pause);
        systick_intr_enable();
    }
#endif
    //
    // Trigger ADC
    //
    adc_trigger();

    //
    // Run the application step function
    //
    systick_intr_disable();
    rt_OneStep();
    //rt_OneStepM();    
    systick_intr_enable();
    // if overrun, alert user and stop
    // check_overrun();
}

void tick_error_halt(void)
{
    MAP_IntMasterDisable();
    led_debug_signal(LED_DEBUG_REENTRANCE);
}

// void test_function(void)
// {
//     float a=1.1f;
//     xprintf("xxx %d", a);
// }
