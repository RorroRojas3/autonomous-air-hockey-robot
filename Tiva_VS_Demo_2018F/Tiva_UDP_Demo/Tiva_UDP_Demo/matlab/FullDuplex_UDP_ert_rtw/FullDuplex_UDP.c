/*
 * Academic Student License -- for use by students to meet course
 * requirements and perform academic research at degree granting
 * institutions only.  Not for government, commercial, or other
 * organizational use.
 *
 * File: FullDuplex_UDP.c
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
#include "MWDSP_EPH_R_R.h"

/* Block signals and states (auto storage) */
DW_FullDuplex_UDP FullDuplex_UDP_DW;

/* Real-time model */
RT_MODEL_FullDuplex_UDP FullDuplex_UDP_M_;
RT_MODEL_FullDuplex_UDP *const FullDuplex_UDP_M = &FullDuplex_UDP_M_;
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
  (FullDuplex_UDP_M->Timing.TaskCounters.TID[1])++;
  if ((FullDuplex_UDP_M->Timing.TaskCounters.TID[1]) > 4999) {/* Sample time: [1.0s, 0.0s] */
    FullDuplex_UDP_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void FullDuplex_UDP_step(void)
{
  uint8_T rtb_SFunction_o1[8];
  real_T rtb_PulseGenerator;
  uint8_T rtb_DataTypeConversion_b;
  real32_T rtb_Switch2;
  int32_T i;

  /* S-Function (stellaris_lp_sfunc_DataPackin): '<S5>/S-Function' incorporates:
   *  Inport: '<S6>/In1'
   */
  rtb_DataTypeConversion_b = datapacket_get(FullDuplex_UDP_P.SFunction_p1, 8,
    rtb_SFunction_o1);

  /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S6>/Enable'
   */
  if (((int32_T)rtb_DataTypeConversion_b) > 0) {
    for (i = 0; i < 8; i++) {
      FullDuplex_UDP_DW.In1[i] = rtb_SFunction_o1[i];
    }
  }

  /* End of S-Function (stellaris_lp_sfunc_DataPackin): '<S5>/S-Function' */
  /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */

  /* S-Function (xpcbytepacking): '<S1>/Unpack' */

  /* Byte Unpacking: <S1>/Unpack */
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Unpack[0], (uint8_T*)
               &FullDuplex_UDP_DW.In1[0] + 0, 8);

  /* S-Function (stellaris_lp_sfunc_GPIOWrite): '<S3>/GPIO Write' incorporates:
   *  Constant: '<S3>/GPIO Pin Select'
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Gain: '<S3>/Gain'
   */
  GPIOWrite(FullDuplex_UDP_P.GPIOWrite_p1, FullDuplex_UDP_P.GPIOPinSelect_Value,
            (uint8_T)(((uint32_T)FullDuplex_UDP_P.Gain_Gain) * ((uint32_T)
              ((uint8_T)FullDuplex_UDP_DW.Unpack[0]))));

  /* Outputs for Atomic SubSystem: '<Root>/X Step to Pulse' */
  /* DiscretePulseGenerator: '<S8>/Pulse Generator' */
  rtb_PulseGenerator = ((((real_T)FullDuplex_UDP_DW.clockTickCounter) <
    FullDuplex_UDP_P.PulseGenerator_Duty) && (FullDuplex_UDP_DW.clockTickCounter
    >= 0)) ? FullDuplex_UDP_P.PulseGenerator_Amp : 0.0;
  if (((real_T)FullDuplex_UDP_DW.clockTickCounter) >=
      (FullDuplex_UDP_P.PulseGenerator_Period - 1.0)) {
    FullDuplex_UDP_DW.clockTickCounter = 0;
  } else {
    FullDuplex_UDP_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S8>/Pulse Generator' */

  /* S-Function (sdspcount2): '<S2>/Counter' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  DataTypeConversion: '<S8>/Data Type Conversion1'
   */
  if (MWDSP_EPH_R_R((real32_T)rtb_PulseGenerator,
                    &FullDuplex_UDP_DW.Counter_ClkEphState) != 0U) {
    if (FullDuplex_UDP_DW.Counter_Count < ((uint8_T)FullDuplex_UDP_DW.Unpack[1]))
    {
      FullDuplex_UDP_DW.Counter_Count = (uint8_T)(((uint32_T)
        FullDuplex_UDP_DW.Counter_Count) + 1U);
    } else {
      FullDuplex_UDP_DW.Counter_Count = 0U;
    }
  }

  rtb_Switch2 = (real32_T)FullDuplex_UDP_DW.Counter_Count;

  /* Outputs for Atomic SubSystem: '<S2>/Hold' */
  /* Switch: '<S7>/Switch2' incorporates:
   *  Memory: '<S7>/Memory'
   *  RelationalOperator: '<S2>/Relational Operator'
   *  S-Function (sdspcount2): '<S2>/Counter'
   */
  if (!(FullDuplex_UDP_DW.Unpack[1] == ((real32_T)
        FullDuplex_UDP_DW.Counter_Count))) {
    rtb_Switch2 = FullDuplex_UDP_DW.Memory_PreviousInput;
  }

  /* End of Switch: '<S7>/Switch2' */

  /* Update for Memory: '<S7>/Memory' */
  FullDuplex_UDP_DW.Memory_PreviousInput = rtb_Switch2;

  /* End of Outputs for SubSystem: '<S2>/Hold' */

  /* Switch: '<S2>/Switch1' incorporates:
   *  Constant: '<S2>/Constant'
   *  DataTypeConversion: '<S8>/Data Type Conversion1'
   *  RelationalOperator: '<S2>/Relational Operator1'
   */
  if (FullDuplex_UDP_DW.Unpack[1] == rtb_Switch2) {
    rtb_Switch2 = FullDuplex_UDP_P.Constant_Value;
  } else {
    rtb_Switch2 = (real32_T)rtb_PulseGenerator;
  }

  /* End of Switch: '<S2>/Switch1' */
  /* End of Outputs for SubSystem: '<Root>/X Step to Pulse' */

  /* S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S9>/S-Function2' */
  PWMUpdate_f(FullDuplex_UDP_P.SFunction2_p1, rtb_Switch2);

  /* S-Function (stellaris_lp_sfunc_GPIOSetup): '<S3>/GPIO Setup1' */
  GPIOVoidFunc();

  /* S-Function (xpcbytepacking): '<S4>/Pack' */

  /* Byte Packing: <S4>/Pack */
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 0, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[0], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 4, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[1], 4);
  if (FullDuplex_UDP_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (stellaris_lp_sfunc_DebugPrint2): '<S4>/DebugPrint2_sfcn' */
    DebugPrint2(FullDuplex_UDP_P.DebugPrint2_sfcn_p1, FullDuplex_UDP_DW.Pack);
  }

  /* S-Function (xpcbytepacking): '<S1>/Pack' */

  /* Byte Packing: <S1>/Pack */
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 0, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[0], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 4, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[1], 4);

  /* S-Function (stellaris_lp_sfunc_DataPackout): '<S1>/MPComSend' */
  datapacket_put(FullDuplex_UDP_P.MPComSend_p1, 8, FullDuplex_UDP_DW.Pack_n);
  rate_scheduler();
}

