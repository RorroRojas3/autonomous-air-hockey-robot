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
 * Model version                  : 1.148
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Mon Nov 26 17:56:29 2018
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

/* Block signals and states (auto storage) for system '<Root>/X Step to Pulse' */
typedef struct {
  real32_T Memory_PreviousInput;       /* '<S12>/Memory' */
  int32_T clockTickCounter;            /* '<S13>/Pulse Generator' */
  uint32_T Counter_ClkEphState;        /* '<S4>/Counter' */
  uint8_T Counter_Count;               /* '<S4>/Counter' */
} DW_XSteptoPulse_FullDuplex_UDP;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  DW_XSteptoPulse_FullDuplex_UDP YSteptoPulse;/* '<Root>/Y Step to Pulse' */
  DW_XSteptoPulse_FullDuplex_UDP XSteptoPulse;/* '<Root>/X Step to Pulse' */
  real_T UniformRandomNumber_NextOutput;/* '<S1>/Uniform Random Number' */
  real32_T Unpack[6];                  /* '<S2>/Unpack' */
  real32_T steps;                      /* '<Root>/Y Movement' */
  real32_T steps_f;                    /* '<Root>/X Movement' */
  int_T Unpack_IWORK[2];               /* '<S2>/Unpack' */
  int_T Pack_IWORK[12];                /* '<S9>/Pack' */
  int_T Pack_IWORK_o[12];              /* '<S2>/Pack' */
  uint32_T RandSeed;                   /* '<S1>/Uniform Random Number' */
  uint8_T Pack[24];                    /* '<S9>/Pack' */
  uint8_T Pack_n[24];                  /* '<S2>/Pack' */
  uint8_T In1[24];                     /* '<S11>/In1' */
  uint8_T SFunction_o1[24];            /* '<S10>/S-Function' */
  uint8_T y_motor;                     /* '<Root>/Y Movement' */
  uint8_T y_dir;                       /* '<Root>/Y Movement' */
  uint8_T x_motor;                     /* '<Root>/X Movement' */
  uint8_T x_dir;                       /* '<Root>/X Movement' */
  uint8_T is_active_c3_FullDuplex_UDP; /* '<Root>/Y Movement' */
  uint8_T is_c3_FullDuplex_UDP;        /* '<Root>/Y Movement' */
  uint8_T is_active_c2_FullDuplex_UDP; /* '<Root>/X Movement' */
  uint8_T is_c2_FullDuplex_UDP;        /* '<Root>/X Movement' */
} DW_FullDuplex_UDP;

/* Parameters for system: '<Root>/X Step to Pulse' */
struct P_XSteptoPulse_FullDuplex_UDP_ {
  uint8_T Counter_InitialCount;        /* Mask Parameter: Counter_InitialCount
                                        * Referenced by: '<S4>/Counter'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 50
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<S13>/Pulse Generator'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S4>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real32_T Memory_X0;                  /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S12>/Memory'
                                        */
  real32_T Switch2_Threshold;          /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S4>/Switch2'
                                        */
};

