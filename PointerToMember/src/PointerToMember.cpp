//============================================================================
// Name        : PointerToMember.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Base {
public:
	char a;
	char b;

	Base(char a_, char b_) : a(a_), b(b_) {};
	void print1(int val) {
		cout << "print1 a=" << a << " b=" << b << " val=" << val << endl;
	}
	void print2(int val) {
		cout << "print2 a=" << a << " b=" << b << " val=" << val << endl;
	}
};

class Derived : public Base {
public:
	char c;
	Derived(int a_, int b_) : Base(a_, b_), c('@') {};
	void print3(int val) {
		cout << "print3 a=" << a << " b=" << b << " c=" << c << " val=" << val << endl;
	}
};

typedef char Base::* MemberPointer;
//using MemberPointer = char Base::*; //c11 stype
typedef void (Base::*MethodPointer)(int);
//using MethodPointer = void (Base::*)(int);

int main() {
	cout << "!!!Hello World!!!" << endl;
	Base object1('a', 'b');
	object1.print1(55);
	object1.print2(56);

	//Member Pointer
	char Base::* const memberPointer1 = &Base::a; //direct declaration (const)
	object1.*memberPointer1 = 'A';
	MemberPointer memberPointer2 = &Base::b;
	object1.*memberPointer2 = 'B';         //declaration using alias (typedef / using
	//Method Pointer
	void (Base::*methodPointer1)(int) = &Base::print1; //direct declaration
	Base* objectPtr = &object1;
	(objectPtr->*methodPointer1)(11);
	MethodPointer methodPointer2 = &Base::print2;
	(object1.*methodPointer2)(22);

	//Derived
	Derived object2('x','y');
	void (Derived::* methodPointer3)(int) = &Derived::print3;
	(object2.*methodPointer3)(22);
	methodPointer3 = &Derived::print1;
	(object2.*methodPointer3)(100);
	(object2.*methodPointer1)(0); //use method pointer of Base with object type Derived

	cout << "sizeof(object1)=" << sizeof(object1) << endl;
	cout << "sizeof(object2)=" << sizeof(object2) << endl;
	return 0;
}
