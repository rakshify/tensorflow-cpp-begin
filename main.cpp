#include<iostream>
#include<vector>
#include<assert.h>


using namespace std;


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


template <typename T>
class Tensor {
	public:
		T val;
		vector<T> grad;
		Operation<T>* frontOp = NULL;
		Operation<T>* backOp = NULL;

		Tensor<T> () {};

		Tensor<T> (T v) {
			this->val = v;
			this->grad.push_back(1);
		}

		Tensor<T>* forward() {
			Tensor<T>* three = this->frontOp->forward();
			three->backOp = this->frontOp;
			return three;
		}

		void backprop(vector<T> grad) {
			assert("Shape mismatch" && this->grad.size() == grad.size());
			for (int i = 0; i < grad.size(); i++) {
				this->grad[i] *= grad[i];
			}

			if (this->backOp == NULL) return;
			this->backOp->backprop(this->grad);
		}

		// Overload * operator to add two Tensor objects.
		Tensor<T>* operator*(const Tensor<T>* two) {
			this->frontOp = new MulOperation<T>(this, (Tensor<T>*)two);
			return this->forward();
		}

		// Overload + operator to add two Tensor objects.
		Tensor<T>* operator+(const Tensor<T>* two) {
			this->frontOp = new AddOperation<T>(this, (Tensor<T>*)two);
			return this->forward();
		}
};


template <typename T>
Tensor<T>* MulOperation<T>::forward() {
	return new Tensor<T>(this->one->val * this->two->val);
}


template <typename T>
Tensor<T>* AddOperation<T>::forward() {
	return new Tensor<T>(this->one->val + this->two->val);
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


template <typename T>
void AddOperation<T>::backprop(vector<T> grad) {
	this->one->backprop(grad);
	this->two->backprop(grad);
}


int main() {
	Tensor<float>* one = new Tensor<float>(2);
	Tensor<float>* two = new Tensor<float>(4);

	Tensor<float>* three = (*one) * two;
	Tensor<float>* four = new Tensor<float>(5);

	Tensor<float>* five = (*three) + four;

	vector<float> grad;
	grad.push_back(1);
	five->backprop(grad);

	cout << five->grad[0] << endl;
	cout << four->grad[0] << endl;
	cout << three->grad[0] << endl;
	cout << two->grad[0] << endl;
	cout << one->grad[0] << endl;

	return 0;
}
