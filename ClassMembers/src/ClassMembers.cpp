//============================================================================
// Name        : ClassMembers.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Demonstrates shadowing and overriding of members and object sizes
//============================================================================

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Base {
public:
	Base(const string& name_) : name(name_) { cout << "Base(const string& name_) :" << name << endl; }
	~Base() { cout << "~Base() :" << name << endl; }
	void signal() const { cout << "Base::signal : " << name << endl; }
	const string name;
};

class Derived : public Base {
public:
	Derived(const string& name_) : Base(string("Derived::").append(name_)) { cout << "Derived(const string& name_) : " << name << endl; }
	~Derived() { cout << "~Derived() :" << name << endl; }
	void signal() const { cout << "Derived::signal : " << name << endl; }
};

//Class with vitual methods
class Base2 {
public:
	Base2(const string& name_) : name(name_) { cout << "Base2(const string& name_) :" << name << endl; }
	virtual ~Base2() { cout << "~Base2() :" << name << endl; }
	virtual void signal() const { cout << "Base2::signal : " << name << endl; }
	virtual void signal2() const { cout << "Base2::signal2 : " << name << endl; } //warning: ‘virtual void Base2::signal2() const’ was hidden [-Woverloaded-virtual]
	const string name;
};

class Derived2 : public Base2 {
public:
	Derived2(const string& name_) : Base2(string("Derived2:").append(name_)) { cout << "Derived2(const string& name_) : " << name << endl; }
	virtual ~Derived2() { cout << "~Derived2() :" << endl; }
	virtual void signal() const override { cout << "Derived2::signal : " << name << endl; }
	void signal2(int i) const { cout << "Derived2::signal2(int i) : " << name << " " << i << endl; } //warning: ‘virtual void Base2::signal2() const’ was hidden [-Woverloaded-virtual]
};

int main() {
	{
		cout << "**** Construct class Base instance base: 'First' ****" << endl;
		Base base{"First"};
		cout << "**** Call signal from base ****" << endl;
		base.signal();
		cout << "**** Construct class Derived instance derived: 'Second' ****" << endl;
		Derived derived{"Second"};
		cout << "**** Call signal and shadowed ****" << endl;
		derived.signal();
		derived.Derived::signal();
		derived.Base::signal();
		cout << "**** Assign &base to Base* basePtr and call basePtr->signal() ****" << endl;
		const Base* basePtr = &base;
		basePtr->signal();
		cout << "**** Assign &derived to Base* basePtr and call basePtr->signal() ****" << endl;
		basePtr = &derived;
		basePtr->signal();
		cout << "**** !!!member of Base is visible in derived!!!" << endl;
		cout << derived.name << endl;
		cout << derived.Derived::name << endl;
		cout << derived.Base::name << endl;
		cout << "**** End of scope1 ****" << endl;
	}
	cout << endl << "**** Classes with virtual functions ****" << endl;
	cout << "**** Construct class Base2 instance base2: 'Third'" << endl;
	Base2 base2{"Third"};
	cout << "**** Call signal from base2" << endl;
	base2.signal();
	{
		cout << "**** Construct class Derived2 instance derived2: 'Fourth'" << endl;
		Derived2 derived2{"Fourth"};
		cout << "**** Call signal() and shadowed signal()" << endl;
		derived2.signal();
		derived2.Derived2::signal();
		derived2.Base2::signal();
		cout << "**** Assign &base2 to Base2* base2Ptr and call base2Ptr->signal() ****" << endl;
		const Base2* base2Ptr = &base2;
		base2Ptr->signal();
		cout << "**** Assign &derived2 to Base2* base2Ptr and call base2Ptr->signal() ****" << endl;
		base2Ptr = &derived2;
		base2Ptr->signal();
		cout << "**** Assign &derived2 to Derived2* derived2Ptr and call derived2Ptr->signal() ****" << endl;
		const Derived2* derived2Ptr = &derived2;
		derived2Ptr->signal();
		cout << "**** No override over namespaces" << endl;
		derived2Ptr->signal2(1);
		//derived2Ptr->signal2(); //error: no matching function for call to ‘Derived2::signal2() const
		cout << "**** End of scope2 ****" << endl;
	}
	cout << "sizeof(Base): " << sizeof(Base) << endl;
	cout << "sizeof(Derived): " << sizeof(Derived) << endl;
	cout << "sizeof(Base2): " << sizeof(Base2) << endl;
	cout << "sizeof(Derived2): " << sizeof(Derived2) << endl;
	cout << "sizeof(string): " << sizeof(string) << endl;
	cout << "sizeof(void*): " << sizeof(void*) << endl;
	const char * p{getenv("PATH")};
	cout << "PATH=" << p << endl;
	return 0;
}
