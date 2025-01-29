//============================================================================
// Name        : ClassMembersMultiple2.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class A {
public:
	A(const string& name_) : name(string(name_).append(" A")) { cout << "A(const string& name_) :" << name << endl; }
	~A() { cout << "~A() :" << name << endl; }
	void signal() const { cout << "A::signal : " << name << endl; }
	const string name;
};

class B : public A {
public:
	B(const string& name_) : A(string(name_).append(" B")) { cout << "B(const string& name_)" << endl; }
	~B() { cout << "~B()" << endl; }
	void signal() const { cout << "B::signal : " << name << endl; }
};

class C : public A {
public:
	C(const string& name_) : A(string(name_).append(" C")) { cout << "C(const string& name_)" << endl; }
	~C() { cout << "~C()" << endl; }
	void signal() const { cout << "C::signal : " << name << endl; }
};

class D : public B, public C {
public:
	D(const string& name_) : B(string(name_).append(" D")), C(string(name_).append(" D")) { cout << "D(const string& name_)" << endl; }
	~D() { cout << "~D()" << endl; }
	void signal() const { cout << "D::signal : " << B::name << " " << C::name << endl; }
};

class AV {
public:
	AV(const string& name_) : name(string(name_).append(" AV")) { cout << "AV(const string& name_) :" << name << endl; }
	virtual ~AV() { cout << "~AV() :" << name << endl; }
	virtual void signal() const { cout << "AV::signal : " << name << endl; }
	const string name;
};

class BV : public AV {
public:
	BV(const string& name_) : AV(string(name_).append(" BV")) { cout << "BV(const string& name_)" << endl; }
	virtual ~BV() override { cout << "~BV()" << endl; }
	virtual void signal() const override { cout << "BV::signal : " << name << endl; }
};

class CV : public AV {
public:
	CV(const string& name_) : AV(string(name_).append(" CV")) { cout << "CV(const string& name_)" << endl; }
	virtual ~CV() override { cout << "~CV()" << endl; }
	virtual void signal() const override { cout << "CV::signal : " << name << endl; }
};

class DV : public BV, public CV {
public:
	DV(const string& name_) : BV(string(name_).append(" DV")), CV(string(name_).append(" DV")) { cout << "DV(const string& name_)" << endl; }
	virtual ~DV() override { cout << "~DV()" << endl; }
	virtual void signal() const override { cout << "DV::signal : " << BV::name << " " << CV::name << endl; }
};


int main() {
	cout << "-- Construct class D instance d: 'Object d'" << endl;
	D d{"Object d"};

	cout << "-- Signal operations with D" << endl;
	d.signal();
	d.D::signal();
	d.C::signal();
	d.B::signal();

	cout << "-- Virtual --" << endl;
	cout << "-- Construct class DV instance dv: 'Object dv'" << endl;
	DV dv{"Object dv"};
	cout << "-- Signal operations with DV" << endl;
	dv.signal();
	dv.DV::signal();
	dv.CV::signal();
	dv.BV::signal();

	AV av{"Object av"};
	cout << "-- Operations with avp" << endl;
	const AV* avp{&av};
	avp->signal();
	//avp = &dv;  //error

	cout << "-- Operations with bvp" << endl;
	const BV* bvp{&dv};
	bvp->signal();
	bvp->AV::signal();
	bvp->BV::signal();

	cout << "-- Operations with cvp" << endl;
	const CV* cvp{&dv};
	cvp->signal();
	cvp->AV::signal();
	cvp->CV::signal();

	cout << "-- Operations with dvp" << endl;
	const DV* dvp{&dv};
	dvp->signal();
	//dvp->AV::signal(); error
	dvp->BV::signal();
	dvp->CV::signal();

	cout << "sizeof(A): " << sizeof(A) << endl;
	cout << "sizeof(B): " << sizeof(B) << endl;
	cout << "sizeof(C): " << sizeof(C) << endl;
	cout << "sizeof(D): " << sizeof(D) << endl;
	cout << "sizeof(AV): " << sizeof(AV) << endl;
	cout << "sizeof(BV): " << sizeof(BV) << endl;
	cout << "sizeof(CV): " << sizeof(CV) << endl;
	cout << "sizeof(DV): " << sizeof(DV) << endl;

	return 0;
}
