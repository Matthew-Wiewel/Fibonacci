fib: fib.o MyInt.o
	g++ -g -o fib fib.o MyInt.o
fib.o: fib.cpp MyInt.h
	g++ -c fib.cpp MyInt.h
MyInt.o: MyInt.cpp MyInt.h
	g++ -c MyInt.cpp MyInt.h
clean:
	erase fib.o MyInt.o
