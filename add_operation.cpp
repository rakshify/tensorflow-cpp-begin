#include<iostream>
#include<vector>
#include "tensor.h"
#include "operation.h"

using namespace std;

template <typename T>
Tensor<T>* AddOperation<T>::forward() {
	return new Tensor<T>(this->one->val + this->two->val);
}

template <typename T>
void AddOperation<T>::backprop(vector<T> grad) {
	this->one->backprop(grad);
	this->two->backprop(grad);
}

template class AddOperation<float>;

