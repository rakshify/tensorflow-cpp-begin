#include<iostream>
#include<vector>
#include<assert.h>
#include "tensor.h"


using namespace std;


int main() {
	Tensor<float>* one = new Tensor<float>(2);
	Tensor<float>* two = new Tensor<float>(4);

	Tensor<float>* three = (*one) * two;
	Tensor<float>* four = new Tensor<float>(5);

	Tensor<float>* five = (*three) + four;

	vector<float> grad;
	grad.push_back(1.0);
	five->backprop(grad);

	cout << five->grad[0] << endl;
	cout << four->grad[0] << endl;
	cout << three->grad[0] << endl;
	cout << two->grad[0] << endl;
	cout << one->grad[0] << endl;

	return 0;
}
