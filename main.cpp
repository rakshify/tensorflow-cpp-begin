#include<iostream>


using namespace std;


class Tensor;


class Operation {
	public:
		Tensor* one;
		Tensor* two;

		Operation() {};

		virtual Tensor* forward() {
			return NULL;
		}
};


class MulOperation : public Operation {
	public:
		MulOperation(Tensor* one, Tensor* two) {
			this->one = one;
			this->two = two;
		}

		Tensor* forward();
};


class AddOperation : public Operation {
	public:
		AddOperation(Tensor* one, Tensor* two) {
			this->one = one;
			this->two = two;
		}

		Tensor* forward();
};


class Tensor {
	public:
		float val;
		Operation* frontOp = NULL;

		Tensor () {};

		Tensor (float v) {
			this->val = v;
		}

		// Overload * operator to add two Box objects.
		Tensor* operator*(const Tensor* two) {
			this->frontOp = new MulOperation(this, (Tensor*)two);
			return this->frontOp->forward();
		}

		// Overload + operator to add two Box objects.
		Tensor* operator+(const Tensor* two) {
			this->frontOp = new AddOperation(this, (Tensor*)two);
			return this->frontOp->forward();
		}
};


Tensor* MulOperation::forward() {
	return new Tensor(this->one->val * this->two->val);
}


Tensor* AddOperation::forward() {
	return new Tensor(this->one->val + this->two->val);
}


int main() {
	Tensor* one = new Tensor(2);
	Tensor* two = new Tensor(4);

	Tensor* three = (*one) * two;
	Tensor* four = new Tensor(5);

	Tensor* five = (*three) + four;
	cout << five->val << endl;

	return 0;
}
