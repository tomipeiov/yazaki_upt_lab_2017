#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-18f452.mk)" "nbproject/Makefile-local-18f452.mk"
include nbproject/Makefile-local-18f452.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=18f452
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=alarm.c boot.c even_man.c int_man.c main.c pro_man.c taskdesc.c timer.c tsk_led.c int.asm kernel.asm tsk_led2.c tsk_led3.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/alarm.o ${OBJECTDIR}/boot.o ${OBJECTDIR}/even_man.o ${OBJECTDIR}/int_man.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pro_man.o ${OBJECTDIR}/taskdesc.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/tsk_led.o ${OBJECTDIR}/int.o ${OBJECTDIR}/kernel.o ${OBJECTDIR}/tsk_led2.o ${OBJECTDIR}/tsk_led3.o
POSSIBLE_DEPFILES=${OBJECTDIR}/alarm.o.d ${OBJECTDIR}/boot.o.d ${OBJECTDIR}/even_man.o.d ${OBJECTDIR}/int_man.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/pro_man.o.d ${OBJECTDIR}/taskdesc.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/tsk_led.o.d ${OBJECTDIR}/int.o.d ${OBJECTDIR}/kernel.o.d ${OBJECTDIR}/tsk_led2.o.d ${OBJECTDIR}/tsk_led3.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/alarm.o ${OBJECTDIR}/boot.o ${OBJECTDIR}/even_man.o ${OBJECTDIR}/int_man.o ${OBJECTDIR}/main.o ${OBJECTDIR}/pro_man.o ${OBJECTDIR}/taskdesc.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/tsk_led.o ${OBJECTDIR}/int.o ${OBJECTDIR}/kernel.o ${OBJECTDIR}/tsk_led2.o ${OBJECTDIR}/tsk_led3.o

