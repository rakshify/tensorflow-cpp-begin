#include<iostream>

using namespace std;

class Tensor {
    public:
	float val;

	Tensor () {};

	Tensor (float v) {
            this->val = v;
	}

	// Overload * operator to add two Box objects.
	Tensor* operator*(const Tensor* two) {
	    return new Tensor(this->val * two->val);
	}
};

int main() {
    Tensor* one = new Tensor(2);
    Tensor* two = new Tensor(4);

    Tensor* three = (*one) * two;
    cout << three->val << endl;

    return 0;
}
