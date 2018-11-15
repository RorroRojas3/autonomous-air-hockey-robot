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
#include "FullDuplex_UDP_private.h"

/* Block parameters (auto storage) */
P_FullDuplex_UDP FullDuplex_UDP_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Uniform Random Number'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S1>/Uniform Random Number'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Uniform Random Number'
                                        */
  2,                                   /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S10>/S-Function'
                                        */
  0,                                   /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S10>/S-Function'
                                        */
  1,                                   /* Expression: int32(ch)
                                        * Referenced by: '<S14>/S-Function2'
                                        */
  -1,                                  /* Expression: int32(invert-1)
                                        * Referenced by: '<S14>/S-Function2'
                                        */
  2,                                   /* Expression: int32(ch)
                                        * Referenced by: '<S17>/S-Function2'
                                        */
  -1,                                  /* Expression: int32(invert-1)
                                        * Referenced by: '<S17>/S-Function2'
                                        */
  3,                                   /* Expression: int32(ch)
                                        * Referenced by: '<S18>/S-Function2'
                                        */
  -1,                                  /* Expression: int32(invert-1)
                                        * Referenced by: '<S18>/S-Function2'
                                        */
  3,                                   /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<S2>/MPComSend'
                                        */
  0,                                   /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<S2>/MPComSend'
                                        */
  1073766400U,                         /* Computed Parameter: GPIOWrite_p1
                                        * Referenced by: '<S5>/GPIO Write'
                                        */
  3000U,                               /* Expression: uint32(freq)
                                        * Referenced by: '<S14>/S-Function2'
                                        */
  536870916U,                          /* Computed Parameter: GPIOSetup1_p1
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  1073766400U,                         /* Computed Parameter: GPIOSetup1_p2
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  1073770496U,                         /* Computed Parameter: GPIOWrite_p1_n
                                        * Referenced by: '<S8>/GPIO Write'
                                        */
  1073770496U,                         /* Computed Parameter: GPIOWrite1_p1
                                        * Referenced by: '<S8>/GPIO Write1'
                                        */
  2500U,                               /* Expression: uint32(freq)
                                        * Referenced by: '<S17>/S-Function2'
                                        */
  2500U,                               /* Expression: uint32(freq)
                                        * Referenced by: '<S18>/S-Function2'
                                        */
  536870920U,                          /* Computed Parameter: GPIOSetup1_p1_l
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  1073770496U,                         /* Computed Parameter: GPIOSetup1_p2_k
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  536870920U,                          /* Computed Parameter: GPIOSetup2_p1
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  1073770496U,                         /* Computed Parameter: GPIOSetup2_p2
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  1073893376U,                         /* Computed Parameter: GPIOWrite_p1_b
                                        * Referenced by: '<S1>/GPIO Write'
                                        */
  536870944U,                          /* Computed Parameter: GPIOSetup_p1
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  1073893376U,                         /* Computed Parameter: GPIOSetup_p2
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  0U,                                  /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S11>/Out1'
                                        */
  128U,                                /* Computed Parameter: GPIOPinSelect_Value
                                        * Referenced by: '<S5>/GPIO Pin Select'
                                        */
  128U,                                /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S5>/Gain'
                                        */
  128U,                                /* Computed Parameter: GPIOSetup1_p3
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  0U,                                  /* Computed Parameter: GPIOSetup1_p4
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  64U,                                 /* Computed Parameter: GPIOPinSelect_Value_g
                                        * Referenced by: '<S8>/GPIO Pin Select'
                                        */
  64U,                                 /* Computed Parameter: Gain_Gain_n
                                        * Referenced by: '<S8>/Gain'
                                        */
  128U,                                /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S8>/Gain1'
                                        */
  128U,                                /* Computed Parameter: GPIOPinSelect1_Value
                                        * Referenced by: '<S8>/GPIO Pin Select1'
                                        */
  64U,                                 /* Computed Parameter: GPIOSetup1_p3_m
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  0U,                                  /* Computed Parameter: GPIOSetup1_p4_o
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  128U,                                /* Computed Parameter: GPIOSetup2_p3
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  0U,                                  /* Computed Parameter: GPIOSetup2_p4
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */

  /*  Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
   * Referenced by: '<S9>/DebugPrint2_sfcn'
   */
  { 88U, 58U, 32U, 37U, 104U, 102U, 32U, 37U, 104U, 102U, 32U, 37U, 104U, 102U,
    44U, 32U, 89U, 58U, 32U, 37U, 104U, 102U, 32U, 37U, 104U, 102U, 32U, 37U,
    104U, 102U, 13U, 10U, 0U },
  2U,                                  /* Computed Parameter: REDLED_Value
                                        * Referenced by: '<S1>/RED LED'
                                        */
  4U,                                  /* Computed Parameter: BLUELED_Value
                                        * Referenced by: '<S1>/BLUE LED'
                                        */
  8U,                                  /* Computed Parameter: GREENLED_Value
                                        * Referenced by: '<S1>/GREEN LED'
                                        */
  14U,                                 /* Computed Parameter: GPIOSetup_p3
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  241U,                                /* Computed Parameter: GPIOSetup_p4
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */

  /* Start of '<Root>/Y Step to Pulse' */
  {
    0U,                                /* Mask Parameter: Counter_InitialCount
                                        * Referenced by: '<S7>/Counter'
                                        */
    50.0,                              /* Expression: 50
                                        * Referenced by: '<S16>/Pulse Generator'
                                        */
    50.0,                              /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S16>/Pulse Generator'
                                        */
    48.999999999999993,                /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S16>/Pulse Generator'
                                        */
    0.0,                               /* Expression: 0
                                        * Referenced by: '<S16>/Pulse Generator'
                                        */
    0.0F,                              /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S7>/Constant'
                                        */
    0.0F,                              /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S7>/Constant1'
                                        */
    0.0F,                              /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S15>/Memory'
                                        */
    0.0F                               /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S7>/Switch2'
                                        */
  }
  ,

  /* End of '<Root>/Y Step to Pulse' */

  /* Start of '<Root>/X Step to Pulse' */
  {
    0U,                                /* Mask Parameter: Counter_InitialCount
                                        * Referenced by: '<S4>/Counter'
                                        */
    50.0,                              /* Expression: 50
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
    50.0,                              /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
    48.999999999999993,                /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
    0.0,                               /* Expression: 0
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
    0.0F,                              /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S4>/Constant'
                                        */
    0.0F,                              /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S4>/Constant1'
                                        */
    0.0F,                              /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S12>/Memory'
                                        */
    0.0F                               /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S4>/Switch2'
                                        */
  }
  /* End of '<Root>/X Step to Pulse' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
