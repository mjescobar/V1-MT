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
	${OBJECTDIR}/Code/Sources/CommandLine.o \
	${OBJECTDIR}/Code/Sources/Functions.o \
	${OBJECTDIR}/Code/Sources/FunctionsManager.Init.o \
	${OBJECTDIR}/Code/Sources/FunctionsManager.o \
	${OBJECTDIR}/Code/Sources/HashEntry.o \
	${OBJECTDIR}/Code/Sources/HashTable.o \
	${OBJECTDIR}/Code/Sources/Interpreter.Init.o \
	${OBJECTDIR}/Code/Sources/Interpreter.o \
	${OBJECTDIR}/Code/Sources/InterpreterCommands.o \
	${OBJECTDIR}/Code/Sources/LogManager.Init.o \
	${OBJECTDIR}/Code/Sources/LogManager.o \
	${OBJECTDIR}/Code/Sources/Neuron.o \
	${OBJECTDIR}/Code/Sources/NeuronType.o \
	${OBJECTDIR}/Code/Sources/Simulator.o \
	${OBJECTDIR}/Code/Sources/SimulatorManager.o \
	${OBJECTDIR}/Code/Sources/VariableManager.o \
	${OBJECTDIR}/Code/Sources/main.o \
	${OBJECTDIR}/Code/Sources/tools.o


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

${OBJECTDIR}/Code/Sources/CommandLine.o: Code/Sources/CommandLine.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/CommandLine.o Code/Sources/CommandLine.cpp

${OBJECTDIR}/Code/Sources/Functions.o: Code/Sources/Functions.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/Functions.o Code/Sources/Functions.cpp

${OBJECTDIR}/Code/Sources/FunctionsManager.Init.o: Code/Sources/FunctionsManager.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/FunctionsManager.Init.o Code/Sources/FunctionsManager.Init.cpp

${OBJECTDIR}/Code/Sources/FunctionsManager.o: Code/Sources/FunctionsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/FunctionsManager.o Code/Sources/FunctionsManager.cpp

${OBJECTDIR}/Code/Sources/HashEntry.o: Code/Sources/HashEntry.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/HashEntry.o Code/Sources/HashEntry.cpp

${OBJECTDIR}/Code/Sources/HashTable.o: Code/Sources/HashTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/HashTable.o Code/Sources/HashTable.cpp

${OBJECTDIR}/Code/Sources/Interpreter.Init.o: Code/Sources/Interpreter.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/Interpreter.Init.o Code/Sources/Interpreter.Init.cpp

${OBJECTDIR}/Code/Sources/Interpreter.o: Code/Sources/Interpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/Interpreter.o Code/Sources/Interpreter.cpp

${OBJECTDIR}/Code/Sources/InterpreterCommands.o: Code/Sources/InterpreterCommands.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/InterpreterCommands.o Code/Sources/InterpreterCommands.cpp

${OBJECTDIR}/Code/Sources/LogManager.Init.o: Code/Sources/LogManager.Init.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/LogManager.Init.o Code/Sources/LogManager.Init.cpp

${OBJECTDIR}/Code/Sources/LogManager.o: Code/Sources/LogManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/LogManager.o Code/Sources/LogManager.cpp

${OBJECTDIR}/Code/Sources/Neuron.o: Code/Sources/Neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/Neuron.o Code/Sources/Neuron.cpp

${OBJECTDIR}/Code/Sources/NeuronType.o: Code/Sources/NeuronType.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/NeuronType.o Code/Sources/NeuronType.cpp

${OBJECTDIR}/Code/Sources/Simulator.o: Code/Sources/Simulator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/Simulator.o Code/Sources/Simulator.cpp

${OBJECTDIR}/Code/Sources/SimulatorManager.o: Code/Sources/SimulatorManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/SimulatorManager.o Code/Sources/SimulatorManager.cpp

${OBJECTDIR}/Code/Sources/VariableManager.o: Code/Sources/VariableManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/VariableManager.o Code/Sources/VariableManager.cpp

${OBJECTDIR}/Code/Sources/main.o: Code/Sources/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/main.o Code/Sources/main.cpp

${OBJECTDIR}/Code/Sources/tools.o: Code/Sources/tools.cpp 
	${MKDIR} -p ${OBJECTDIR}/Code/Sources
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Werror -IHeaders -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Code/Sources/tools.o Code/Sources/tools.cpp

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