/* Parameters (auto storage) */
struct P_FullDuplex_UDP_ {
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T UniformRandomNumber_Minimum;  /* Expression: 0
                                        * Referenced by: '<S1>/Uniform Random Number'
                                        */
  real_T UniformRandomNumber_Maximum;  /* Expression: 2
                                        * Referenced by: '<S1>/Uniform Random Number'
                                        */
  real_T UniformRandomNumber_Seed;     /* Expression: 0
                                        * Referenced by: '<S1>/Uniform Random Number'
                                        */
  int32_T SFunction_p1;                /* Computed Parameter: SFunction_p1
                                        * Referenced by: '<S10>/S-Function'
                                        */
  int32_T SFunction_p3;                /* Computed Parameter: SFunction_p3
                                        * Referenced by: '<S10>/S-Function'
                                        */
  int32_T SFunction2_p1;               /* Expression: int32(ch)
                                        * Referenced by: '<S14>/S-Function2'
                                        */
  int32_T SFunction2_p3;               /* Expression: int32(invert-1)
                                        * Referenced by: '<S14>/S-Function2'
                                        */
  int32_T SFunction2_p1_b;             /* Expression: int32(ch)
                                        * Referenced by: '<S17>/S-Function2'
                                        */
  int32_T SFunction2_p3_d;             /* Expression: int32(invert-1)
                                        * Referenced by: '<S17>/S-Function2'
                                        */
  int32_T SFunction2_p1_n;             /* Expression: int32(ch)
                                        * Referenced by: '<S18>/S-Function2'
                                        */
  int32_T SFunction2_p3_l;             /* Expression: int32(invert-1)
                                        * Referenced by: '<S18>/S-Function2'
                                        */
  int32_T MPComSend_p1;                /* Computed Parameter: MPComSend_p1
                                        * Referenced by: '<S2>/MPComSend'
                                        */
  int32_T MPComSend_p2;                /* Computed Parameter: MPComSend_p2
                                        * Referenced by: '<S2>/MPComSend'
                                        */
  uint32_T GPIOWrite_p1;               /* Computed Parameter: GPIOWrite_p1
                                        * Referenced by: '<S5>/GPIO Write'
                                        */
  uint32_T SFunction2_p2;              /* Expression: uint32(freq)
                                        * Referenced by: '<S14>/S-Function2'
                                        */
  uint32_T GPIOSetup1_p1;              /* Computed Parameter: GPIOSetup1_p1
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  uint32_T GPIOSetup1_p2;              /* Computed Parameter: GPIOSetup1_p2
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  uint32_T GPIOWrite_p1_n;             /* Computed Parameter: GPIOWrite_p1_n
                                        * Referenced by: '<S8>/GPIO Write'
                                        */
  uint32_T GPIOWrite1_p1;              /* Computed Parameter: GPIOWrite1_p1
                                        * Referenced by: '<S8>/GPIO Write1'
                                        */
  uint32_T SFunction2_p2_n;            /* Expression: uint32(freq)
                                        * Referenced by: '<S17>/S-Function2'
                                        */
  uint32_T SFunction2_p2_o;            /* Expression: uint32(freq)
                                        * Referenced by: '<S18>/S-Function2'
                                        */
  uint32_T GPIOSetup1_p1_l;            /* Computed Parameter: GPIOSetup1_p1_l
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  uint32_T GPIOSetup1_p2_k;            /* Computed Parameter: GPIOSetup1_p2_k
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  uint32_T GPIOSetup2_p1;              /* Computed Parameter: GPIOSetup2_p1
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  uint32_T GPIOSetup2_p2;              /* Computed Parameter: GPIOSetup2_p2
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  uint32_T GPIOWrite_p1_b;             /* Computed Parameter: GPIOWrite_p1_b
                                        * Referenced by: '<S1>/GPIO Write'
                                        */
  uint32_T GPIOSetup_p1;               /* Computed Parameter: GPIOSetup_p1
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  uint32_T GPIOSetup_p2;               /* Computed Parameter: GPIOSetup_p2
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  uint8_T Out1_Y0;                     /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S11>/Out1'
                                        */
  uint8_T GPIOPinSelect_Value;         /* Computed Parameter: GPIOPinSelect_Value
                                        * Referenced by: '<S5>/GPIO Pin Select'
                                        */
  uint8_T Gain_Gain;                   /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S5>/Gain'
                                        */
  uint8_T GPIOSetup1_p3;               /* Computed Parameter: GPIOSetup1_p3
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  uint8_T GPIOSetup1_p4;               /* Computed Parameter: GPIOSetup1_p4
                                        * Referenced by: '<S5>/GPIO Setup1'
                                        */
  uint8_T GPIOPinSelect_Value_g;       /* Computed Parameter: GPIOPinSelect_Value_g
                                        * Referenced by: '<S8>/GPIO Pin Select'
                                        */
  uint8_T Gain_Gain_n;                 /* Computed Parameter: Gain_Gain_n
                                        * Referenced by: '<S8>/Gain'
                                        */
  uint8_T Gain1_Gain;                  /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S8>/Gain1'
                                        */
  uint8_T GPIOPinSelect1_Value;        /* Computed Parameter: GPIOPinSelect1_Value
                                        * Referenced by: '<S8>/GPIO Pin Select1'
                                        */
  uint8_T GPIOSetup1_p3_m;             /* Computed Parameter: GPIOSetup1_p3_m
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  uint8_T GPIOSetup1_p4_o;             /* Computed Parameter: GPIOSetup1_p4_o
                                        * Referenced by: '<S8>/GPIO Setup1'
                                        */
  uint8_T GPIOSetup2_p3;               /* Computed Parameter: GPIOSetup2_p3
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  uint8_T GPIOSetup2_p4;               /* Computed Parameter: GPIOSetup2_p4
                                        * Referenced by: '<S8>/GPIO Setup2'
                                        */
  uint8_T DebugPrint2_sfcn_p1[33];     /* Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
                                        * Referenced by: '<S9>/DebugPrint2_sfcn'
                                        */
  uint8_T REDLED_Value;                /* Computed Parameter: REDLED_Value
                                        * Referenced by: '<S1>/RED LED'
                                        */
  uint8_T BLUELED_Value;               /* Computed Parameter: BLUELED_Value
                                        * Referenced by: '<S1>/BLUE LED'
                                        */
  uint8_T GREENLED_Value;              /* Computed Parameter: GREENLED_Value
                                        * Referenced by: '<S1>/GREEN LED'
                                        */
  uint8_T GPIOSetup_p3;                /* Computed Parameter: GPIOSetup_p3
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  uint8_T GPIOSetup_p4;                /* Computed Parameter: GPIOSetup_p4
                                        * Referenced by: '<S1>/GPIO Setup'
                                        */
  P_XSteptoPulse_FullDuplex_UDP YSteptoPulse;/* '<Root>/Y Step to Pulse' */
  P_XSteptoPulse_FullDuplex_UDP XSteptoPulse;/* '<Root>/X Step to Pulse' */
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
      uint16_T TID[3];
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
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S4>/Scope2' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S7>/Scope1' : Unused code path elimination
 * Block '<S7>/Scope2' : Unused code path elimination
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion4' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion5' : Eliminate redundant data type conversion
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
 * '<S1>'   : 'FullDuplex_UDP/Running Indicator1'
 * '<S2>'   : 'FullDuplex_UDP/UDP RECEIVE'
 * '<S3>'   : 'FullDuplex_UDP/X Movement'
 * '<S4>'   : 'FullDuplex_UDP/X Step to Pulse'
 * '<S5>'   : 'FullDuplex_UDP/X-Axis'
 * '<S6>'   : 'FullDuplex_UDP/Y Movement'
 * '<S7>'   : 'FullDuplex_UDP/Y Step to Pulse'
 * '<S8>'   : 'FullDuplex_UDP/Y-Axis'
 * '<S9>'   : 'FullDuplex_UDP/UDP RECEIVE/Advanced Debug Print'
 * '<S10>'  : 'FullDuplex_UDP/UDP RECEIVE/MPComRecv'
 * '<S11>'  : 'FullDuplex_UDP/UDP RECEIVE/MPComRecv/Enabled Subsystem'
 * '<S12>'  : 'FullDuplex_UDP/X Step to Pulse/Hold'
 * '<S13>'  : 'FullDuplex_UDP/X Step to Pulse/PWM2'
 * '<S14>'  : 'FullDuplex_UDP/X-Axis/PWM Output X-Axis'
 * '<S15>'  : 'FullDuplex_UDP/Y Step to Pulse/Hold'
 * '<S16>'  : 'FullDuplex_UDP/Y Step to Pulse/PWM2'
 * '<S17>'  : 'FullDuplex_UDP/Y-Axis/PWM Output Y-Axis (Left)'
 * '<S18>'  : 'FullDuplex_UDP/Y-Axis/PWM Output Y-Axis (Right)'
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
