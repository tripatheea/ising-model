CXX = g++
# CXXFLAGS= -O3 -Wall -Woverloaded-virtual -g -std=c++11
CXXFLAGS= -O0 -g -ggdb -Wall -Woverloaded-virtual -g -std=c++11

OBJDIR=src
EXECDIR=exec
BINDIR=bin
INCDIR=interface
INC= -I$(INCDIR)

_OBJ = Vertex Lattice System
OBJ  = $(patsubst %,$(OBJDIR)/%,$(_OBJ:=.o))


_EXEC=test
EXEC=$(patsubst %,$(EXECDIR)/%,$(_EXEC:=.o))
BIN=$(patsubst %,$(BINDIR)/%,$(_EXEC))


all: $(BIN)

$(OBJDIR)/%.o : $(OBJDIR)/%.cc
	$(CXX) -I/usr/include/python2.7 -c -o $@ $< $(CXXFLAGS) $(INC) -lpython2.7 

$(EXECDIR)/%.o : $(EXECDIR)/%.cc
	$(CXX) -I/usr/include/python2.7 -c -o $@ $< $(CXXFLAGS) $(INC) -lpython2.7 
	
$(BINDIR)/% : $(EXECDIR)/%.o $(OBJ)
	$(CXX) -I/usr/include/python2.7 $< $(OBJ) -o $@ $(CXXFLAGS) -lpython2.7

.PHONY: clean
.PRECIOUS: $(OBJ) $(EXEC)

clean:
	rm $(OBJ) $(EXEC) $(BIN)
