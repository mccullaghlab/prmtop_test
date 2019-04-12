
CXX = g++
LAPACK = /Users/mmccull/lib
OPTS = -O3 -ftree-vectorize

sort: test_main.cpp atom_class.h bond_class.h read_prmtop.h read_prmtop.c 
	$(CXX) -c test_main.cpp  read_prmtop.c $(OPTS) 
	$(CXX) test_main.o read_prmtop.o $(OPTS) -lm -o test_main.x
