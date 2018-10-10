/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'Fullduplex'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 19 2013)
 * C/C++ source code generated on : Tue Apr 21 17:49:08 2015
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Fullduplex.h"

//#include "inc/hw_ints.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_types.h"
//#include "driverlib/debug.h"
//#include "driverlib/fpu.h"
//#include "driverlib/gpio.h"
//#include "driverlib/interrupt.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/rom.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/timer.h"
#include "stellaris_runtime.h"
#define STEP_SIZE                      0.005f
#define OverrunFlag                    IsrOverrun

volatile int IsrOverrun = 0;
volatile boolean_T isRateRunning[3] = { 0, 0, 0 };

volatile boolean_T need2runFlags[3] = { 0, 0, 0 };

void rt_OneStep()
{
  /* Disable interrupts here */

  /* Check for overun */
  if (OverrunFlag++) {
    rtmSetErrorStatus(Fullduplex_M, "Overrun");
    return;
  }

  //led_debug_signal(LED_DEBUG_ALL_ON);

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  systick_intr_enable();
  Fullduplex_output();

  /* Get model outputs here */
  Fullduplex_update();
  systick_intr_disable();

  //led_debug_signal(LED_DEBUG_ALL_OFF);
  OverrunFlag--;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

int_T main(int_T argc, const char_T *argv[])
{
  volatile boolean_T noErr;
  system_init();

  /* Initialize model */
  /* Model initialization might involve enabling of some peripherals.
   * I discovered that it must happen after IntMasterEnable(); otherwise
   * I get non-deterministic behaviour. For example, UART Read may return
   * bogus values after power cycle */
  Fullduplex_initialize();
  systick_init(STEP_SIZE);

  //
  // Loop forever while the timer is running.
  //
  do {
    noErr =
      (rtmGetErrorStatus(Fullduplex_M) == (NULL));
  } while ( noErr );

  systick_intr_disable();
  Fullduplex_terminate();
  if (IsrOverrun) {
    led_debug_signal(LED_DEBUG_OVERRUN);

    /* program will hang here */
  } else {
    system_safe();
    system_delay_ms(300);
    system_reset();
  }

  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
