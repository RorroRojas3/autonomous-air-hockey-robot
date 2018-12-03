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

#include "FullDuplex_UDP.h"
#include "FullDuplex_UDP_private.h"
#include "MWDSP_EPH_R_R.h"
#include "rt_urand_Upu32_Yd_f_pw.h"

/* Named constants for Chart: '<Root>/X Movement' */
#define FullDuplex_IN_Motor_Moving_CCW1 ((uint8_T)1U)
#define FullDuplex_UDP_IN_Motor_Still  ((uint8_T)3U)
#define FullDuplex_U_IN_Motor_Moving_CW ((uint8_T)2U)
#define FullDuplex_U_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

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
  if ((FullDuplex_UDP_M->Timing.TaskCounters.TID[1]) > 999) {/* Sample time: [0.2s, 0.0s] */
    FullDuplex_UDP_M->Timing.TaskCounters.TID[1] = 0;
  }

  (FullDuplex_UDP_M->Timing.TaskCounters.TID[2])++;
  if ((FullDuplex_UDP_M->Timing.TaskCounters.TID[2]) > 4999) {/* Sample time: [1.0s, 0.0s] */
    FullDuplex_UDP_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * System initialize for atomic system:
 *    '<Root>/X Step to Pulse'
 *    '<Root>/Y Step to Pulse'
 */
void FullDuplex_UD_XSteptoPulse_Init(DW_XSteptoPulse_FullDuplex_UDP *localDW,
  P_XSteptoPulse_FullDuplex_UDP *localP)
{
  /* InitializeConditions for S-Function (sdspcount2): '<S4>/Counter' */
  localDW->Counter_ClkEphState = 5U;
  localDW->Counter_Count = localP->Counter_InitialCount;

  /* SystemInitialize for Atomic SubSystem: '<S4>/Hold' */
  /* InitializeConditions for Memory: '<S12>/Memory' */
  localDW->Memory_PreviousInput = localP->Memory_X0;

  /* End of SystemInitialize for SubSystem: '<S4>/Hold' */
}

/*
 * Start for atomic system:
 *    '<Root>/X Step to Pulse'
 *    '<Root>/Y Step to Pulse'
 */
void FullDuplex_U_XSteptoPulse_Start(DW_XSteptoPulse_FullDuplex_UDP *localDW)
{
  /* Start for DiscretePulseGenerator: '<S13>/Pulse Generator' */
  localDW->clockTickCounter = 0;
}

/*
 * Output and update for atomic system:
 *    '<Root>/X Step to Pulse'
 *    '<Root>/Y Step to Pulse'
 */
real32_T FullDuplex_UDP_XSteptoPulse(real_T rtu_Steps, uint8_T rtu_In1,
  DW_XSteptoPulse_FullDuplex_UDP *localDW, P_XSteptoPulse_FullDuplex_UDP *localP)
{
  real_T rtb_PulseGenerator;
  real32_T rtb_Switch2_d;
  real32_T rty_Pulses_0;

  /* DiscretePulseGenerator: '<S13>/Pulse Generator' */
  rtb_PulseGenerator = ((((real_T)localDW->clockTickCounter) <
    localP->PulseGenerator_Duty) && (localDW->clockTickCounter >= 0)) ?
    localP->PulseGenerator_Amp : 0.0;
  if (((real_T)localDW->clockTickCounter) >= (localP->PulseGenerator_Period -
       1.0)) {
    localDW->clockTickCounter = 0;
  } else {
    localDW->clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S13>/Pulse Generator' */

  /* S-Function (sdspcount2): '<S4>/Counter' incorporates:
   *  DataTypeConversion: '<S13>/Data Type Conversion1'
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   */
  if (MWDSP_EPH_R_R((real32_T)rtb_PulseGenerator, &localDW->Counter_ClkEphState)
      != 0U) {
    if (localDW->Counter_Count < ((uint8_T)rtu_Steps)) {
      localDW->Counter_Count = (uint8_T)(((uint32_T)localDW->Counter_Count) + 1U);
    } else {
      localDW->Counter_Count = 0U;
    }
  }

  rtb_Switch2_d = (real32_T)localDW->Counter_Count;

  /* Outputs for Atomic SubSystem: '<S4>/Hold' */
  /* Switch: '<S12>/Switch2' incorporates:
   *  Memory: '<S12>/Memory'
   *  RelationalOperator: '<S4>/Relational Operator'
   *  S-Function (sdspcount2): '<S4>/Counter'
   */
  if (!(rtu_Steps == ((real_T)localDW->Counter_Count))) {
    rtb_Switch2_d = localDW->Memory_PreviousInput;
  }

  /* End of Switch: '<S12>/Switch2' */

  /* Update for Memory: '<S12>/Memory' */
  localDW->Memory_PreviousInput = rtb_Switch2_d;

  /* End of Outputs for SubSystem: '<S4>/Hold' */

  /* Switch: '<S4>/Switch2' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  Switch: '<S4>/Switch1'
   */
  if (rtb_Switch2_d > localP->Switch2_Threshold) {
    rty_Pulses_0 = localP->Constant1_Value;
  } else if (((int32_T)rtu_In1) != 0) {
    /* Switch: '<S4>/Switch1' incorporates:
     *  DataTypeConversion: '<S13>/Data Type Conversion1'
     */
    rty_Pulses_0 = (real32_T)rtb_PulseGenerator;
  } else {
    rty_Pulses_0 = localP->Constant_Value;
  }

  /* End of Switch: '<S4>/Switch2' */
  return rty_Pulses_0;
}

/* Model step function */
void FullDuplex_UDP_step(void)
{
  uint8_T tmp;
  real32_T rtb_Switch2;
  int32_T i;
  real_T tmp_0;

  /* S-Function (stellaris_lp_sfunc_DataPackin): '<S10>/S-Function' incorporates:
   *  Inport: '<S11>/In1'
   */
  tmp = datapacket_get(FullDuplex_UDP_P.SFunction_p1, 24,
                       FullDuplex_UDP_DW.SFunction_o1);

  /* Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  if (((int32_T)tmp) > 0) {
    for (i = 0; i < 24; i++) {
      FullDuplex_UDP_DW.In1[i] = FullDuplex_UDP_DW.SFunction_o1[i];
    }
  }

  /* End of S-Function (stellaris_lp_sfunc_DataPackin): '<S10>/S-Function' */
  /* End of Outputs for SubSystem: '<S10>/Enabled Subsystem' */

  /* S-Function (xpcbytepacking): '<S2>/Unpack' */

  /* Byte Unpacking: <S2>/Unpack */
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Unpack[0], (uint8_T*)
               &FullDuplex_UDP_DW.In1[0] + 0, 24);

  /* Chart: '<Root>/X Movement' */
  /* Gateway: X Movement */
  /* During: X Movement */
  if (((uint32_T)FullDuplex_UDP_DW.is_active_c2_FullDuplex_UDP) == 0U) {
    /* Entry: X Movement */
    FullDuplex_UDP_DW.is_active_c2_FullDuplex_UDP = 1U;

    /* Entry Internal: X Movement */
    /* Transition: '<S3>:10' */
    FullDuplex_UDP_DW.is_c2_FullDuplex_UDP = FullDuplex_UDP_IN_Motor_Still;

    /* Entry 'Motor_Still': '<S3>:3' */
    /* '<S3>:3:1' steps = 1; */
    FullDuplex_UDP_DW.steps_f = 1.0F;

    /* '<S3>:3:1' x_motor = 0; */
    FullDuplex_UDP_DW.x_motor = 0U;
  } else {
    switch (FullDuplex_UDP_DW.is_c2_FullDuplex_UDP) {
     case FullDuplex_IN_Motor_Moving_CCW1:
      FullDuplex_UDP_DW.x_dir = 0U;

      /* During 'Motor_Moving_CCW1': '<S3>:1' */
      /* '<S3>:4:1' sf_internal_predicateOutput = ... */
      /* '<S3>:4:1' x_position == x_desired; */
      if (FullDuplex_UDP_DW.Unpack[1] == FullDuplex_UDP_DW.Unpack[0]) {
        /* Transition: '<S3>:4' */
        /* Exit 'Motor_Moving_CCW1': '<S3>:1' */
        /* '<S3>:1:3' x_motor = 0; */
        /* '<S3>:1:4' steps = 0; */
        FullDuplex_UDP_DW.is_c2_FullDuplex_UDP = FullDuplex_UDP_IN_Motor_Still;

        /* Entry 'Motor_Still': '<S3>:3' */
        /* '<S3>:3:1' steps = 1; */
        FullDuplex_UDP_DW.steps_f = 1.0F;

        /* '<S3>:3:1' x_motor = 0; */
        FullDuplex_UDP_DW.x_motor = 0U;
      } else {
        /* '<S3>:18:1' sf_internal_predicateOutput = ... */
        /* '<S3>:18:1' x_position > x_desired; */
        if (FullDuplex_UDP_DW.Unpack[1] > FullDuplex_UDP_DW.Unpack[0]) {
          /* Transition: '<S3>:18' */
          /* Exit 'Motor_Moving_CCW1': '<S3>:1' */
          /* '<S3>:1:3' x_motor = 0; */
          /* '<S3>:1:4' steps = 0; */
          FullDuplex_UDP_DW.is_c2_FullDuplex_UDP =
            FullDuplex_U_IN_Motor_Moving_CW;

          /* Entry 'Motor_Moving_CW': '<S3>:7' */
          /* '<S3>:7:1' steps = 1; */
          FullDuplex_UDP_DW.steps_f = 1.0F;

          /* '<S3>:7:1' x_dir = 1; */
          FullDuplex_UDP_DW.x_dir = 1U;

          /* '<S3>:7:1' x_motor = 1; */
          FullDuplex_UDP_DW.x_motor = 1U;
        }
      }
      break;

     case FullDuplex_U_IN_Motor_Moving_CW:
      FullDuplex_UDP_DW.x_dir = 1U;

      /* During 'Motor_Moving_CW': '<S3>:7' */
      /* '<S3>:9:1' sf_internal_predicateOutput = ... */
      /* '<S3>:9:1' x_position == x_desired; */
      if (FullDuplex_UDP_DW.Unpack[1] == FullDuplex_UDP_DW.Unpack[0]) {
        /* Transition: '<S3>:9' */
        /* Exit 'Motor_Moving_CW': '<S3>:7' */
        /* '<S3>:7:3' x_motor = 0; */
        /* '<S3>:7:4' steps = 0; */
        FullDuplex_UDP_DW.is_c2_FullDuplex_UDP = FullDuplex_UDP_IN_Motor_Still;

        /* Entry 'Motor_Still': '<S3>:3' */
        /* '<S3>:3:1' steps = 1; */
        FullDuplex_UDP_DW.steps_f = 1.0F;

        /* '<S3>:3:1' x_motor = 0; */
        FullDuplex_UDP_DW.x_motor = 0U;
      } else {
        /* '<S3>:17:1' sf_internal_predicateOutput = ... */
        /* '<S3>:17:1' x_position < x_desired; */
        if (FullDuplex_UDP_DW.Unpack[1] < FullDuplex_UDP_DW.Unpack[0]) {
          /* Transition: '<S3>:17' */
          /* Exit 'Motor_Moving_CW': '<S3>:7' */
          /* '<S3>:7:3' x_motor = 0; */
          /* '<S3>:7:4' steps = 0; */
          FullDuplex_UDP_DW.is_c2_FullDuplex_UDP =
            FullDuplex_IN_Motor_Moving_CCW1;

          /* Entry 'Motor_Moving_CCW1': '<S3>:1' */
          /* '<S3>:1:1' steps = 1; */
          FullDuplex_UDP_DW.steps_f = 1.0F;

          /* '<S3>:1:1' x_dir = 0; */
          FullDuplex_UDP_DW.x_dir = 0U;

          /* '<S3>:1:1' x_motor = 1; */
          FullDuplex_UDP_DW.x_motor = 1U;
        }
      }
      break;

     default:
      /* During 'Motor_Still': '<S3>:3' */
      /* '<S3>:5:1' sf_internal_predicateOutput = ... */
      /* '<S3>:5:1' x_position < x_desired; */
      if (FullDuplex_UDP_DW.Unpack[1] < FullDuplex_UDP_DW.Unpack[0]) {
        /* Transition: '<S3>:5' */
        /* Exit 'Motor_Still': '<S3>:3' */
        /* '<S3>:3:1' steps = 0; */
        FullDuplex_UDP_DW.is_c2_FullDuplex_UDP = FullDuplex_IN_Motor_Moving_CCW1;

        /* Entry 'Motor_Moving_CCW1': '<S3>:1' */
        /* '<S3>:1:1' steps = 1; */
        FullDuplex_UDP_DW.steps_f = 1.0F;

        /* '<S3>:1:1' x_dir = 0; */
        FullDuplex_UDP_DW.x_dir = 0U;

        /* '<S3>:1:1' x_motor = 1; */
        FullDuplex_UDP_DW.x_motor = 1U;
      } else {
        /* '<S3>:8:1' sf_internal_predicateOutput = ... */
        /* '<S3>:8:1' x_position > x_desired; */
        if (FullDuplex_UDP_DW.Unpack[1] > FullDuplex_UDP_DW.Unpack[0]) {
          /* Transition: '<S3>:8' */
          /* Exit 'Motor_Still': '<S3>:3' */
          /* '<S3>:3:1' steps = 0; */
          FullDuplex_UDP_DW.is_c2_FullDuplex_UDP =
            FullDuplex_U_IN_Motor_Moving_CW;

          /* Entry 'Motor_Moving_CW': '<S3>:7' */
          /* '<S3>:7:1' steps = 1; */
          FullDuplex_UDP_DW.steps_f = 1.0F;

          /* '<S3>:7:1' x_dir = 1; */
          FullDuplex_UDP_DW.x_dir = 1U;

          /* '<S3>:7:1' x_motor = 1; */
          FullDuplex_UDP_DW.x_motor = 1U;
        }
      }
      break;
    }
  }

  /* End of Chart: '<Root>/X Movement' */

  /* S-Function (stellaris_lp_sfunc_GPIOWrite): '<S5>/GPIO Write' incorporates:
   *  Constant: '<S5>/GPIO Pin Select'
   *  Gain: '<S5>/Gain'
   */
  GPIOWrite(FullDuplex_UDP_P.GPIOWrite_p1, FullDuplex_UDP_P.GPIOPinSelect_Value,
            (uint8_T)(((uint32_T)FullDuplex_UDP_P.Gain_Gain) * ((uint32_T)
              FullDuplex_UDP_DW.x_dir)));

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  if (FullDuplex_UDP_DW.steps_f != 0.0F) {
    tmp_0 = (real_T)FullDuplex_UDP_DW.Unpack[2];
  } else {
    tmp_0 = FullDuplex_UDP_P.Constant_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Outputs for Atomic SubSystem: '<Root>/X Step to Pulse' */
  rtb_Switch2 = (real32_T) FullDuplex_UDP_XSteptoPulse(tmp_0,
    FullDuplex_UDP_DW.x_motor, &FullDuplex_UDP_DW.XSteptoPulse,
    (P_XSteptoPulse_FullDuplex_UDP *)(&FullDuplex_UDP_P.XSteptoPulse));

  /* End of Outputs for SubSystem: '<Root>/X Step to Pulse' */

  /* S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S14>/S-Function2' */
  PWMUpdate_f(FullDuplex_UDP_P.SFunction2_p1, rtb_Switch2);

  /* S-Function (stellaris_lp_sfunc_GPIOSetup): '<S5>/GPIO Setup1' */
  GPIOVoidFunc();

  /* Chart: '<Root>/Y Movement' */
  /* Gateway: Y Movement */
  /* During: Y Movement */
  if (((uint32_T)FullDuplex_UDP_DW.is_active_c3_FullDuplex_UDP) == 0U) {
    /* Entry: Y Movement */
    FullDuplex_UDP_DW.is_active_c3_FullDuplex_UDP = 1U;

    /* Entry Internal: Y Movement */
    /* Transition: '<S6>:10' */
    FullDuplex_UDP_DW.is_c3_FullDuplex_UDP = FullDuplex_UDP_IN_Motor_Still;

    /* Entry 'Motor_Still': '<S6>:3' */
    /* '<S6>:3:1' steps = 1; */
    FullDuplex_UDP_DW.steps = 1.0F;

    /* '<S6>:3:1' y_motor = 0; */
    FullDuplex_UDP_DW.y_motor = 0U;
  } else {
    switch (FullDuplex_UDP_DW.is_c3_FullDuplex_UDP) {
     case FullDuplex_IN_Motor_Moving_CCW1:
      FullDuplex_UDP_DW.y_dir = 0U;

      /* During 'Motor_Moving_CCW1': '<S6>:1' */
      /* '<S6>:4:1' sf_internal_predicateOutput = ... */
      /* '<S6>:4:1' y_position == y_desired; */
      if (FullDuplex_UDP_DW.Unpack[4] == FullDuplex_UDP_DW.Unpack[3]) {
        /* Transition: '<S6>:4' */
        /* Exit 'Motor_Moving_CCW1': '<S6>:1' */
        /* '<S6>:1:3' y_motor = 0; */
        /* '<S6>:1:4' steps = 0; */
        FullDuplex_UDP_DW.is_c3_FullDuplex_UDP = FullDuplex_UDP_IN_Motor_Still;

        /* Entry 'Motor_Still': '<S6>:3' */
        /* '<S6>:3:1' steps = 1; */
        FullDuplex_UDP_DW.steps = 1.0F;

        /* '<S6>:3:1' y_motor = 0; */
        FullDuplex_UDP_DW.y_motor = 0U;
      } else {
        /* '<S6>:17:1' sf_internal_predicateOutput = ... */
        /* '<S6>:17:1' y_position > y_desired; */
        if (FullDuplex_UDP_DW.Unpack[4] > FullDuplex_UDP_DW.Unpack[3]) {
          /* Transition: '<S6>:17' */
          /* Exit 'Motor_Moving_CCW1': '<S6>:1' */
          /* '<S6>:1:3' y_motor = 0; */
          /* '<S6>:1:4' steps = 0; */
          FullDuplex_UDP_DW.is_c3_FullDuplex_UDP =
            FullDuplex_U_IN_Motor_Moving_CW;

          /* Entry 'Motor_Moving_CW': '<S6>:7' */
          /* '<S6>:7:1' steps = 1; */
          FullDuplex_UDP_DW.steps = 1.0F;

          /* '<S6>:7:1' y_dir = 1; */
          FullDuplex_UDP_DW.y_dir = 1U;

          /* '<S6>:7:1' y_motor = 1; */
          FullDuplex_UDP_DW.y_motor = 1U;
        }
      }
      break;

     case FullDuplex_U_IN_Motor_Moving_CW:
      FullDuplex_UDP_DW.y_dir = 1U;

      /* During 'Motor_Moving_CW': '<S6>:7' */
      /* '<S6>:9:1' sf_internal_predicateOutput = ... */
      /* '<S6>:9:1' y_position == y_desired; */
      if (FullDuplex_UDP_DW.Unpack[4] == FullDuplex_UDP_DW.Unpack[3]) {
        /* Transition: '<S6>:9' */
        /* Exit 'Motor_Moving_CW': '<S6>:7' */
        /* '<S6>:7:3' y_motor = 0; */
        /* '<S6>:7:4' steps = 0; */
        FullDuplex_UDP_DW.is_c3_FullDuplex_UDP = FullDuplex_UDP_IN_Motor_Still;

        /* Entry 'Motor_Still': '<S6>:3' */
        /* '<S6>:3:1' steps = 1; */
        FullDuplex_UDP_DW.steps = 1.0F;

        /* '<S6>:3:1' y_motor = 0; */
        FullDuplex_UDP_DW.y_motor = 0U;
      } else {
        /* '<S6>:18:1' sf_internal_predicateOutput = ... */
        /* '<S6>:18:1' y_position < y_desired; */
        if (FullDuplex_UDP_DW.Unpack[4] < FullDuplex_UDP_DW.Unpack[3]) {
          /* Transition: '<S6>:18' */
          /* Exit 'Motor_Moving_CW': '<S6>:7' */
          /* '<S6>:7:3' y_motor = 0; */
          /* '<S6>:7:4' steps = 0; */
          FullDuplex_UDP_DW.is_c3_FullDuplex_UDP =
            FullDuplex_IN_Motor_Moving_CCW1;

          /* Entry 'Motor_Moving_CCW1': '<S6>:1' */
          /* '<S6>:1:1' steps = 1; */
          FullDuplex_UDP_DW.steps = 1.0F;

          /* '<S6>:1:1' y_dir = 0; */
          FullDuplex_UDP_DW.y_dir = 0U;

          /* '<S6>:1:1' y_motor = 1; */
          FullDuplex_UDP_DW.y_motor = 1U;
        }
      }
      break;

     default:
      /* During 'Motor_Still': '<S6>:3' */
      /* '<S6>:5:1' sf_internal_predicateOutput = ... */
      /* '<S6>:5:1' y_position < y_desired; */
      if (FullDuplex_UDP_DW.Unpack[4] < FullDuplex_UDP_DW.Unpack[3]) {
        /* Transition: '<S6>:5' */
        FullDuplex_UDP_DW.is_c3_FullDuplex_UDP = FullDuplex_IN_Motor_Moving_CCW1;

        /* Entry 'Motor_Moving_CCW1': '<S6>:1' */
        /* '<S6>:1:1' steps = 1; */
        FullDuplex_UDP_DW.steps = 1.0F;

        /* '<S6>:1:1' y_dir = 0; */
        FullDuplex_UDP_DW.y_dir = 0U;

        /* '<S6>:1:1' y_motor = 1; */
        FullDuplex_UDP_DW.y_motor = 1U;
      } else {
        /* '<S6>:8:1' sf_internal_predicateOutput = ... */
        /* '<S6>:8:1' y_position > y_desired; */
        if (FullDuplex_UDP_DW.Unpack[4] > FullDuplex_UDP_DW.Unpack[3]) {
          /* Transition: '<S6>:8' */
          FullDuplex_UDP_DW.is_c3_FullDuplex_UDP =
            FullDuplex_U_IN_Motor_Moving_CW;

          /* Entry 'Motor_Moving_CW': '<S6>:7' */
          /* '<S6>:7:1' steps = 1; */
          FullDuplex_UDP_DW.steps = 1.0F;

          /* '<S6>:7:1' y_dir = 1; */
          FullDuplex_UDP_DW.y_dir = 1U;

          /* '<S6>:7:1' y_motor = 1; */
          FullDuplex_UDP_DW.y_motor = 1U;
        }
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Y Movement' */

  /* S-Function (stellaris_lp_sfunc_GPIOWrite): '<S8>/GPIO Write' incorporates:
   *  Constant: '<S8>/GPIO Pin Select'
   *  Gain: '<S8>/Gain'
   */
  GPIOWrite(FullDuplex_UDP_P.GPIOWrite_p1_n,
            FullDuplex_UDP_P.GPIOPinSelect_Value_g, (uint8_T)(((uint32_T)
              FullDuplex_UDP_P.Gain_Gain_n) * ((uint32_T)FullDuplex_UDP_DW.y_dir)));

  /* S-Function (stellaris_lp_sfunc_GPIOWrite): '<S8>/GPIO Write1' incorporates:
   *  Constant: '<S8>/GPIO Pin Select1'
   *  Gain: '<S8>/Gain1'
   *  Logic: '<S8>/Logical Operator'
   */
  GPIOWrite(FullDuplex_UDP_P.GPIOWrite1_p1,
            FullDuplex_UDP_P.GPIOPinSelect1_Value, (uint8_T)((int32_T)
             ((!(((int32_T)FullDuplex_UDP_DW.y_dir) != 0)) ? ((int32_T)
    FullDuplex_UDP_P.Gain1_Gain) : 0)));

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   */
  if (FullDuplex_UDP_DW.steps != 0.0F) {
    tmp_0 = (real_T)FullDuplex_UDP_DW.Unpack[5];
  } else {
    tmp_0 = FullDuplex_UDP_P.Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Outputs for Atomic SubSystem: '<Root>/Y Step to Pulse' */
  rtb_Switch2 = (real32_T) FullDuplex_UDP_XSteptoPulse(tmp_0,
    FullDuplex_UDP_DW.y_motor, &FullDuplex_UDP_DW.YSteptoPulse,
    (P_XSteptoPulse_FullDuplex_UDP *)(&FullDuplex_UDP_P.YSteptoPulse));

  /* End of Outputs for SubSystem: '<Root>/Y Step to Pulse' */

  /* S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S17>/S-Function2' */
  PWMUpdate_f(FullDuplex_UDP_P.SFunction2_p1_b, rtb_Switch2);

  /* S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S18>/S-Function2' */
  PWMUpdate_f(FullDuplex_UDP_P.SFunction2_p1_n, rtb_Switch2);

  /* S-Function (stellaris_lp_sfunc_GPIOSetup): '<S8>/GPIO Setup1' */
  GPIOVoidFunc();

  /* S-Function (stellaris_lp_sfunc_GPIOSetup): '<S8>/GPIO Setup2' */
  GPIOVoidFunc();

  /* S-Function (xpcbytepacking): '<S9>/Pack' */

  /* Byte Packing: <S9>/Pack */
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 0, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[0], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 4, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[1], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 8, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[2], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 12, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[3], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 16, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[4], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 20, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[5], 4);
  if (FullDuplex_UDP_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (stellaris_lp_sfunc_DebugPrint2): '<S9>/DebugPrint2_sfcn' */
    DebugPrint2(FullDuplex_UDP_P.DebugPrint2_sfcn_p1, FullDuplex_UDP_DW.Pack);
  }

  /* S-Function (xpcbytepacking): '<S2>/Pack' */

  /* Byte Packing: <S2>/Pack */
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 0, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[0], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 4, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[1], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 8, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[2], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 12, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[3], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 16, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[4], 4);
  (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 20, (uint8_T*)
               &FullDuplex_UDP_DW.Unpack[5], 4);

  /* S-Function (stellaris_lp_sfunc_DataPackout): '<S2>/MPComSend' */
  datapacket_put(FullDuplex_UDP_P.MPComSend_p1, 24, FullDuplex_UDP_DW.Pack_n);
  if (FullDuplex_UDP_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (stellaris_lp_sfunc_GPIOWrite): '<S1>/GPIO Write' incorporates:
     *  Constant: '<S1>/BLUE LED'
     *  Constant: '<S1>/GREEN LED'
     *  Constant: '<S1>/RED LED'
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     *  S-Function (sfix_bitop): '<S1>/Bitwise Operator'
     *  UniformRandomNumber: '<S1>/Uniform Random Number'
     */
    GPIOWrite(FullDuplex_UDP_P.GPIOWrite_p1_b, (uint8_T)
              ((FullDuplex_UDP_P.REDLED_Value | FullDuplex_UDP_P.BLUELED_Value) |
               FullDuplex_UDP_P.GREENLED_Value), (uint8_T)
              FullDuplex_UDP_DW.UniformRandomNumber_NextOutput);
  }

  /* S-Function (stellaris_lp_sfunc_GPIOSetup): '<S1>/GPIO Setup' */
  GPIOVoidFunc();
  if (FullDuplex_UDP_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update for UniformRandomNumber: '<S1>/Uniform Random Number' */
    FullDuplex_UDP_DW.UniformRandomNumber_NextOutput =
      ((FullDuplex_UDP_P.UniformRandomNumber_Maximum -
        FullDuplex_UDP_P.UniformRandomNumber_Minimum) * rt_urand_Upu32_Yd_f_pw
       (&FullDuplex_UDP_DW.RandSeed)) +
      FullDuplex_UDP_P.UniformRandomNumber_Minimum;
  }

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
    uint32_T tseed;
    int32_T t;
    int32_T i;

    /* Start for S-Function (stellaris_lp_sfunc_DataPackin): '<S10>/S-Function' */
    init_datapacket(FullDuplex_UDP_P.SFunction_p1, 24,
                    FullDuplex_UDP_P.SFunction_p3);

    /* Start for Atomic SubSystem: '<Root>/X Step to Pulse' */
    FullDuplex_U_XSteptoPulse_Start(&FullDuplex_UDP_DW.XSteptoPulse);

    /* End of Start for SubSystem: '<Root>/X Step to Pulse' */

    /* Start for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S14>/S-Function2' */
    PWMInit(FullDuplex_UDP_P.SFunction2_p1, FullDuplex_UDP_P.SFunction2_p2,
            FullDuplex_UDP_P.SFunction2_p3);

    /* Start for S-Function (stellaris_lp_sfunc_GPIOSetup): '<S5>/GPIO Setup1' */
    GPIOSetup(FullDuplex_UDP_P.GPIOSetup1_p1, FullDuplex_UDP_P.GPIOSetup1_p2,
              FullDuplex_UDP_P.GPIOSetup1_p3, FullDuplex_UDP_P.GPIOSetup1_p4);

    /* Start for Atomic SubSystem: '<Root>/Y Step to Pulse' */
    FullDuplex_U_XSteptoPulse_Start(&FullDuplex_UDP_DW.YSteptoPulse);

    /* End of Start for SubSystem: '<Root>/Y Step to Pulse' */

    /* Start for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S17>/S-Function2' */
    PWMInit(FullDuplex_UDP_P.SFunction2_p1_b, FullDuplex_UDP_P.SFunction2_p2_n,
            FullDuplex_UDP_P.SFunction2_p3_d);

    /* Start for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S18>/S-Function2' */
    PWMInit(FullDuplex_UDP_P.SFunction2_p1_n, FullDuplex_UDP_P.SFunction2_p2_o,
            FullDuplex_UDP_P.SFunction2_p3_l);

    /* Start for S-Function (stellaris_lp_sfunc_GPIOSetup): '<S8>/GPIO Setup1' */
    GPIOSetup(FullDuplex_UDP_P.GPIOSetup1_p1_l, FullDuplex_UDP_P.GPIOSetup1_p2_k,
              FullDuplex_UDP_P.GPIOSetup1_p3_m, FullDuplex_UDP_P.GPIOSetup1_p4_o);

    /* Start for S-Function (stellaris_lp_sfunc_GPIOSetup): '<S8>/GPIO Setup2' */
    GPIOSetup(FullDuplex_UDP_P.GPIOSetup2_p1, FullDuplex_UDP_P.GPIOSetup2_p2,
              FullDuplex_UDP_P.GPIOSetup2_p3, FullDuplex_UDP_P.GPIOSetup2_p4);

    /* Start for S-Function (stellaris_lp_sfunc_DataPackout): '<S2>/MPComSend' */
    init_datapacket(FullDuplex_UDP_P.MPComSend_p1, FullDuplex_UDP_P.MPComSend_p2,
                    24);

    /* Start for S-Function (stellaris_lp_sfunc_GPIOSetup): '<S1>/GPIO Setup' */
    GPIOSetup(FullDuplex_UDP_P.GPIOSetup_p1, FullDuplex_UDP_P.GPIOSetup_p2,
              FullDuplex_UDP_P.GPIOSetup_p3, FullDuplex_UDP_P.GPIOSetup_p4);

    /* InitializeConditions for UniformRandomNumber: '<S1>/Uniform Random Number' */
    tseed = (uint32_T)FullDuplex_UDP_P.UniformRandomNumber_Seed;
    i = (int32_T)((uint32_T)(tseed >> 16U));
    t = (int32_T)((uint32_T)(tseed & 32768U));
    tseed = ((((tseed - (((uint32_T)i) << 16U)) + ((uint32_T)t)) << 16U) +
             ((uint32_T)t)) + ((uint32_T)i);
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    FullDuplex_UDP_DW.RandSeed = tseed;
    FullDuplex_UDP_DW.UniformRandomNumber_NextOutput =
      ((FullDuplex_UDP_P.UniformRandomNumber_Maximum -
        FullDuplex_UDP_P.UniformRandomNumber_Minimum) * rt_urand_Upu32_Yd_f_pw
       (&FullDuplex_UDP_DW.RandSeed)) +
      FullDuplex_UDP_P.UniformRandomNumber_Minimum;

    /* End of InitializeConditions for UniformRandomNumber: '<S1>/Uniform Random Number' */

    /* SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem' */
    /* SystemInitialize for Outport: '<S11>/Out1' */
    for (i = 0; i < 24; i++) {
      FullDuplex_UDP_DW.In1[i] = FullDuplex_UDP_P.Out1_Y0;
    }

    /* End of SystemInitialize for Outport: '<S11>/Out1' */
    /* End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem' */

    /* SystemInitialize for Chart: '<Root>/X Movement' */
    FullDuplex_UDP_DW.is_active_c2_FullDuplex_UDP = 0U;
    FullDuplex_UDP_DW.is_c2_FullDuplex_UDP = FullDuplex_U_IN_NO_ACTIVE_CHILD;

    /* SystemInitialize for Atomic SubSystem: '<Root>/X Step to Pulse' */
    FullDuplex_UD_XSteptoPulse_Init(&FullDuplex_UDP_DW.XSteptoPulse,
      (P_XSteptoPulse_FullDuplex_UDP *)(&FullDuplex_UDP_P.XSteptoPulse));

    /* End of SystemInitialize for SubSystem: '<Root>/X Step to Pulse' */

    /* SystemInitialize for Chart: '<Root>/Y Movement' */
    FullDuplex_UDP_DW.is_active_c3_FullDuplex_UDP = 0U;
    FullDuplex_UDP_DW.is_c3_FullDuplex_UDP = FullDuplex_U_IN_NO_ACTIVE_CHILD;

    /* SystemInitialize for Atomic SubSystem: '<Root>/Y Step to Pulse' */
    FullDuplex_UD_XSteptoPulse_Init(&FullDuplex_UDP_DW.YSteptoPulse,
      (P_XSteptoPulse_FullDuplex_UDP *)(&FullDuplex_UDP_P.YSteptoPulse));

    /* End of SystemInitialize for SubSystem: '<Root>/Y Step to Pulse' */
  }
}

/* Model terminate function */
void FullDuplex_UDP_terminate(void)
{
  /* Terminate for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S14>/S-Function2' */
  PWMStop(FullDuplex_UDP_P.SFunction2_p1);

  /* Terminate for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S17>/S-Function2' */
  PWMStop(FullDuplex_UDP_P.SFunction2_p1_b);

  /* Terminate for S-Function (stellaris_lp_sfunc_PWMUpdate_f): '<S18>/S-Function2' */
  PWMStop(FullDuplex_UDP_P.SFunction2_p1_n);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
