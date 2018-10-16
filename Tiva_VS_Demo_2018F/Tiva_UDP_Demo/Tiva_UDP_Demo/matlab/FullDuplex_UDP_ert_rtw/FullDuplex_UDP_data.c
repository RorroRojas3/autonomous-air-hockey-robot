/*
 * Academic Student License -- for use by students to meet course
 * requirements and perform academic research at degree granting
 * institutions only.  Not for government, commercial, or other
 * organizational use.
 *
 * File: FullDuplex_UDP_data.c
 *
 * Code generated for Simulink model 'FullDuplex_UDP'.
 *
 * Model version                  : 1.93
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Oct 16 13:03:49 2018
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
#include "FullDuplex_UDP_private.h"

/* Block parameters (auto storage) */
P_FullDuplex_UDP FullDuplex_UDP_P = {
  0U,                                  /* Mask Parameter: Counter_InitialCount
                                        * Referenced by: '<S2>/Counter'
                                        */
  50.0,                                /* Expression: 50
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  500.0,                               /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  490.0,                               /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S7>/Memory'
                                        */
  2,                                   /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S5>/S-Function'
                                        */
  0,                                   /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S5>/S-Function'
                                        */
  1,                                   /* Expression: int32(ch)
                                        * Referenced by: '<S9>/S-Function2'
                                        */
  -1,                                  /* Expression: int32(invert-1)
                                        * Referenced by: '<S9>/S-Function2'
                                        */
  3,                                   /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<S1>/MPComSend'
                                        */
  0,                                   /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<S1>/MPComSend'
                                        */
  1073766400U,                         /* Computed Parameter: GPIOWrite_p1
                                        * Referenced by: '<S3>/GPIO Write'
                                        */
  500U,                                /* Expression: uint32(freq)
                                        * Referenced by: '<S9>/S-Function2'
                                        */
  536870916U,                          /* Computed Parameter: GPIOSetup1_p1
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  1073766400U,                         /* Computed Parameter: GPIOSetup1_p2
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  0U,                                  /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S6>/Out1'
                                        */
  128U,                                /* Computed Parameter: GPIOPinSelect_Value
                                        * Referenced by: '<S3>/GPIO Pin Select'
                                        */
  128U,                                /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S3>/Gain'
                                        */
  128U,                                /* Computed Parameter: GPIOSetup1_p3
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  0U,                                  /* Computed Parameter: GPIOSetup1_p4
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */

  /*  Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
   * Referenced by: '<S4>/DebugPrint2_sfcn'
   */
  { 88U, 58U, 32U, 37U, 104U, 102U, 32U, 37U, 104U, 102U, 13U, 10U, 0U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
