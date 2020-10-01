#include<iostream>
#include<vector>
#include "operation.h"
#include "tensor.h"

using namespace std;

template <typename T>
Tensor<T>* MulOperation<T>::forward() {
	return new Tensor<T>(this->one->val * this->two->val);
}

template <typename T>
void MulOperation<T>::backprop(vector<T> grad) {
	vector<T> gradOne;
	vector<T> gradTwo;
	for (int i = 0; i < grad.size(); i++) {
		gradOne.push_back(grad[i] * this->two->val);
		gradTwo.push_back(grad[i] * this->one->val);
	}
	this->one->backprop(gradOne);
	this->two->backprop(gradTwo);
}

template class MulOperation<float>;