# Source Files
SOURCEFILES=alarm.c boot.c even_man.c int_man.c main.c pro_man.c taskdesc.c timer.c tsk_led.c int.asm kernel.asm tsk_led2.c tsk_led3.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-18f452.mk dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F452
MP_PROCESSOR_OPTION_LD=18f452
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/int.o: int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/int.o.d 
	@${RM} ${OBJECTDIR}/int.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/int.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG -d__MPLAB_DEBUGGER_SIMULATOR=1 -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/int.lst\" -e\"${OBJECTDIR}/int.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/int.o\" \"int.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/int.o"
	@${FIXDEPS} "${OBJECTDIR}/int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/kernel.o: kernel.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/kernel.o.d 
	@${RM} ${OBJECTDIR}/kernel.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/kernel.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG -d__MPLAB_DEBUGGER_SIMULATOR=1 -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/kernel.lst\" -e\"${OBJECTDIR}/kernel.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/kernel.o\" \"kernel.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/kernel.o"
	@${FIXDEPS} "${OBJECTDIR}/kernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/int.o: int.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/int.o.d 
	@${RM} ${OBJECTDIR}/int.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/int.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/int.lst\" -e\"${OBJECTDIR}/int.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/int.o\" \"int.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/int.o"
	@${FIXDEPS} "${OBJECTDIR}/int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/kernel.o: kernel.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/kernel.o.d 
	@${RM} ${OBJECTDIR}/kernel.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/kernel.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/kernel.lst\" -e\"${OBJECTDIR}/kernel.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/kernel.o\" \"kernel.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/kernel.o"
	@${FIXDEPS} "${OBJECTDIR}/kernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/alarm.o: alarm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/alarm.o.d 
	@${RM} ${OBJECTDIR}/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/alarm.o   alarm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/alarm.o 
	@${FIXDEPS} "${OBJECTDIR}/alarm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/boot.o: boot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/boot.o.d 
	@${RM} ${OBJECTDIR}/boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/boot.o   boot.c 
	@${DEP_GEN} -d ${OBJECTDIR}/boot.o 
	@${FIXDEPS} "${OBJECTDIR}/boot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/even_man.o: even_man.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/even_man.o.d 
	@${RM} ${OBJECTDIR}/even_man.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/even_man.o   even_man.c 
	@${DEP_GEN} -d ${OBJECTDIR}/even_man.o 
	@${FIXDEPS} "${OBJECTDIR}/even_man.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/int_man.o: int_man.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/int_man.o.d 
	@${RM} ${OBJECTDIR}/int_man.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/int_man.o   int_man.c 
	@${DEP_GEN} -d ${OBJECTDIR}/int_man.o 
	@${FIXDEPS} "${OBJECTDIR}/int_man.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/pro_man.o: pro_man.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pro_man.o.d 
	@${RM} ${OBJECTDIR}/pro_man.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/pro_man.o   pro_man.c 
	@${DEP_GEN} -d ${OBJECTDIR}/pro_man.o 
	@${FIXDEPS} "${OBJECTDIR}/pro_man.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/taskdesc.o: taskdesc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/taskdesc.o.d 
	@${RM} ${OBJECTDIR}/taskdesc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/taskdesc.o   taskdesc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/taskdesc.o 
	@${FIXDEPS} "${OBJECTDIR}/taskdesc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/timer.o   timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/tsk_led.o: tsk_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tsk_led.o.d 
	@${RM} ${OBJECTDIR}/tsk_led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/tsk_led.o   tsk_led.c 
	@${DEP_GEN} -d ${OBJECTDIR}/tsk_led.o 
	@${FIXDEPS} "${OBJECTDIR}/tsk_led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/tsk_led2.o: tsk_led2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tsk_led2.o.d 
	@${RM} ${OBJECTDIR}/tsk_led2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/tsk_led2.o   tsk_led2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/tsk_led2.o 
	@${FIXDEPS} "${OBJECTDIR}/tsk_led2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/tsk_led3.o: tsk_led3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tsk_led3.o.d 
	@${RM} ${OBJECTDIR}/tsk_led3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/tsk_led3.o   tsk_led3.c 
	@${DEP_GEN} -d ${OBJECTDIR}/tsk_led3.o 
	@${FIXDEPS} "${OBJECTDIR}/tsk_led3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/alarm.o: alarm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/alarm.o.d 
	@${RM} ${OBJECTDIR}/alarm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/alarm.o   alarm.c 
	@${DEP_GEN} -d ${OBJECTDIR}/alarm.o 
	@${FIXDEPS} "${OBJECTDIR}/alarm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/boot.o: boot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/boot.o.d 
	@${RM} ${OBJECTDIR}/boot.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/boot.o   boot.c 
	@${DEP_GEN} -d ${OBJECTDIR}/boot.o 
	@${FIXDEPS} "${OBJECTDIR}/boot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/even_man.o: even_man.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/even_man.o.d 
	@${RM} ${OBJECTDIR}/even_man.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/even_man.o   even_man.c 
	@${DEP_GEN} -d ${OBJECTDIR}/even_man.o 
	@${FIXDEPS} "${OBJECTDIR}/even_man.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/int_man.o: int_man.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/int_man.o.d 
	@${RM} ${OBJECTDIR}/int_man.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/int_man.o   int_man.c 
	@${DEP_GEN} -d ${OBJECTDIR}/int_man.o 
	@${FIXDEPS} "${OBJECTDIR}/int_man.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/pro_man.o: pro_man.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pro_man.o.d 
	@${RM} ${OBJECTDIR}/pro_man.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/pro_man.o   pro_man.c 
	@${DEP_GEN} -d ${OBJECTDIR}/pro_man.o 
	@${FIXDEPS} "${OBJECTDIR}/pro_man.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/taskdesc.o: taskdesc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/taskdesc.o.d 
	@${RM} ${OBJECTDIR}/taskdesc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/taskdesc.o   taskdesc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/taskdesc.o 
	@${FIXDEPS} "${OBJECTDIR}/taskdesc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/timer.o   timer.c 
	@${DEP_GEN} -d ${OBJECTDIR}/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/tsk_led.o: tsk_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tsk_led.o.d 
	@${RM} ${OBJECTDIR}/tsk_led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/tsk_led.o   tsk_led.c 
	@${DEP_GEN} -d ${OBJECTDIR}/tsk_led.o 
	@${FIXDEPS} "${OBJECTDIR}/tsk_led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/tsk_led2.o: tsk_led2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tsk_led2.o.d 
	@${RM} ${OBJECTDIR}/tsk_led2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/tsk_led2.o   tsk_led2.c 
	@${DEP_GEN} -d ${OBJECTDIR}/tsk_led2.o 
	@${FIXDEPS} "${OBJECTDIR}/tsk_led2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/tsk_led3.o: tsk_led3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tsk_led3.o.d 
	@${RM} ${OBJECTDIR}/tsk_led3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/tsk_led3.o   tsk_led3.c 
	@${DEP_GEN} -d ${OBJECTDIR}/tsk_led3.o 
	@${FIXDEPS} "${OBJECTDIR}/tsk_led3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    18f452.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "18f452.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_SIMULATOR=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   18f452.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "18f452.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/PICOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/18f452
	${RM} -r dist/18f452

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
