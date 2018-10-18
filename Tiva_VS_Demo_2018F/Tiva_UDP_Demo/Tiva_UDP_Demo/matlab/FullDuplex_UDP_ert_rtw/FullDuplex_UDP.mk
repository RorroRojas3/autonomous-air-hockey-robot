###########################################################################
## Makefile generated for Simulink model 'FullDuplex_UDP'. 
## 
## Makefile     : FullDuplex_UDP.mk
## Generated on : Thu Oct 18 17:16:53 2018
## MATLAB Coder version: 3.3 (R2017a)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/FullDuplex_UDP.out
## Product type : executable
## Build type   : Top-Level Standalone Executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.
# SHARED_OBJS             Shared Object Names

PRODUCT_NAME              = FullDuplex_UDP
MAKEFILE                  = FullDuplex_UDP.mk
COMPUTER                  = PCWIN64
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2017a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2017a/bin
MATLAB_ARCH_BIN           = C:/PROGRA~1/MATLAB/R2017a/bin/win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:/Users/Rorro/Documents/github/autonomous-air-hockey-robot/Tiva_VS_Demo_2018F/Tiva_UDP_Demo/Tiva_UDP_Demo/matlab
ARCH                      = win64
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = None
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
MODELREF_LINK_RSPFILE_NAME = FullDuplex_UDP_ref.rsp
RELATIVE_PATH_TO_ANCHOR   = ..
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
SHARED_SRC_DIR            = ../slprj/ert/_sharedutils
SHARED_SRC                = $(SHARED_SRC_DIR)/*.c
SHARED_BIN_DIR            = ../slprj/ert/_sharedutils
SHARED_LIB                = $(SHARED_BIN_DIR)/rtwshared.lib
SHARED_OBJS               =  \
$(addprefix $(join $(SHARED_BIN_DIR),/), $(addsuffix .obj, $(basename $(notdir $(wildcard $(SHARED_SRC_DIR)/*.c)))))

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Stellaris Code Generation Tools v6.0.0 | gmake (64-bit Windows)
# Supported Version(s):    
# ToolchainInfo Version:   R2017a
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

CCSINSTALLDIR     = C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS
STELLARISWARE_DIR = C:/StellarisWare
SUPPORT_PKG_DIR   = C:/MATLAB/SupportPackages/Tiva_TM4C123G
TI_TOOLS          = $(CCSINSTALLDIR)/bin
TI_INCLUDE        = $(CCSINSTALLDIR)/include
TI_LIB            = $(CCSINSTALLDIR)/lib
CCOUTPUTFLAG      = --output_file=
LDOUTPUTFLAG      = --output_file=
EXE_FILE_EXT      = $(PROGRAM_FILE_EXT)
PRODUCT_BIN       = $(RELATIVE_PATH_TO_ANCHOR)/$(PRODUCT_NAME).bin

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: ARM C Compiler
AS_PATH = $(TI_TOOLS)
AS = $(AS_PATH)/armcl

# C Compiler: ARM C Compiler
CC_PATH = $(TI_TOOLS)
CC = $(CC_PATH)/armcl

# Linker: ARM Linker
LD_PATH = $(TI_TOOLS)
LD = $(LD_PATH)/armlnk

# C++ Compiler: ARM C++ Compiler
CPP_PATH = $(TI_TOOLS)
CPP = $(CPP_PATH)/armcl

# C++ Linker: ARM Linker
CPP_LD_PATH = $(TI_TOOLS)
CPP_LD = $(CPP_LD_PATH)/armlnk

# Archiver: ARM Archiver
AR_PATH = $(TI_TOOLS)
AR = $(AR_PATH)/armar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = $(MEX_PATH)/mex

# Bin Converter: Bin Converter

# Download: Download
DOWNLOAD_PATH = $(SUPPORT_PKG_DIR)/utils/lm4flash
DOWNLOAD = $(DOWNLOAD_PATH)/lmflash.exe

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = $(MAKE_PATH)/gmake


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = --output_file=
CDEBUG              = -g
C_OUTPUT_FLAG       = --output_file=
LDDEBUG             = -g
OUTPUT_FLAG         = --output_file=
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = --output_file=
CPPLDDEBUG          = -g
OUTPUT_FLAG         = --output_file=
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = -r
ASFLAGS              = --compile_only \
                       --compile_only \
                       -mv7M4 \
                       --code_state=16 \
                       --float_support=FPv4SPD16 \
                       --abi=eabi \
                       -me \
                       -O2 \
                       -mf4 \
                       --define="PART_LM4F120H5QR=" \
                       --define="TARGET_IS_BLIZZARD_RA1=" \
                       --define="UART_BUFFERED=1" \
                       -I"$(SUPPORT_PKG_DIR)/src" \
                       -I"$(SUPPORT_PKG_DIR)/blocks/stellaris_lp_lct" \
                       -I"$(STELLARISWARE_DIR)" \
                       -I"$(TI_INCLUDE)"
OBJCOPYFLAGS_HEX     =  "$<" "$@" "$(TI_TOOLS)/armofd" "$(TI_TOOLS)/armhex" "$(SUPPORT_PKG_DIR)/utils/tiobj2bin/mkhex4bin" 
CFLAGS               = --compile_only \
                       -mv7M4 \
                       --code_state=16 \
                       --float_support=FPv4SPD16 \
                       --abi=eabi \
                       -me \
                       -O2 \
                       -mf4 \
                       --define="PART_LM4F120H5QR=" \
                       --define="TARGET_IS_BLIZZARD_RA1=" \
                       --define="UART_BUFFERED=1" \
                       -I"$(SUPPORT_PKG_DIR)/src" \
                       -I"$(SUPPORT_PKG_DIR)/blocks/stellaris_lp_lct" \
                       -I"$(STELLARISWARE_DIR)" \
                       -I"$(TI_INCLUDE)"
CPPFLAGS             = --compile_only \
                       -mv7M4 \
                       --code_state=16 \
                       --float_support=FPv4SPD16 \
                       --abi=eabi \
                       -me \
                       -O2 \
                       -mf4 \
                       --define="PART_LM4F120H5QR=" \
                       --define="TARGET_IS_BLIZZARD_RA1=" \
                       --define="UART_BUFFERED=1" \
                       -I"$(SUPPORT_PKG_DIR)/src" \
                       -I"$(SUPPORT_PKG_DIR)/blocks/stellaris_lp_lct" \
                       -I"$(STELLARISWARE_DIR)" \
                       -I"$(TI_INCLUDE)"
CPP_LDFLAGS          = -I$(TI_LIB) \
                       --stack_size=4096 \
                       --heap_size=4096 \
                       --warn_sections \
                       --reread_libs \
                       --rom_model \
                       "$(SUPPORT_PKG_DIR)/utils/stellaris_link.cmd"
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       =  -q ek-lm4f120xl --erase=all -r $(PRODUCT_BIN)
EXECUTE_FLAGS        =
LDFLAGS              = -I$(TI_LIB) \
                       --stack_size=4096 \
                       --heap_size=4096 \
                       --warn_sections \
                       --reread_libs \
                       --rom_model \
                       "$(SUPPORT_PKG_DIR)/utils/stellaris_link.cmd"
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -B -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -I$(TI_LIB) \
                       --stack_size=4096 \
                       --heap_size=4096 \
                       --warn_sections \
                       --reread_libs \
                       --rom_model \
                       "$(SUPPORT_PKG_DIR)/utils/stellaris_link.cmd" \
                       -dll -def:$(DEF_FILE)

#--------------------
# File extensions
#--------------------

OBJ_EXT             = .obj
ASM_EXT             = .asm
AS_EXT              = .asm
CLA_EXT             = .cla
H_EXT               = .h
OBJ_EXT             = .obj
C_EXT               = .c
EXE_EXT             = .out
SHAREDLIB_EXT       =
HPP_EXT             = .hpp
OBJ_EXT             = .obj
CPP_EXT             = .cpp
EXE_EXT             = .out
SHAREDLIB_EXT       =
STATICLIB_EXT       = .lib
MEX_EXT             = .mexw64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/FullDuplex_UDP.out
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(MATLAB_ROOT)/simulink/include/sf_runtime -I$(START_DIR)/FullDuplex_UDP_ert_rtw -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -I$(START_DIR)/slprj/ert/_sharedutils -I$(MATLAB_ROOT)/toolbox/dsp/include -I$(MATLAB_ROOT)/toolbox/dsp/extern/src/export/include/src -I$(MATLAB_ROOT)/toolbox/dsp/extern/src/export/include -I$(MATLAB_ROOT)/toolbox/shared/dsp/vision/matlab/include -I$(MATLAB_ROOT)/simulink/include/messages

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -DMODEL=FullDuplex_UDP -DNUMST=3 -DNCSTATES=0 -DHAVESTDIO -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DSTACK_SIZE=64 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT
DEFINES_BUILD_ARGS = -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0
DEFINES_IMPLIED = -DTID01EQ=0
DEFINES_SKIPFORSIL = -DSTACK_SIZE=64 -DRT
DEFINES_STANDARD = -DMODEL=FullDuplex_UDP -DNUMST=3 -DNCSTATES=0 -DHAVESTDIO

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_IMPLIED) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/FullDuplex_UDP_ert_rtw/FullDuplex_UDP.c $(START_DIR)/FullDuplex_UDP_ert_rtw/FullDuplex_UDP_data.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/I2C_Stellaris_API.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/ringbuf.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/rtiostreamserial_mp.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/ssi_API.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/startup_ccs.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/stellaris_runtime.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/stellaris_timer.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/uart_driver_mp.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/uartx_driver.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/xprintf.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/rtiostream_serial.cpp C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/reentrance.asm C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/buttonslct.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/datapacket.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/gpiolct.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/ls7366r.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/mpu6050.c C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/xdatapacket.c

MAIN_SRC = $(START_DIR)/FullDuplex_UDP_ert_rtw/ert_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = FullDuplex_UDP.obj FullDuplex_UDP_data.obj I2C_Stellaris_API.obj ringbuf.obj rtiostreamserial_mp.obj ssi_API.obj startup_ccs.obj stellaris_runtime.obj stellaris_timer.obj uart_driver_mp.obj uartx_driver.obj xprintf.obj rtiostream_serial.obj reentrance.obj buttonslct.obj datapacket.obj gpiolct.obj ls7366r.obj mpu6050.obj xdatapacket.obj

MAIN_OBJ = ert_main.obj

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = $(SHARED_LIB)

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


all :

ifeq ($(PRODUCT_TYPE),"executable")
postbuild : $(PRODUCT_BIN)

$(PRODUCT_BIN): $(PRODUCT)
	@echo "### Invoking postbuild tool "Bin Converter" on "$<"..."
	$(SUPPORT_PKG_DIR)/utils/tiobj2bin/tiobj2bin.bat $(OBJCOPYFLAGS_HEX)
	@echo "### Done Invoking postbuild tool "Bin Converter" ..."

endif



-include codertarget_assembly_flags.mk
-include ../codertarget_assembly_flags.mk


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild postbuild download execute


all : build postbuild
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


postbuild : build


download : postbuild
	@echo "### Invoking postbuild tool "Download" ..."
	$(DOWNLOAD) $(DOWNLOAD_FLAGS)
	@echo "### Done invoking postbuild tool."


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(CPP_LD) $(CPP_LDFLAGS) --output_file=$(PRODUCT) $(OBJS) $(MAIN_OBJ) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : %.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : %.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/toolbox/rtw/targets/xpc/target/build/xpcblocks/%.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/toolbox/rtw/targets/xpc/target/build/xpcblocks/%.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/toolbox/rtw/targets/xpc/target/build/xpcblocks/%.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/toolbox/rtw/targets/xpc/target/build/xpcblocks/%.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/%.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/%.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/FullDuplex_UDP_ert_rtw/%.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/FullDuplex_UDP_ert_rtw/%.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/FullDuplex_UDP_ert_rtw/%.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : $(START_DIR)/FullDuplex_UDP_ert_rtw/%.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/simulink/src/%.cla
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/simulink/src/%.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


I2C_Stellaris_API.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/I2C_Stellaris_API.c
	$(CC) $(CFLAGS) --output_file=$@ $<


ringbuf.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/ringbuf.c
	$(CC) $(CFLAGS) --output_file=$@ $<


rtiostreamserial_mp.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/rtiostreamserial_mp.c
	$(CC) $(CFLAGS) --output_file=$@ $<


ssi_API.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/ssi_API.c
	$(CC) $(CFLAGS) --output_file=$@ $<


startup_ccs.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/startup_ccs.c
	$(CC) $(CFLAGS) --output_file=$@ $<


stellaris_runtime.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/stellaris_runtime.c
	$(CC) $(CFLAGS) --output_file=$@ $<


stellaris_timer.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/stellaris_timer.c
	$(CC) $(CFLAGS) --output_file=$@ $<


uart_driver_mp.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/uart_driver_mp.c
	$(CC) $(CFLAGS) --output_file=$@ $<


uartx_driver.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/uartx_driver.c
	$(CC) $(CFLAGS) --output_file=$@ $<


xprintf.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/xprintf.c
	$(CC) $(CFLAGS) --output_file=$@ $<


rtiostream_serial.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/rtiostream_serial.cpp
	$(CPP) $(CPPFLAGS) --output_file=$@ $<


reentrance.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../src/reentrance.asm
	$(AS) $(ASFLAGS) --output_file=$@ $<


buttonslct.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/buttonslct.c
	$(CC) $(CFLAGS) --output_file=$@ $<


datapacket.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/datapacket.c
	$(CC) $(CFLAGS) --output_file=$@ $<


gpiolct.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/gpiolct.c
	$(CC) $(CFLAGS) --output_file=$@ $<


ls7366r.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/ls7366r.c
	$(CC) $(CFLAGS) --output_file=$@ $<


mpu6050.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/mpu6050.c
	$(CC) $(CFLAGS) --output_file=$@ $<


xdatapacket.obj : C:/MATLAB/SupportPackages/Tiva_TM4C123G/target/../blocks/stellaris_lp_lct/xdatapacket.c
	$(CC) $(CFLAGS) --output_file=$@ $<


$(SHARED_BIN_DIR)/%.obj : $(SHARED_SRC_DIR)/%.c
	@echo "### Compiling $< ..."
	$(CC) $(CFLAGS) --output_file=$@ $<


#---------------------------
# SHARED UTILITY LIBRARY
#---------------------------

$(SHARED_LIB) : $(SHARED_OBJS)
	@echo "### Creating shared utilities library "$(SHARED_LIB)" ..."
	$(AR) $(ARFLAGS)  $(SHARED_LIB) $(SHARED_OBJS)
	@echo "### Created: $(SHARED_LIB)"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### ASFLAGS = $(ASFLAGS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### OBJCOPYFLAGS_HEX = $(OBJCOPYFLAGS_HEX)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(ECHO) "### Deleted all derived files."


