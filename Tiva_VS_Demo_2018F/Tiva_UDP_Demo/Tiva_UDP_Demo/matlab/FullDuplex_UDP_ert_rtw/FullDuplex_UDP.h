/*
 * Academic Student License -- for use by students to meet course
 * requirements and perform academic research at degree granting
 * institutions only.  Not for government, commercial, or other
 * organizational use.
 *
 * File: FullDuplex_UDP.h
 *
 * Code generated for Simulink model 'FullDuplex_UDP'.
 *
 * Model version                  : 1.87
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Oct 10 10:33:41 2018
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

#ifndef RTW_HEADER_FullDuplex_UDP_h_
#define RTW_HEADER_FullDuplex_UDP_h_
#include <string.h>
#include <stddef.h>
#ifndef FullDuplex_UDP_COMMON_INCLUDES_
# define FullDuplex_UDP_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "datapacket.h"
#include "lct_wrapper.h"
#endif                                 /* FullDuplex_UDP_COMMON_INCLUDES_ */

#include "FullDuplex_UDP_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real32_T Unpack[2];                  /* '<Root>/Unpack' */
  int_T Unpack_IWORK[2];               /* '<Root>/Unpack' */
  int_T Pack_IWORK[4];                 /* '<S1>/Pack' */
  int_T Pack_IWORK_m[4];               /* '<Root>/Pack' */
  uint8_T Pack[8];                     /* '<S1>/Pack' */
  uint8_T Pack_i[8];                   /* '<Root>/Pack' */
  uint8_T In1[8];                      /* '<S3>/In1' */
} DW_FullDuplex_UDP;

/* Parameters (auto storage) */
struct P_FullDuplex_UDP_ {
  int32_T SFunction_p1;                /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S2>/S-Function'
                                        */
  int32_T SFunction_p3;                /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S2>/S-Function'
                                        */
  int32_T MPComSend_p1;                /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<Root>/MPComSend'
                                        */
  int32_T MPComSend_p2;                /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<Root>/MPComSend'
                                        */
  uint8_T Out1_Y0;                     /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S3>/Out1'
                                        */
  uint8_T DebugPrint2_sfcn_p1[15];     /* Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
                                        * Referenced by: '<S1>/DebugPrint2_sfcn'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_FullDuplex_UDP {
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_FullDuplex_UDP FullDuplex_UDP_P;

/* Block signals and states (auto storage) */
extern DW_FullDuplex_UDP FullDuplex_UDP_DW;

/* Model entry point functions */
extern void FullDuplex_UDP_initialize(void);
extern void FullDuplex_UDP_step(void);
extern void FullDuplex_UDP_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FullDuplex_UDP *const FullDuplex_UDP_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FullDuplex_UDP'
 * '<S1>'   : 'FullDuplex_UDP/Advanced Debug Print'
 * '<S2>'   : 'FullDuplex_UDP/MPComRecv'
 * '<S3>'   : 'FullDuplex_UDP/MPComRecv/Enabled Subsystem'
 */

/*-
 * Requirements for '<Root>': FullDuplex_UDP
 */
#endif                                 /* RTW_HEADER_FullDuplex_UDP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
