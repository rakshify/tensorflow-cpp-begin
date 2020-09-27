#include<vector>
//#include "tensor.h"

using namespace std;


#ifndef OPERATION_H
#define OPERATION_H

template <typename T>
class Tensor;


template <typename T>
class Operation {
	public:
		Tensor<T>* one;
		Tensor<T>* two;

		Operation () {};

		virtual Tensor<T>* forward() {
			return NULL;
		}

		virtual void backprop(vector<T> grad) {};
};


template <typename T>
class MulOperation : public Operation<T> {
	public:
		MulOperation(Tensor<T>* one, Tensor<T>* two) {
			this->one = one;
			this->two = two;
		}

		Tensor<T>* forward();

		void backprop(vector<T> grad);
};


template <typename T>
class AddOperation : public Operation<T> {
	public:
		AddOperation(Tensor<T>* one, Tensor<T>* two) {
			this->one = one;
			this->two = two;
		}

		Tensor<T>* forward();

		void backprop(vector<T> grad);
};

#endif

