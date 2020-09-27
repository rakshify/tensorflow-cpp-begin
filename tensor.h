#include<vector>
#include "operation.h"

using namespace std;


#ifndef TENSOR_H
#define TENSOR_H

template <typename T>
class Tensor {
	public:
		T val;
		vector<T> grad;
		Operation<T>* frontOp = NULL;
		Operation<T>* backOp = NULL;

		Tensor<T> ();

		Tensor<T> (T v) {
			this->val = v;
			this->grad.push_back(1);
		}
		
		Tensor<T>* forward();
		
		void backprop(vector<T> grad);
		
		Tensor<T>* operator*(const Tensor<T>* two);
		
		Tensor<T>* operator+(const Tensor<T>* two);
};

#endif

