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
	${OBJECTDIR}/Little.o \
	${OBJECTDIR}/Matrix/TestStats.o \
	${OBJECTDIR}/test.o \
	${OBJECTDIR}/tspParse.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread
CXXFLAGS=-D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Little.o: Little.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -MMD -MP -MF $@.d -o ${OBJECTDIR}/Little.o Little.cpp

${OBJECTDIR}/Matrix/TestStats.o: Matrix/TestStats.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matrix
	${RM} $@.d
	$(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix/TestStats.o Matrix/TestStats.cpp

${OBJECTDIR}/test.o: test.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -MMD -MP -MF $@.d -o ${OBJECTDIR}/test.o test.cpp

${OBJECTDIR}/tspParse.o: tspParse.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -MMD -MP -MF $@.d -o ${OBJECTDIR}/tspParse.o tspParse.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newtestclass.o ${TESTDIR}/tests/newtestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/tests/newtestclass.o: tests/newtestclass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestclass.o tests/newtestclass.cpp


${TESTDIR}/tests/newtestrunner.o: tests/newtestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestrunner.o tests/newtestrunner.cpp


${OBJECTDIR}/Little_nomain.o: ${OBJECTDIR}/Little.o Little.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Little.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Little_nomain.o Little.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Little.o ${OBJECTDIR}/Little_nomain.o;\
	fi

${OBJECTDIR}/Matrix/TestStats_nomain.o: ${OBJECTDIR}/Matrix/TestStats.o Matrix/TestStats.cpp 
	${MKDIR} -p ${OBJECTDIR}/Matrix
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Matrix/TestStats.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Matrix/TestStats_nomain.o Matrix/TestStats.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Matrix/TestStats.o ${OBJECTDIR}/Matrix/TestStats_nomain.o;\
	fi

${OBJECTDIR}/test_nomain.o: ${OBJECTDIR}/test.o test.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/test.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/test_nomain.o test.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/test.o ${OBJECTDIR}/test_nomain.o;\
	fi

${OBJECTDIR}/tspParse_nomain.o: ${OBJECTDIR}/tspParse.o tspParse.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tspParse.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Iwebsocketpp -std=c++11 -D_WEBSOCKETPP_CPP11_STL_ -I websocketpp/ -lboost_system -lboost_thread -lpthread -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/tspParse_nomain.o tspParse.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tspParse.o ${OBJECTDIR}/tspParse_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
