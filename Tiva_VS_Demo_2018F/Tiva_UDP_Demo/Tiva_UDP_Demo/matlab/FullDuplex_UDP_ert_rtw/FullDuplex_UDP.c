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
  if ((FullDuplex_UDP_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [1.0s, 0.0s] */
    FullDuplex_UDP_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void FullDuplex_UDP_step(void)
{
  uint8_T tmp;
  uint8_T rtb_SFunction_o1[8];
  int32_T i;
  if (FullDuplex_UDP_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (stellaris_lp_sfunc_DataPackin): '<S3>/S-Function' incorporates:
     *  Inport: '<S4>/In1'
     */
    tmp = datapacket_get(FullDuplex_UDP_P.SFunction_p1, 8, rtb_SFunction_o1);

    /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S4>/Enable'
     */
    if (((int32_T)tmp) > 0) {
      for (i = 0; i < 8; i++) {
        FullDuplex_UDP_DW.In1[i] = rtb_SFunction_o1[i];
      }
    }

    /* End of S-Function (stellaris_lp_sfunc_DataPackin): '<S3>/S-Function' */
    /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */

    /* S-Function (xpcbytepacking): '<S1>/Unpack' */

    /* Byte Unpacking: <S1>/Unpack */
    (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Unpack[0], (uint8_T*)
                 &FullDuplex_UDP_DW.In1[0] + 0, 8);

    /* S-Function (xpcbytepacking): '<S2>/Pack' */

    /* Byte Packing: <S2>/Pack */
    (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 0, (uint8_T*)
                 &FullDuplex_UDP_DW.Unpack[0], 4);
    (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack[0] + 4, (uint8_T*)
                 &FullDuplex_UDP_DW.Unpack[1], 4);

    /* S-Function (stellaris_lp_sfunc_DebugPrint2): '<S2>/DebugPrint2_sfcn' */
    DebugPrint2(FullDuplex_UDP_P.DebugPrint2_sfcn_p1, FullDuplex_UDP_DW.Pack);

    /* S-Function (xpcbytepacking): '<S1>/Pack' */

    /* Byte Packing: <S1>/Pack */
    (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 0, (uint8_T*)
                 &FullDuplex_UDP_DW.Unpack[0], 4);
    (void)memcpy((uint8_T*)&FullDuplex_UDP_DW.Pack_n[0] + 4, (uint8_T*)
                 &FullDuplex_UDP_DW.Unpack[1], 4);

    /* S-Function (stellaris_lp_sfunc_DataPackout): '<S1>/MPComSend' */
    datapacket_put(FullDuplex_UDP_P.MPComSend_p1, 8, FullDuplex_UDP_DW.Pack_n);
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
    int32_T i;

    /* Start for S-Function (stellaris_lp_sfunc_DataPackin): '<S3>/S-Function' */
    init_datapacket(FullDuplex_UDP_P.SFunction_p1, 8,
                    FullDuplex_UDP_P.SFunction_p3);

    /* Start for S-Function (stellaris_lp_sfunc_DataPackout): '<S1>/MPComSend' */
    init_datapacket(FullDuplex_UDP_P.MPComSend_p1, FullDuplex_UDP_P.MPComSend_p2,
                    8);

    /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
    /* SystemInitialize for Outport: '<S4>/Out1' */
    for (i = 0; i < 8; i++) {
      FullDuplex_UDP_DW.In1[i] = FullDuplex_UDP_P.Out1_Y0;
    }

    /* End of SystemInitialize for Outport: '<S4>/Out1' */
    /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  }
}

/* Model terminate function */
void FullDuplex_UDP_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
