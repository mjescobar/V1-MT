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
	${OBJECTDIR}/FunctionsManager.Init.o \
	${OBJECTDIR}/Sources/CommandLine.o \
	${OBJECTDIR}/Sources/Functions.o \
	${OBJECTDIR}/Sources/FunctionsManager.o \
	${OBJECTDIR}/Sources/HashEntry.o \
	${OBJECTDIR}/Sources/HashTable.o \
	${OBJECTDIR}/Sources/Interpreter.Init.o \
	${OBJECTDIR}/Sources/Interpreter.o \
	${OBJECTDIR}/Sources/InterpreterCommands.o \
	${OBJECTDIR}/Sources/LogManager.Init.o \
	${OBJECTDIR}/Sources/LogManager.o \
	${OBJECTDIR}/Sources/Neuron.o \
	${OBJECTDIR}/Sources/NeuronType.o \
	${OBJECTDIR}/Sources/Simulator.o \
	${OBJECTDIR}/Sources/SimulatorManager.o \
	${OBJECTDIR}/Sources/VariableManager.o \
	${OBJECTDIR}/Sources/main.o \
	${OBJECTDIR}/Sources/tools.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/neuronment ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/FunctionsManager.Init.o: FunctionsManager.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FunctionsManager.Init.o FunctionsManager.Init.cpp

${OBJECTDIR}/Sources/CommandLine.o: Sources/CommandLine.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/CommandLine.o Sources/CommandLine.cpp

${OBJECTDIR}/Sources/Functions.o: Sources/Functions.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Functions.o Sources/Functions.cpp

${OBJECTDIR}/Sources/FunctionsManager.o: Sources/FunctionsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/FunctionsManager.o Sources/FunctionsManager.cpp

${OBJECTDIR}/Sources/HashEntry.o: Sources/HashEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/HashEntry.o Sources/HashEntry.cpp

${OBJECTDIR}/Sources/HashTable.o: Sources/HashTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/HashTable.o Sources/HashTable.cpp

${OBJECTDIR}/Sources/Interpreter.Init.o: Sources/Interpreter.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Interpreter.Init.o Sources/Interpreter.Init.cpp

${OBJECTDIR}/Sources/Interpreter.o: Sources/Interpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Interpreter.o Sources/Interpreter.cpp

${OBJECTDIR}/Sources/InterpreterCommands.o: Sources/InterpreterCommands.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/InterpreterCommands.o Sources/InterpreterCommands.cpp

${OBJECTDIR}/Sources/LogManager.Init.o: Sources/LogManager.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/LogManager.Init.o Sources/LogManager.Init.cpp

${OBJECTDIR}/Sources/LogManager.o: Sources/LogManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/LogManager.o Sources/LogManager.cpp

${OBJECTDIR}/Sources/Neuron.o: Sources/Neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Neuron.o Sources/Neuron.cpp

${OBJECTDIR}/Sources/NeuronType.o: Sources/NeuronType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/NeuronType.o Sources/NeuronType.cpp

${OBJECTDIR}/Sources/Simulator.o: Sources/Simulator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/Simulator.o Sources/Simulator.cpp

${OBJECTDIR}/Sources/SimulatorManager.o: Sources/SimulatorManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/SimulatorManager.o Sources/SimulatorManager.cpp

${OBJECTDIR}/Sources/VariableManager.o: Sources/VariableManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/VariableManager.o Sources/VariableManager.cpp

${OBJECTDIR}/Sources/main.o: Sources/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/main.o Sources/main.cpp

${OBJECTDIR}/Sources/tools.o: Sources/tools.cpp 
	${MKDIR} -p ${OBJECTDIR}/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -IHeaders -ISources -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sources/tools.o Sources/tools.cpp

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
