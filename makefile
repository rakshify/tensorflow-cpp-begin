all: main.o

main.o: main.cpp tensor.o add_op.o mul_op.o
	g++ main.cpp tensor.o add_op.o mul_op.o -o main.o

#tensor.o: tensor.cpp tensor.h forward.o backprop.o
tensor.o: tensor.cpp tensor.h add_op.o mul_op.o
	g++ -c tensor.cpp -o tensor.o
#	g++ -g -o tensor.o add_op.o mul_op.o
#	g++ -g -o tensor.o forward.o backprop.o

# mul_op.o: mul_operation.cpp operation.h tensor.h forward.o backprop.o
mul_op.o: mul_operation.cpp operation.h tensor.h
	g++ -c mul_operation.cpp -o mul_op.o
#	g++ -g -o mul_op.o forward.o backprop.o

# add_op.o: add_operation.cpp operation.h tensor.h forward.o backprop.o
add_op.o: add_operation.cpp operation.h tensor.h
	g++ -c add_operation.cpp -o add_op.o
#	g++ -g -o add_op.o forward.o backprop.o

# forward.o: forward.cpp operation.h tensor.h
# 	g++ -c forward.cpp -o forward.o
# 
# backprop.o: backprop.cpp operation.h tensor.h
# 	g++ -c backprop.cpp -o backprop.o
