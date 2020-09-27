#include<vector>

#include "operation.h"
#include "tensor.h"


template <typename T>
Tensor<T>* Tensor::forward() {
	Tensor<T>* three = this->frontOp->forward();
	three->backOp = this->frontOp;
	return three;
}

template <typename T>
void Tensor::backprop(vector<T> grad) {
	assert("Shape mismatch" && this->grad.size() == grad.size());
	for (int i = 0; i < grad.size(); i++) {
		this->grad[i] *= grad[i];
	}

	if (this->backOp == NULL) return;
	this->backOp->backprop(this->grad);
}

// Overload * operator to add two Tensor objects.
template <typename T>
Tensor<T>* Tensor::operator*(const Tensor<T>* two) {
	this->frontOp = new MulOperation<T>(this, (Tensor<T>*)two);
	return this->forward();
}

// Overload + operator to add two Tensor objects.
template <typename T>
Tensor<T>* Tensor::operator+(const Tensor<T>* two) {
	this->frontOp = new AddOperation<T>(this, (Tensor<T>*)two);
	return this->forward();
}

