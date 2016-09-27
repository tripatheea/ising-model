CXX = g++
CXXFLAGS= -O3 -Wall -Woverloaded-virtual -g -std=c++11

OBJDIR=src
EXECDIR=exec
BINDIR=bin
INCDIR=interface
INC= -I$(INCDIR)

_OBJ = Vertex Lattice System
OBJ  = $(patsubst %,$(OBJDIR)/%,$(_OBJ:=.o))


_EXEC=ising
EXEC=$(patsubst %,$(EXECDIR)/%,$(_EXEC:=.o))
BIN=$(patsubst %,$(BINDIR)/%,$(_EXEC))


all: $(BIN)

$(OBJDIR)/%.o : $(OBJDIR)/%.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INC)

$(EXECDIR)/%.o : $(EXECDIR)/%.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INC)
	
$(BINDIR)/% : $(EXECDIR)/%.o $(OBJ)
	$(CXX) $< $(OBJ) -o $@ $(CXXFLAGS) 

.PHONY: clean
.PRECIOUS: $(OBJ) $(EXEC)

clean:
	rm $(OBJ) $(EXEC) $(BIN)