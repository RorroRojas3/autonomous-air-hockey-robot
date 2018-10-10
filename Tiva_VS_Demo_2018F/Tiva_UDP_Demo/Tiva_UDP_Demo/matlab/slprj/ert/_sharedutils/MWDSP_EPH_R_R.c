/*
 * Academic Student License -- for use by students to meet course
 * requirements and perform academic research at degree granting
 * institutions only.  Not for government, commercial, or other
 * organizational use.
 *
 * File: MWDSP_EPH_R_R.c
 *
 * Code generated for Simulink model 'FullDuplex_UDP'.
 *
 * Model version                  : 1.89
 * Simulink Coder version         : 8.12 (R2017a) 16-Feb-2017
 * C/C++ source code generated on : Wed Oct 10 12:34:32 2018
 */

#include "rtwtypes.h"
#include "MWDSP_EPH_R_R.h"

uint32_T MWDSP_EPH_R_R(real32_T evt, uint32_T *sta)
{
  uint32_T retVal;
  int32_T curState;
  int32_T newState;
  int32_T newStateR;
  int32_T lastzcevent;
  uint32_T previousState;

  /* S-Function (sdspcount2): '<S2>/Counter' */
  /* Detect rising edge events */
  previousState = *sta;
  retVal = 0U;
  lastzcevent = 0;
  newState = 5;
  newStateR = 5;
  if (evt > 0.0F) {
    curState = 2;
  } else {
    curState = (int32_T)((!(evt < 0.0F)) ? 1 : 0);
  }

  if (previousState == 5U) {
    newStateR = curState;
  } else {
    if (((uint32_T)curState) != previousState) {
      if (previousState == 3U) {
        if (((uint32_T)curState) == 1U) {
          newStateR = 1;
        } else {
          lastzcevent = 2;
          previousState = 1U;
        }
      }

      if (previousState == 4U) {
        if (((uint32_T)curState) == 1U) {
          newStateR = 1;
        } else {
          lastzcevent = 3;
          previousState = 1U;
        }
      }

      if ((previousState == 1U) && (((uint32_T)curState) == 2U)) {
        retVal = 2U;
      }

      if (previousState == 0U) {
        retVal = 2U;
      }

      if (retVal == ((uint32_T)lastzcevent)) {
        retVal = 0U;
      }

      if ((((uint32_T)curState) == 1U) && (retVal == 2U)) {
        newState = 3;
      } else {
        newState = curState;
      }
    }
  }

  if (((uint32_T)newStateR) != 5U) {
    *sta = (uint32_T)newStateR;
    retVal = 0U;
  }

  if (((uint32_T)newState) != 5U) {
    *sta = (uint32_T)newState;
  }

  /* End of S-Function (sdspcount2): '<S2>/Counter' */
  return retVal;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
