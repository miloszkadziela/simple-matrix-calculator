all: testmatrix 

testmatrix: testmatrix.o Matrix.o DifferentSizeException.o MemoryAllocationErrorException.o OutOfBoundsException.o
	g++ -g $^ -o $@

.cpp.o:
	g++ -g -c -Wall -std=c++11 -pedantic $< -o $@

testmatrix.o: testmatrix.cpp 

Matrix.o: Matrix.cpp Matrix.h

DifferentSizeException.o: DifferentSizeException.cpp DifferentSizeException.h

MemoryAllocationErrorException.o: MemoryAllocationErrorException.cpp MemoryAllocationErrorException.h

OutOfBoundsException.o: OutOfBoundsException.cpp OutOfBoundsException.h

.PHONY: clean

run:
	valgrind ./testmatrix

clean:
	-rm Matrix.o DifferentSizeException.o MemoryAllocationErrorException.o OutOfBoundsException.o testmatrix.o testmatrix
