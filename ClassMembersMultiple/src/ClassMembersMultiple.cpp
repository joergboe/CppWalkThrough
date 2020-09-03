//============================================================================
// Name        : ClassMembersMultiple.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Demonstrates composition of class from 2 parent classes and object sizes
//============================================================================

#include <iostream>
using namespace std;

class BaseA {
public:
	BaseA(const string& name_) : name(name_) { cout << "BaseA(const string& name_) :" << name << endl; }
	~BaseA() { cout << "~BaseA() :" << name << endl; }
	void signal() const { cout << "BaseA::signal : " << name << endl; }
	const string name;
};

class BaseB {
public:
	BaseB(const string& name_) : name(name_) { cout << "BaseB(const string& name_) : " << name_ << endl; }
	~BaseB() { cout << "~BaseB() :" << name << endl; }
	void signal() const { cout << "BaseB::signal : " << name << endl; }
	const string name;
};

class Composite : public BaseA, public BaseB {
public:
	Composite(const string& name_) : BaseA(string("BaseA::").append(name_)), BaseB(string("BaseB::").append(name_)) { cout << "Composite(const string& name_) : " << name_ << endl; }
	~Composite() { cout << "~Composite() :" << endl; }
	void signal() const { cout << "Composite::signal : " << BaseA::name << " " << BaseB::name << endl; }
};

class BaseA2 {
public:
	BaseA2(const string& name_) : name(name_) { cout << "BaseA2(const string& name_) :" << name << endl; }
	virtual ~BaseA2() { cout << "~BaseA2() :" << name << endl; }
	virtual void signal() const { cout << "BaseA2::signal : " << name << endl; }
	const string name;
};

class BaseB2 {
public:
	BaseB2(const string& name_) : name(name_) { cout << "BaseB2(const string& name_) : " << name_ << endl; }
	virtual ~BaseB2() { cout << "~BaseB2() :" << name << endl; }
	virtual void signal() const { cout << "BaseB2::signal : " << name << endl; }
	const string name;
};

class Composite2 : public BaseA2, public BaseB2 {
public:
	Composite2(const string& name_) : BaseA2(string("BaseA2::").append(name_)), BaseB2(string("BaseB2::").append(name_)) { cout << "Composite2(const string& name_) : " << name_ << endl; }
	virtual ~Composite2() { cout << "~Composite2() :" << endl; }
	void signal() const override { cout << "Composite2::signal : " << BaseA2::name << " " << BaseB2::name << endl; }
};

int main() {
	cout << "**** Construct class Composite instance c: 'First'" << endl;
	Composite c{"First"};
	cout << "**** Call signal from c" << endl;
	c.signal();

	cout << "**** Call signal with explicit names" << endl;
	c.BaseA::signal();
	c.BaseB::signal();
	c.Composite::signal();
	cout << "**** Member access" << endl;
	// cout << c.name << endl; //error: request for member ‘name’ is ambiguous
	// cout << c.Composite::name << endl; // error: request for member ‘name’ is ambiguous
	cout << c.BaseA::name << endl;
	cout << c.BaseB::name << endl;


	cout << endl << "**** with virtual functions ****" << endl;
	cout << "**** Construct class BaseA2 and BaseB2 instance av bv: 'Second'" << endl;
	BaseA2 av{"Second"};
	av.signal();
	BaseB2 bv{"Third"};
	bv.signal();
	cout << "**** Construct class Composite2 instance cv: 'Fives'" << endl;
	Composite2 cv{"Fives"};
	cout << "**** Call signal from cv" << endl;
	cv.signal();
	cout << "**** Call signal with explicit names" << endl;
	cv.BaseA2::signal();
	cv.BaseB2::signal();
	cv.Composite2::signal();

	cout << "**** Pointer operations with base pointers BaseA2* and BaseB2*" << endl;
	const BaseA2* avp = &cv;
	const BaseB2* bvp = &cv;
	avp->signal();
	bvp->signal();
	cout << "**** Pointer operations with Composite2*" << endl;
	const Composite2* cvp{&cv};
	cvp->signal();
	cvp->Composite2::signal();
	cvp->BaseB2::signal();
	cvp->BaseA2::signal();

	cout << "sizeof(BaseA): " << sizeof(BaseA) << endl;
	cout << "sizeof(BaseB): " << sizeof(BaseB) << endl;
	cout << "sizeof(Composite): " << sizeof(Composite) << endl;
	cout << "sizeof(BaseA2): " << sizeof(BaseA2) << endl;
	cout << "sizeof(BaseB2): " << sizeof(BaseB2) << endl;
	cout << "sizeof(Composite2): " << sizeof(Composite2) << endl;
	cout << "sizeof(string): " << sizeof(string) << endl;
	cout << "sizeof(void*): " << sizeof(void*) << endl;


	return 0;
}
