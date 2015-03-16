
CC         = g++ 

LOCALPATH = $(PWD) 

X11PATH = /usr/lib/X11/

INCLUDES = -I../GA-FilterResponse/ \
        -I../GA-Individual/ \
        -I../GA-MultithreadManager/ \
        -I../GA-Population/ \
        -I../GA-UniversalStorage/ \
        -I../GA-V1MTSimulator/ \
        -I../GA-Tools/

CFLAGS = -g -Wall 

LDFLAGS = -L../ABFilter-v1.5/src -L$(X11PATH)	\

LIBS = -lABFilter -lm -lpthread 
OBJS =  ../GA-FilterResponse/FilterResponse.o \
        ../GA-Individual/Individual.o \
        ../GA-MultithreadManager/MultithreadManager.o \
        ../GA-Population/Population.o \
        ../GA-UniversalStorage/UniversalStorage.o \
        ../GA-V1MTSimulator/V1MTSimulator.o \
        ../GA-V1MTSimulator/MTNeuron.o \
        ../GA-V1MTSimulator/V1Neuron.o \
        ../GA-Tools/Tools.o \
        main.o
        	

# ---------------------------------------------------------------
#   COMPILATION RULES

all : ga-tester

%.o: %.cpp
	@echo "> Compiling $@..." 
	$(CC) -c $(@:.o=.cpp) $(CFLAGS) $(INCLUDES) -o $@

ga-tester: $(OBJS) 
	@echo "> Generating $@..."
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LDFLAGS) -o $@ $(LIBS)

clean:
	rm -f ga-tester *.o *~ 






