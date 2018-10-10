/*
 * File: Fullduplex.c
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

/* Block signals (auto storage) */
B_Fullduplex_T Fullduplex_B;

/* Block states (auto storage) */
DW_Fullduplex_T Fullduplex_DW;

/* Real-time model */
RT_MODEL_Fullduplex_T Fullduplex_M_;
RT_MODEL_Fullduplex_T *const Fullduplex_M = &Fullduplex_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Fullduplex_M->Timing.TaskCounters.TID[2])++;
  if ((Fullduplex_M->Timing.TaskCounters.TID[2]) > 19) {/* Sample time: [0.1s, 0.0s] */
    Fullduplex_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/* Model output function */
void Fullduplex_output(void)
{
  int32_T i;

  /* Sin: '<Root>/Sine Wave' */
  Fullduplex_B.SineWave = sin(Fullduplex_P.SineWave_Freq *
    Fullduplex_M->Timing.t[0] + Fullduplex_P.SineWave_Phase) *
    Fullduplex_P.SineWave_Amp + Fullduplex_P.SineWave_Bias;

  /* DataTypeConversion: '<Root>/Data Type Conversion1' */
  Fullduplex_B.DataTypeConversion1 = (real32_T)Fullduplex_B.SineWave;

  /* S-Function (stellaris_lp_sfunc_DataPackin): '<S2>/S-Function' */
  i = datapacket_get(Fullduplex_P.SFunction_p1, Fullduplex_ConstP.pooled1,
                     Fullduplex_B.SFunction_o1);
  Fullduplex_B.SFunction_o2 = i;

  /* Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (Fullduplex_B.SFunction_o2 > 0) {
    if (!Fullduplex_DW.EnabledSubsystem_MODE) {
      Fullduplex_DW.EnabledSubsystem_MODE = TRUE;
    }
  } else {
    if (Fullduplex_DW.EnabledSubsystem_MODE) {
      Fullduplex_DW.EnabledSubsystem_MODE = FALSE;
    }
  }

  if (Fullduplex_DW.EnabledSubsystem_MODE) {
    /* Inport: '<S3>/In1' */
    for (i = 0; i < 8; i++) {
      Fullduplex_B.In1[i] = Fullduplex_B.SFunction_o1[i];
    }

    /* End of Inport: '<S3>/In1' */
  }

  /* End of Outputs for SubSystem: '<S2>/Enabled Subsystem' */

  /* Unpack: <Root>/Unpack */
  (void) memcpy(Fullduplex_B.Unpack, Fullduplex_B.In1,
                8);

  /* Sum: '<Root>/Sum' */
  Fullduplex_B.Sum = Fullduplex_B.DataTypeConversion1 - Fullduplex_B.Unpack[0];

  /* Pack: <S1>/Pack */
  (void) memcpy(Fullduplex_B.Pack, &Fullduplex_B.DataTypeConversion1,
                4);
  (void) memcpy(&Fullduplex_B.Pack[4], &Fullduplex_B.Unpack[0],
                4);
  (void) memcpy(&Fullduplex_B.Pack[8], &Fullduplex_B.Sum,
                4);
  (void) memcpy(&Fullduplex_B.Pack[12], &Fullduplex_B.Unpack[1],
                4);
  if (Fullduplex_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (stellaris_lp_sfunc_DebugPrint2): '<S1>/DebugPrint2_sfcn' */
    DebugPrint2(Fullduplex_P.DebugPrint2_sfcn_p1, Fullduplex_B.Pack);
  }

  /* Pack: <Root>/Pack */
  (void) memcpy(Fullduplex_B.Pack_m, &Fullduplex_B.DataTypeConversion1,
                4);
  (void) memcpy(&Fullduplex_B.Pack_m[4], &Fullduplex_P.Constant_Value,
                4);

  /* S-Function (stellaris_lp_sfunc_DataPackout): '<Root>/MPComSend' */
  i = datapacket_put(Fullduplex_P.MPComSend_p1, Fullduplex_ConstP.pooled1,
                     Fullduplex_B.Pack_m);
  Fullduplex_B.MPComSend = i;
}

/* Model update function */
void Fullduplex_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  Fullduplex_M->Timing.t[0] =
    (++Fullduplex_M->Timing.clockTick0) * Fullduplex_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.005s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.005, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    Fullduplex_M->Timing.clockTick1++;
  }

  rate_scheduler();
}

/* Model initialize function */
void Fullduplex_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Fullduplex_M, 0,
                sizeof(RT_MODEL_Fullduplex_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Fullduplex_M->solverInfo,
                          &Fullduplex_M->Timing.simTimeStep);
    rtsiSetTPtr(&Fullduplex_M->solverInfo, &rtmGetTPtr(Fullduplex_M));
    rtsiSetStepSizePtr(&Fullduplex_M->solverInfo,
                       &Fullduplex_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Fullduplex_M->solverInfo, ((const char_T **)
      (&rtmGetErrorStatus(Fullduplex_M))));
    rtsiSetRTModelPtr(&Fullduplex_M->solverInfo, Fullduplex_M);
  }

  rtsiSetSimTimeStep(&Fullduplex_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&Fullduplex_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Fullduplex_M, &Fullduplex_M->Timing.tArray[0]);
  Fullduplex_M->Timing.stepSize0 = 0.005;

  /* block I/O */
  (void) memset(((void *) &Fullduplex_B), 0,
                sizeof(B_Fullduplex_T));

  /* states (dwork) */
  (void) memset((void *)&Fullduplex_DW, 0,
                sizeof(DW_Fullduplex_T));

  /* Start for S-Function (stellaris_lp_sfunc_DataPackin): '<S2>/S-Function' */
  init_datapacket(Fullduplex_P.SFunction_p1, Fullduplex_ConstP.pooled1,
                  Fullduplex_P.SFunction_p3);

  /* Start for S-Function (stellaris_lp_sfunc_DataPackout): '<Root>/MPComSend' */
  init_datapacket(Fullduplex_P.MPComSend_p1, Fullduplex_P.MPComSend_p2,
                  Fullduplex_ConstP.pooled1);
}

/* Model terminate function */
void Fullduplex_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
