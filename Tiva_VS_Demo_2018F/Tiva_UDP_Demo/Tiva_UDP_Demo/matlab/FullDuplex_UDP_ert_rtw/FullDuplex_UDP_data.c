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
 * Model version                  : 1.87
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Oct 10 10:54:26 2018
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
  2,                                   /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S3>/S-Function'
                                        */
  0,                                   /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S3>/S-Function'
                                        */
  3,                                   /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<S1>/MPComSend'
                                        */
  0,                                   /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<S1>/MPComSend'
                                        */
  0U,                                  /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S4>/Out1'
                                        */

  /*  Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
   * Referenced by: '<S2>/DebugPrint2_sfcn'
   */
  { 86U, 83U, 58U, 32U, 37U, 104U, 102U, 44U, 32U, 37U, 104U, 102U, 13U, 10U, 0U
  }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
