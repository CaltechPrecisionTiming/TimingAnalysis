CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)
INC = $(shell pwd)

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore
CPPFLAGS += -g -std=c++14 -I$(INC)/include 

TARGET = analyzeBTL
TARGET1 = analyzeETL
SRC = app/analyzeBTL.cc src/pulse.cc
SRC1 = app/analyzeETL.cc src/pulse.cc
OBJ = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)

TARGETS = $(TARGET) $(TARGET1) 

all : $(TARGETS)

$(TARGET) : $(OBJ)
	@echo $@
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

$(TARGET1) : $(OBJ1)
	@echo $@
	$(LD) $(CPPFLAGS) -o $(TARGET1) $(OBJ1) $(LDFLAGS)

%.o : %.cc
	@echo $@
	$(CXX) $(CPPFLAGS) -o $@ -c $<
clean :
	rm -rf *.o app/*.o src/*.o $(TARGET) *~ *.dSYM
