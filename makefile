all: main.o

main.o: tensor.o main.cpp
	g++ main.cpp tensor.o -o main.o

tensor.o: tensor.cpp tensor.h add_op.o mul_op.o
	g++ -g -c tensor.cpp -o tensor.o

mul_op.o: mul_operation.cpp operation.h tensor.h
	g++ -g -c mul_operation.cpp -o mul_op.o

add_op.o: add_operation.cpp operation.h tensor.h
	g++ -g -c add_operation.cpp -o add_op.o

