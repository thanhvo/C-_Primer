#include <memory>
#include <iostream>

using namespace std;

struct B;
struct A {
	shared_ptr<B> b;
	~A() {
		cout << "~A()\n";
	}	
};

struct B {
	//shared_ptr<A> a;
	weak_ptr<A> a;
	~B() { 
		cout << "~B()\n";
	}
};

void useAnB() {
	auto a = make_shared<A>();
	auto b = make_shared<B>();
	a->b = b;
	b->a = a;
}

int main() {
	useAnB();
	cout << "Finished using A and B\n";
}
