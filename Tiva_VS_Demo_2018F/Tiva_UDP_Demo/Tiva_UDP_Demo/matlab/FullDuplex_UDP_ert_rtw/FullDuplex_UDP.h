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

#ifndef RTW_HEADER_FullDuplex_UDP_h_
#define RTW_HEADER_FullDuplex_UDP_h_
#include <string.h>
#include <stddef.h>
#ifndef FullDuplex_UDP_COMMON_INCLUDES_
# define FullDuplex_UDP_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "datapacket.h"
#include "gpiolct.h"
#include "lct_wrapper.h"
#endif                                 /* FullDuplex_UDP_COMMON_INCLUDES_ */

#include "FullDuplex_UDP_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real32_T Unpack[2];                  /* '<S1>/Unpack' */
  real32_T Memory_PreviousInput;       /* '<S7>/Memory' */
  int_T Unpack_IWORK[2];               /* '<S1>/Unpack' */
  int_T Pack_IWORK[4];                 /* '<S4>/Pack' */
  int_T Pack_IWORK_o[4];               /* '<S1>/Pack' */
  int32_T clockTickCounter;            /* '<S8>/Pulse Generator' */
  uint32_T Counter_ClkEphState;        /* '<S2>/Counter' */
  uint8_T Pack[8];                     /* '<S4>/Pack' */
  uint8_T Pack_n[8];                   /* '<S1>/Pack' */
  uint8_T In1[8];                      /* '<S6>/In1' */
  uint8_T Counter_Count;               /* '<S2>/Counter' */
} DW_FullDuplex_UDP;

/* Parameters (auto storage) */
struct P_FullDuplex_UDP_ {
  uint8_T Counter_InitialCount;        /* Mask Parameter: Counter_InitialCount
                                        * Referenced by: '<S2>/Counter'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 50
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<S8>/Pulse Generator'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  real32_T Memory_X0;                  /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S7>/Memory'
                                        */
  int32_T SFunction_p1;                /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S5>/S-Function'
                                        */
  int32_T SFunction_p3;                /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S5>/S-Function'
                                        */
  int32_T SFunction2_p1;               /* Expression: int32(ch)
                                        * Referenced by: '<S9>/S-Function2'
                                        */
  int32_T SFunction2_p3;               /* Expression: int32(invert-1)
                                        * Referenced by: '<S9>/S-Function2'
                                        */
  int32_T MPComSend_p1;                /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<S1>/MPComSend'
                                        */
  int32_T MPComSend_p2;                /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<S1>/MPComSend'
                                        */
  uint32_T GPIOWrite_p1;               /* Computed Parameter: GPIOWrite_p1
                                        * Referenced by: '<S3>/GPIO Write'
                                        */
  uint32_T SFunction2_p2;              /* Expression: uint32(freq)
                                        * Referenced by: '<S9>/S-Function2'
                                        */
  uint32_T GPIOSetup1_p1;              /* Computed Parameter: GPIOSetup1_p1
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  uint32_T GPIOSetup1_p2;              /* Computed Parameter: GPIOSetup1_p2
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  uint8_T Out1_Y0;                     /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S6>/Out1'
                                        */
  uint8_T GPIOPinSelect_Value;         /* Computed Parameter: GPIOPinSelect_Value
                                        * Referenced by: '<S3>/GPIO Pin Select'
                                        */
  uint8_T Gain_Gain;                   /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S3>/Gain'
                                        */
  uint8_T GPIOSetup1_p3;               /* Computed Parameter: GPIOSetup1_p3
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  uint8_T GPIOSetup1_p4;               /* Computed Parameter: GPIOSetup1_p4
                                        * Referenced by: '<S3>/GPIO Setup1'
                                        */
  uint8_T DebugPrint2_sfcn_p1[13];     /* Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
                                        * Referenced by: '<S4>/DebugPrint2_sfcn'
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
      uint16_T TID[2];
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
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 */

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
 * '<S1>'   : 'FullDuplex_UDP/UDP RECEIVE'
 * '<S2>'   : 'FullDuplex_UDP/X Step to Pulse'
 * '<S3>'   : 'FullDuplex_UDP/X-Axis'
 * '<S4>'   : 'FullDuplex_UDP/UDP RECEIVE/Advanced Debug Print'
 * '<S5>'   : 'FullDuplex_UDP/UDP RECEIVE/MPComRecv'
 * '<S6>'   : 'FullDuplex_UDP/UDP RECEIVE/MPComRecv/Enabled Subsystem'
 * '<S7>'   : 'FullDuplex_UDP/X Step to Pulse/Hold'
 * '<S8>'   : 'FullDuplex_UDP/X Step to Pulse/PWM2'
 * '<S9>'   : 'FullDuplex_UDP/X-Axis/PWM Output X-Axis'
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