/* Model initialize function */
void FullDuplex_UDP_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)FullDuplex_UDP_M, 0,
                sizeof(RT_MODEL_FullDuplex_UDP));

  /* states (dwork) */
  (void) memset((void *)&FullDuplex_UDP_DW, 0,
                sizeof(DW_FullDuplex_UDP));

  {
    int32_T i;

    /* Start for S-Function (stellaris_lp_sfunc_DataPackin): '<S5>/S-Function' */
    init_datapacket(FullDuplex_UDP_P.SFunction_p1, 8,
                    FullDuplex_UDP_P.SFunction_p3);

    /* Start for Atomic SubSystem: '<Root>/X Step to Pulse' */
    /* Start for DiscretePulseGenerator: '<S8>/Pulse Generator' */
    FullDuplex_UDP_DW.clockTickCounter = 0;

    /* End of Start for SubSystem: '<Root>/X Step to Pulse' */

    /* Start for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S9>/S-Function2' */
    PWMInit(FullDuplex_UDP_P.SFunction2_p1, FullDuplex_UDP_P.SFunction2_p2,
            FullDuplex_UDP_P.SFunction2_p3);

    /* Start for S-Function (stellaris_lp_sfunc_GPIOSetup): '<S3>/GPIO Setup1' */
    GPIOSetup(FullDuplex_UDP_P.GPIOSetup1_p1, FullDuplex_UDP_P.GPIOSetup1_p2,
              FullDuplex_UDP_P.GPIOSetup1_p3, FullDuplex_UDP_P.GPIOSetup1_p4);

    /* Start for S-Function (stellaris_lp_sfunc_DataPackout): '<S1>/MPComSend' */
    init_datapacket(FullDuplex_UDP_P.MPComSend_p1, FullDuplex_UDP_P.MPComSend_p2,
                    8);

    /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
    /* SystemInitialize for Outport: '<S6>/Out1' */
    for (i = 0; i < 8; i++) {
      FullDuplex_UDP_DW.In1[i] = FullDuplex_UDP_P.Out1_Y0;
    }

    /* End of SystemInitialize for Outport: '<S6>/Out1' */
    /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/X Step to Pulse' */
    /* InitializeConditions for S-Function (sdspcount2): '<S2>/Counter' */
    FullDuplex_UDP_DW.Counter_ClkEphState = 5U;
    FullDuplex_UDP_DW.Counter_Count = FullDuplex_UDP_P.Counter_InitialCount;

    /* SystemInitialize for Atomic SubSystem: '<S2>/Hold' */
    /* InitializeConditions for Memory: '<S7>/Memory' */
    FullDuplex_UDP_DW.Memory_PreviousInput = FullDuplex_UDP_P.Memory_X0;

    /* End of SystemInitialize for SubSystem: '<S2>/Hold' */
    /* End of SystemInitialize for SubSystem: '<Root>/X Step to Pulse' */
  }
}

/* Model terminate function */
void FullDuplex_UDP_terminate(void)
{
  /* Terminate for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S9>/S-Function2' */
  PWMStop(FullDuplex_UDP_P.SFunction2_p1);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
