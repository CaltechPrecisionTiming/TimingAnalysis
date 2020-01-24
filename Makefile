CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)
INC = $(shell pwd)

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore
CPPFLAGS += -g -std=c++14 -I$(INC)/include

TARGET = analyzeBTL
TARGET1 = analyzeETL
TARGET2 = analyzeETL_Scope
TARGET3 = get_minimum_time_resolution

SRC = app/analyzeBTL.cc src/pulse.cc
SRC1 = app/analyzeETL.cc src/pulse.cc src/pulseScope.cc
SRC2 = app/analyzeETL_Scope.cc src/pulse.cc src/pulseScope.cc
SRC3 = app/get_minimum_time_resolution.cc

OBJ = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ3 = $(SRC3:.cc=.o)

TARGETS = $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3)

all : $(TARGETS)

$(TARGET) : $(OBJ)
	@echo $@
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

$(TARGET1) : $(OBJ1)
	@echo $@
	$(LD) $(CPPFLAGS) -o $(TARGET1) $(OBJ1) $(LDFLAGS)

$(TARGET2) : $(OBJ2)
	@echo $@
	$(LD) $(CPPFLAGS) -o $(TARGET2) $(OBJ2) $(LDFLAGS)

$(TARGET3) : $(OBJ3)
	@echo $@
	$(LD) $(CPPFLAGS) -o $(TARGET3) $(OBJ3) $(LDFLAGS)

%.o : %.cc
	@echo $@
	$(CXX) $(CPPFLAGS) -o $@ -c $<
clean :
	rm -rf *.o app/*.o src/*.o $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3) *~ *.dSYM
