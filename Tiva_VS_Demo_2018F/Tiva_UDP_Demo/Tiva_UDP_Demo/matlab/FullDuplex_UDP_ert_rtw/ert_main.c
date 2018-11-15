/*
 * Academic Student License -- for use by students to meet course
 * requirements and perform academic research at degree granting
 * institutions only.  Not for government, commercial, or other
 * organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'FullDuplex_UDP'.
 *
 * Model version                  : 1.134
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Nov 14 17:43:46 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. ROM efficiency
 *    3. RAM efficiency
 *    4. Traceability
 *    5. Safety precaution
 *    6. Debugging
 *    7. MISRA C:2012 guidelines
 *    8. Polyspace
 * Validation result: Not run
 */

#include "FullDuplex_UDP.h"
#include "rtwtypes.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  systick_intr_enable();
  FullDuplex_UDP_step();

  /* Get model outputs here */
  systick_intr_disable();
  OverrunFlag--;
}

int main(int argc, char **argv)
{
  volatile boolean_T runModel = 1;
  float modelBaseRate = 0.0002;
  float systemClock = 100;
  system_init();
  ((void) 0);
  FullDuplex_UDP_initialize();
  systick_init(modelBaseRate);
  systick_intr_enable();
  while (runModel) {
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  FullDuplex_UDP_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
