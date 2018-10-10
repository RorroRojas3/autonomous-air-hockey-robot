#ifndef PORTABLE_WORDSIZES
#ifdef __MW_TARGET_USE_HARDWARE_RESOURCES_H__
#ifndef __MW_TARGET_HARDWARE_RESOURCES_H__
#define __MW_TARGET_HARDWARE_RESOURCES_H__

#include "stellaris_runtime.h"

#define MW_USECODERTARGET 1
#define MW_TARGETHARDWARE Tiva TM4C123G Launchpad
#define MW_RTOS Baremetal
#define MW_SCHEDULER_INTERRUPT_SOURCE 0
#define MW_CLOCKING_CPUCLOCKRATEMHZ 100
#define MW_DATAVERSION 2016.02
#define MW_MULTI_TASKING_MODE 0

#endif /* __MW_TARGET_HARDWARE_RESOURCES_H__ */

#endif

#endif
