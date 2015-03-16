
#--------------------------------------------------------------------------------------
#
#  Makefile :             Makefile for compiling V1-MT architectures
#
#  Author :               Maria-Jose ESCOBAR 
#  Institution :          Neuromathcomp, INRIA Sophia Antipolis.
#
#  Contact :              Maria-Jose.Escobar@sophia.inria.fr
#
#  Date :                 Project started january 2008.
#
# -----------------------------------------------------------------------------------

CC         = g++ -g -ggdb -Wall

CIMGPATH = ../include/ 
X11PATH = /opt/local/lib

INCLUDES = -I$(shell pwd)/../src	\
	-I$(CIMGPATH)		\
	-I../include 		

LDFLAGS = -L$(X11PATH)	\
	-L.

LIBS = -lABFilter -lX11 -lm -lpthread -Wl
OBJS =	../include/recfilter.o		\
	../include/baserecfilter.o	\
	../include/cimg/cimg_tools.o		\
	../include/instantsynapse.o		\
	../include/cimg/cimg_signal_drawer.o		\
	../include/cell.o  \
	../include/ABFilter.o	

# ---------------------------------------------------------------
#   COMPILATION RULES

all : lib testABFilter 

%.o: %.cpp
	@echo "> Compiling $@..." 
	$(CC) -c $(@:.o=.cpp) $(CFLAGS) $(INCLUDES) -o $@

testABFilter: testABFilter.o
	@echo "> Generating $@..."
	$(CC) $(CFLAGS) testABFilter.o $(LDFLAGS) $(LIBS) -o $@

lib: $(OBJS) 
	ar cr libABFilter.a $(OBJS) 

clean:
	rm -f test ../include/*.o ../include/cimg/*.o *.o *~ testABFilter libABFilter.a






