
CXX = g++
LAPACK = /Users/mmccull/lib
OPTS = -O3 -ftree-vectorize

sort: test_main.cpp atom_class.h atom_class.cpp bond_class.h bond_class.cpp config_class.h stringlib.h stringlib.c
	$(CXX) -c test_main.cpp stringlib.c bond_class.cpp atom_class.cpp $(OPTS) 
	$(CXX) test_main.o stringlib.o bond_class.o atom_class.o $(OPTS) -lm -o test_main.x

sep: test_main.cpp atom_class.h bond_class.h read_prmtop.h read_prmtop.cpp
	$(CXX) -c test_main.cpp  read_prmtop.cpp $(OPTS) 
	$(CXX) test_main.o read_prmtop.o $(OPTS) -lm -o test_main.x
