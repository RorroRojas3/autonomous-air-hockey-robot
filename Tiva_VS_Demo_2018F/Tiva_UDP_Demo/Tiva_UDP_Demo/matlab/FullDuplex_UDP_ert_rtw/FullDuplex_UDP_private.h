/*
 * Academic Student License -- for use by students to meet course
 * requirements and perform academic research at degree granting
 * institutions only.  Not for government, commercial, or other
 * organizational use.
 *
 * File: FullDuplex_UDP_private.h
 *
 * Code generated for Simulink model 'FullDuplex_UDP'.
 *
 * Model version                  : 1.107
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Tue Nov 13 19:06:57 2018
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

#ifndef RTW_HEADER_FullDuplex_UDP_private_h_
#define RTW_HEADER_FullDuplex_UDP_private_h_
#include "rtwtypes.h"
#include "FullDuplex_UDP.h"

extern void FullDuplex_UD_XSteptoPulse_Init(DW_XSteptoPulse_FullDuplex_UDP
  *localDW, P_XSteptoPulse_FullDuplex_UDP *localP);
extern void FullDuplex_U_XSteptoPulse_Start(DW_XSteptoPulse_FullDuplex_UDP
  *localDW);
extern real32_T FullDuplex_UDP_XSteptoPulse(real_T rtu_Steps, uint8_T rtu_In1,
  DW_XSteptoPulse_FullDuplex_UDP *localDW, P_XSteptoPulse_FullDuplex_UDP *localP);

#endif                                 /* RTW_HEADER_FullDuplex_UDP_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
