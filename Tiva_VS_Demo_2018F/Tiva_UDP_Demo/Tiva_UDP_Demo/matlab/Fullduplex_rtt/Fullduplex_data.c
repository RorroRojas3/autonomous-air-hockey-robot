/*
 * File: Fullduplex_data.c
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
#include "Fullduplex_private.h"

/* Block parameters (auto storage) */
P_Fullduplex_T Fullduplex_P = {
  10.0,                                /* Expression: 10
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  0.01,                                /* Expression: .01
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  3.1415F,                             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<Root>/Constant'
                                        */
  2,                                   /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S2>/S-Function'
                                        */
  0,                                   /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S2>/S-Function'
                                        */
  3,                                   /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<Root>/MPComSend'
                                        */
  0,                                   /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<Root>/MPComSend'
                                        */

  /*  Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
   * Referenced by: '<S1>/DebugPrint2_sfcn'
   */
  { 83U, 111U, 117U, 114U, 99U, 101U, 32U, 61U, 37U, 104U, 102U, 13U, 10U, 32U,
    70U, 114U, 111U, 109U, 32U, 84U, 105U, 118U, 97U, 32U, 61U, 37U, 104U, 102U,
    13U, 10U, 32U, 68U, 105U, 102U, 102U, 101U, 114U, 101U, 110U, 99U, 101U, 32U,
    61U, 37U, 104U, 102U, 13U, 10U, 32U, 67U, 111U, 110U, 115U, 116U, 97U, 110U,
    116U, 32U, 61U, 37U, 104U, 102U, 13U, 10U, 10U, 0U }
};

/* Constant parameters (auto storage) */
const ConstP_Fullduplex_T Fullduplex_ConstP = {
  /* Pooled Parameter (Expression: pack_size)
   * Referenced by:
   *   '<Root>/MPComSend'
   *   '<S2>/S-Function'
   */
  8
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
