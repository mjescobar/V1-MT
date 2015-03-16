#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Sources/Globals.o \
	${OBJECTDIR}/Sources/HashEntry.o \
	${OBJECTDIR}/Sources/HashTable.o \
	${OBJECTDIR}/Sources/InterpreterManager.Initialize.o \
	${OBJECTDIR}/Sources/InterpreterManager.o \
	${OBJECTDIR}/Sources/LogManager.Initialize.o \
	${OBJECTDIR}/Sources/LogManager.o \
	${OBJECTDIR}/Sources/MT_Neuron.o \
	${OBJECTDIR}/Sources/ND_Neuron.o \
	${OBJECTDIR}/Sources/SettingsManager.Initialize.o \
	${OBJECTDIR}/Sources/SettingsManager.o \
	${OBJECTDIR}/Sources/SimulationManager.o \
	${OBJECTDIR}/Sources/Tools.o \
	${OBJECTDIR}/Sources/V1_Neuron.o \
	${OBJECTDIR}/Sources/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -DDEVELOPMENT
CXXFLAGS=-m64 -DDEVELOPMENT

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment_v1.0

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment_v1.0: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment_v1.0 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Sources/Globals.o: Sources/Globals.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Globals.o Sources/Globals.cpp

${OBJECTDIR}/Sources/HashEntry.o: Sources/HashEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/HashEntry.o Sources/HashEntry.cpp

${OBJECTDIR}/Sources/HashTable.o: Sources/HashTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/HashTable.o Sources/HashTable.cpp

${OBJECTDIR}/Sources/InterpreterManager.Initialize.o: Sources/InterpreterManager.Initialize.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/InterpreterManager.Initialize.o Sources/InterpreterManager.Initialize.cpp

${OBJECTDIR}/Sources/InterpreterManager.o: Sources/InterpreterManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/InterpreterManager.o Sources/InterpreterManager.cpp

${OBJECTDIR}/Sources/LogManager.Initialize.o: Sources/LogManager.Initialize.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/LogManager.Initialize.o Sources/LogManager.Initialize.cpp

${OBJECTDIR}/Sources/LogManager.o: Sources/LogManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/LogManager.o Sources/LogManager.cpp

${OBJECTDIR}/Sources/MT_Neuron.o: Sources/MT_Neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/MT_Neuron.o Sources/MT_Neuron.cpp

${OBJECTDIR}/Sources/ND_Neuron.o: Sources/ND_Neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/ND_Neuron.o Sources/ND_Neuron.cpp

${OBJECTDIR}/Sources/SettingsManager.Initialize.o: Sources/SettingsManager.Initialize.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/SettingsManager.Initialize.o Sources/SettingsManager.Initialize.cpp

${OBJECTDIR}/Sources/SettingsManager.o: Sources/SettingsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/SettingsManager.o Sources/SettingsManager.cpp

${OBJECTDIR}/Sources/SimulationManager.o: Sources/SimulationManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/SimulationManager.o Sources/SimulationManager.cpp

${OBJECTDIR}/Sources/Tools.o: Sources/Tools.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Tools.o Sources/Tools.cpp

${OBJECTDIR}/Sources/V1_Neuron.o: Sources/V1_Neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/V1_Neuron.o Sources/V1_Neuron.cpp

${OBJECTDIR}/Sources/main.o: Sources/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -IDocumentation -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/main.o Sources/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment_v1.0

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
