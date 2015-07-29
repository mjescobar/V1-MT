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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Sources/CommandManager.o \
	${OBJECTDIR}/Sources/HashEntry.o \
	${OBJECTDIR}/Sources/HashTable.o \
	${OBJECTDIR}/Sources/InterpreterManager.Init.o \
	${OBJECTDIR}/Sources/InterpreterManager.o \
	${OBJECTDIR}/Sources/LogManager.Init.o \
	${OBJECTDIR}/Sources/LogManager.o \
	${OBJECTDIR}/Sources/NeuronmentCommand.o \
	${OBJECTDIR}/Sources/Simulator.o \
	${OBJECTDIR}/Sources/SimulatorManager.o \
	${OBJECTDIR}/Sources/VariableManager.o \
	${OBJECTDIR}/Sources/main.o \
	${OBJECTDIR}/Sources/tools.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Sources/CommandManager.o: Sources/CommandManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/CommandManager.o Sources/CommandManager.cpp

${OBJECTDIR}/Sources/HashEntry.o: Sources/HashEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/HashEntry.o Sources/HashEntry.cpp

${OBJECTDIR}/Sources/HashTable.o: Sources/HashTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/HashTable.o Sources/HashTable.cpp

${OBJECTDIR}/Sources/InterpreterManager.Init.o: Sources/InterpreterManager.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/InterpreterManager.Init.o Sources/InterpreterManager.Init.cpp

${OBJECTDIR}/Sources/InterpreterManager.o: Sources/InterpreterManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/InterpreterManager.o Sources/InterpreterManager.cpp

${OBJECTDIR}/Sources/LogManager.Init.o: Sources/LogManager.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/LogManager.Init.o Sources/LogManager.Init.cpp

${OBJECTDIR}/Sources/LogManager.o: Sources/LogManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/LogManager.o Sources/LogManager.cpp

${OBJECTDIR}/Sources/NeuronmentCommand.o: Sources/NeuronmentCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/NeuronmentCommand.o Sources/NeuronmentCommand.cpp

${OBJECTDIR}/Sources/Simulator.o: Sources/Simulator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Simulator.o Sources/Simulator.cpp

${OBJECTDIR}/Sources/SimulatorManager.o: Sources/SimulatorManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/SimulatorManager.o Sources/SimulatorManager.cpp

${OBJECTDIR}/Sources/VariableManager.o: Sources/VariableManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/VariableManager.o Sources/VariableManager.cpp

${OBJECTDIR}/Sources/main.o: Sources/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/main.o Sources/main.cpp

${OBJECTDIR}/Sources/tools.o: Sources/tools.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/tools.o Sources/tools.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
