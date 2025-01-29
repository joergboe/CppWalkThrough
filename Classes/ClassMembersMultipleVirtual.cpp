//============================================================================
// Name        : ClassMembersMultipleVirtual.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;

class A {
public:
	A(const string& name_) : name(name_) { cout << "A(const string& name_) :" << name << endl; }
	~A() { cout << "~A() :" << name << endl; }
	void signal() const { cout << "A::signal : " << name << endl; }
	const string name;
};

class B {
public:
	B(const string& name_) : name(name_) { cout << "B(const string& name_) : " << name_ << endl; }
	~B() { cout << "~B() :" << name << endl; }
	void signal() const { cout << "B::signal : " << name << endl; }
	const string name;
};

class C : virtual public A, virtual public B {
public:
	C(const string& name_) : A(name_), B(name_) { cout << "C(const string& name_) : " << name_ << endl; }
	~C() { cout << "~C() :" << endl; }
	void signal() const { cout << "C::signal : " << A::name << " " << B::name << endl; }
};

class AV {
public:
	AV(const string& name_) : name(name_) { cout << "AV(const string& name_) :" << name << endl; }
	virtual ~AV() { cout << "~AV() :" << name << endl; }
	virtual void signal() const { cout << "AV::signal : " << name << endl; }
	const string name;
};

class BV {
public:
	BV(const string& name_) : name(name_) { cout << "BV(const string& name_) : " << name_ << endl; }
	virtual ~BV() { cout << "~BV() :" << name << endl; }
	virtual void signal() const { cout << "BV::signal : " << name << endl; }
	const string name;
};

class CV : virtual public AV, virtual public BV {
public:
	CV(const string& name_) : AV(name_), BV(name_) { cout << "CV(const string& name_) : " << name_ << endl; }
	virtual ~CV() { cout << "~CV() :" << endl; }
	virtual void signal() const override { cout << "CV::signal : " << AV::name << " " << BV::name << endl; }
};

int main() {
	cout << "-- Construct class A instance a: 'First a'" << endl;
	//A aa; -> error : No default constructor
	A a{"First a"};
	cout << "-- Call signal from a" << endl;
	a.signal();
	cout << "-- Construct class B instance b: 'Second b'" << endl;
	B b{"Second b"};
	cout << "-- Call signal from b" << endl;
	b.signal();
	cout << "-- Construct class C instance c: 'Third c'" << endl;
	C c{"Third c"};
	cout << "-- Call signal from c" << endl;
	c.signal();
	cout << "-- Call signal with explicit names" << endl;
	c.A::signal();
	c.B::signal();
	c.C::signal();

	cout << "-- Virtual --" << endl;
	cout << "-- Construct class AV instance av: 'First av'" << endl;
	AV av{"First av"};
	cout << "-- Call signal from av" << endl;
	av.signal();
	cout << "-- Construct class BV instance bv: 'Second bv'" << endl;
	BV bv{"Second bv"};
	cout << "-- Call signal from bv" << endl;
	bv.signal();
	cout << "-- Construct class CV instance cv: 'Third cv'" << endl;
	CV cv{"Third cv"};
	cout << "-- Call signal from cv" << endl;
	cv.signal();
	cout << "-- Call signal with explicit names" << endl;
	cv.AV::signal();
	cv.BV::signal();
	cv.CV::signal();

	cout << "Operations with AV*" << endl;
	const AV* avp = &av;
	cout << "AV* avp = &av; avp->signal()" << endl;
	avp->signal();
	cout << "avp = &cv; avp->signal()" << endl;
	avp = &cv;
	avp->signal();
	cout << "Operations with BV*" << endl;
	const BV* bvp = &bv;
	cout << "BV* bvp = &bv; bvp->signal()" << endl;
	bvp->signal();
	cout << "bvp = &cv; vvp->signal()" << endl;
	bvp = &cv;
	bvp->signal();
	cout << "Operations with CV*" << endl;
	const CV* cvp{&cv};
	cvp->signal();
	cvp->CV::signal();
	cvp->BV::signal();
	cvp->AV::signal();

	cout << "sizeof(A): " << sizeof(A) << endl;
	cout << "sizeof(B): " << sizeof(B) << endl;
	cout << "sizeof(C): " << sizeof(C) << endl;
	cout << "sizeof(AV): " << sizeof(AV) << endl;
	cout << "sizeof(BV): " << sizeof(BV) << endl;
	cout << "sizeof(CV): " << sizeof(CV) << endl;

	return 0;
}
