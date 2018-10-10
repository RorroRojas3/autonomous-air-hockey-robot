/*
 * File: Fullduplex.h
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

#ifndef RTW_HEADER_Fullduplex_h_
#define RTW_HEADER_Fullduplex_h_
#ifndef Fullduplex_COMMON_INCLUDES_
# define Fullduplex_COMMON_INCLUDES_
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "datapacket.h"
#include "lct_wrapper.h"
#endif                                 /* Fullduplex_COMMON_INCLUDES_ */

#include "Fullduplex_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T SineWave;                     /* '<Root>/Sine Wave' */
  real32_T DataTypeConversion1;        /* '<Root>/Data Type Conversion1' */
  real32_T Unpack[2];                  /* '<Root>/Unpack' */
  real32_T Sum;                        /* '<Root>/Sum' */
  int32_T SFunction_o2;                /* '<S2>/S-Function' */
  int32_T MPComSend;                   /* '<Root>/MPComSend' */
  uint8_T SFunction_o1[8];             /* '<S2>/S-Function' */
  uint8_T Pack[16];                    /* '<S1>/Pack' */
  uint8_T Pack_m[8];                   /* '<Root>/Pack' */
  uint8_T In1[8];                      /* '<S3>/In1' */
} B_Fullduplex_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  boolean_T EnabledSubsystem_MODE;     /* '<S2>/Enabled Subsystem' */
} DW_Fullduplex_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Pooled Parameter (Expression: pack_size)
   * Referenced by:
   *   '<Root>/MPComSend'
   *   '<S2>/S-Function'
   */
  int32_T pooled1;
} ConstP_Fullduplex_T;

/* Parameters (auto storage) */
struct P_Fullduplex_T_ {
  real_T SineWave_Amp;                 /* Expression: 10
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T SineWave_Bias;                /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T SineWave_Freq;                /* Expression: .01
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real_T SineWave_Phase;               /* Expression: 0
                                        * Referenced by: '<Root>/Sine Wave'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<Root>/Constant'
                                        */
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
  uint8_T DebugPrint2_sfcn_p1[66];     /* Expression: uint8([sprintf(strrep(fmt,'%','%%')) 0])
                                        * Referenced by: '<S1>/DebugPrint2_sfcn'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Fullduplex_T {
  const char_T * volatile errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_Fullduplex_T Fullduplex_P;

/* Block signals (auto storage) */
extern B_Fullduplex_T Fullduplex_B;

/* Block states (auto storage) */
extern DW_Fullduplex_T Fullduplex_DW;

/* Constant parameters (auto storage) */
extern const ConstP_Fullduplex_T Fullduplex_ConstP;

/* Model entry point functions */
extern void Fullduplex_initialize(void);
extern void Fullduplex_output(void);
extern void Fullduplex_update(void);
extern void Fullduplex_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Fullduplex_T *const Fullduplex_M;

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
 * '<Root>' : 'Fullduplex'
 * '<S1>'   : 'Fullduplex/Advanced Debug Print'
 * '<S2>'   : 'Fullduplex/MPComRecv'
 * '<S3>'   : 'Fullduplex/MPComRecv/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_Fullduplex_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
