//============================================================================
// Name        : PointerToMember.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
using namespace std;

class Base {
public:
	char const * mess;
	char a, b;
	char const cc;
private:
	char privc;
public:
	Base(char const * mess_ = "Base", char a_ = 'a', char b_ = 'b') : mess(mess_), a(a_), b(b_), cc('C'), privc('p') {};
	void print1(int val) const {
		cout << "print1";
		printVars();
		cout << " val=" << val << endl;
	}
	/*void print2(int val) const {
		cout << "print2";
		printVars();
		cout << " val=" << val << endl;
	}*/
	void setA(char c_) {
		a = c_;
	}
	void setB(char c_) {
		b = c_;
	}
protected:
	void printVars() const {
		cout << " mess=" << mess << " a=" << a << " b=" << b << " privc=" << privc;
	}
};

class Derived : public Base {
public:
	char d;
	Derived() : Base("Derived", 'a'), d('d') {};
	void print3(int val) {
		cout << "print3";
		printVars();
		cout << " d=" << d << endl;
	}
};

typedef char Base::* MemberPointerB1;
//using MemberPointer = char Base::*; //c11 stype
typedef void (Base::*MethodPointer)(int);
//using MethodPointer = void (Base::*)(int);

int main() {
	cout << "Demonstration of pointer to member and pointer to method.\n"
			"The declaration 'T C::* P' declares P as a pointer to non-static member of C of type T.\n"
			"Where member can be a non-static attribute or a non-static class function.\n"
			"Use operator '.*' (pointer to member of object) or '->*' (pointer to member of pointer)\n"
			"to access these members.\n"
			"Address operator '&C::member delivers the address for these pointers.\n"
			"Pointers to member must not be assigned to other pointer types an void*.\n"
			"The 'nullptr' can be assigned to a pointer to member.\n\n";

	Base base1;
	base1.print1(1);

	cout << "\n****** Pointer to class member (non-static member) ******\n";
	cout << "use 'char Base::* const char_ptr1' to declare a pointer to member\n";
	cout << "use '&Base::a' to define the pointer\n";
	char Base::* char_ptr1 = &Base::a;
	cout << "use 'base1.*char_ptr1' to address where it points to.\n";
	cout << base1.*char_ptr1 << endl;
	cout << "char_ptr1 may point to all non-const char members of Base\n";
	char_ptr1 = &Base::b;
	cout << base1.*char_ptr1 << endl;
	cout << "The member must be visible in that context:\n";
	//char_ptr1 = &Base::privc; //error: ‘char Base::privc’ is private within this context
	cout << "the pointer can be const qualified with 'char Base::* const char_ptr2 = &Base::a'\n";
	char Base::* const char_ptr2 = &Base::a;
	cout << "base1.*char_ptr2: " << base1.*char_ptr2 << endl;
	cout << "constantness is maintained\n";
	//char_ptr2 = &Base::b; //error: assignment of read-only variable ‘char_ptr2’
	//char_ptr1 = &Base::cc; //error: invalid conversion from ‘const char Base::*’ to ‘char Base::*’ [-fpermissive]
	Base const base2("Base const");
	//base2.*char_ptr1 = 'x'; //error: assignment of read-only location ‘*(((const char*)(& base2)) + ((sizetype)char_ptr1))’
	const char * Base::* mess_ptr = &Base::mess;
	cout << "base2.*mess_ptr: " << base2.*mess_ptr << endl;

	cout << "\nPointer to members can be used with objects of public derived classes\n";
	Derived derived1;
	cout << "derived1.*mess_ptr: " << derived1.*mess_ptr << endl;
	cout << "But pointers to members of derived can not point to members of base\n";
	char Derived::* char_ptr3 = &Derived::d;
	cout << "derived1.*char_ptr3: " << derived1.*char_ptr3 << endl;
	//base1.*char_ptr3 = 'x'; //error: pointer to member type ‘char’ incompatible with object type ‘Base’

	cout << "\nRecomended use of aliases:\n";
	typedef char Base::* BaseToCharMemberPtr;
	using BaseToMessMemberPtr = char const * Base::*; //c11 stype
	BaseToCharMemberPtr mptr3 = &Base::b;
	BaseToMessMemberPtr mptr4 = &Base::mess;
	cout << "base2.*mptr4: " << base2.*mptr4 << " base2.*mptr3: " << base2.*mptr3 << endl;

	cout << "\nUse operator '->*' with an object pointer\n";
	Base const * b_cptr = & base2;
	cout << "b_cptr->*mptr4: " << b_cptr->*mptr4 << " b_cptr->*mptr3: " << b_cptr->*mptr3 << endl;

	cout << "\n****** Pointer to class member functions (non-static member) ******\n";

	cout << "Function pointer declaration rules and '::*' declares a pointer to a visible member function:\n"
			"void (Base::*func_ptr1)(char) = &Base::setA\n";
	void (Base::*func_ptr1)(char) = &Base::setA;
	cout << "the usage of this pointer requires parentheses:\n";
	(base1.*func_ptr1)('x');
	cout << "a pointer of this type can point to any member function with a matching signature.\n";
	func_ptr1 = &Base::setB;
	(base1.*func_ptr1)('y');
	base1.print1(12);
	cout << "The member must be visible in that context:\n";
	//void (Base::*func_ptr2)() = &Base::printVars;  //error: ‘void Base::printVars()’ is protected within this context
	cout << "\nPointer to members can be used with objects of public derived classes\n";
	(derived1.*func_ptr1)('z');
	derived1.print1(0);
	cout << "const qualifier is part of the function pointer type:\n";
	void (Base::*func_ptr_const)(int) const = &Base::print1;
	cout << "type func_ptr1:      " << typeid(func_ptr1).name() <<
			"\ntype func_ptr_const: " << typeid(func_ptr_const).name() << endl;
	cout << "Use with a pointer to object (b_cptr->*func_ptr_const)(14)\n";
	(b_cptr->*func_ptr_const)(14);
	Derived * d_ptr = & derived1;
	(d_ptr->*func_ptr_const)(15);

	cout << "\nRecomended use of aliases:\n";
	typedef void (Base::*BaseSetCharMemberFunctionPointer)(char);
	using BasePrintMemberFunctionPointer = void (Base::*)(int) const;
	BaseSetCharMemberFunctionPointer fmp1 = &Base::setA;
	BasePrintMemberFunctionPointer fmp2 = &Base::print1;
	(base1.*fmp1)('@');
	(base1.*fmp2)(999);

	cout << "\n****** compare pointer to members ******\n";
	cout << "\nPointer to members of same type can be compared:\n";
	if (mess_ptr == mptr4) {
		cout << "Equal pointers point to the same member but may not point to different objects.\n"
				"(*fp1)(7)=" << base1.*mess_ptr << endl <<
				"(*pa1)(7)=" << derived1.*mptr4 << endl;
	}
	cout << "\nThe same applies to pointers to member functions:\n";
	if (fmp1 != func_ptr1) {
		cout << "&Base::setB and &Base::setA are not equal\n";
	}
	cout << "Distinct pointer types without a cast can not be compared.\n";
	//if (mess_ptr == mptr3); //comparison between distinct pointer types ‘const char* Base::*’ and ‘BaseToCharMemberPtr’ {aka ‘char Base::*’} lacks a cast [-fpermissive]
	cout << "Can assign 'nullptr' to pointer to member but never use such member! The result is undefined.\n"
			"You can compare pointer to member to 'nullptr'.\n";
	char_ptr1 = nullptr;
	if (char_ptr1 == nullptr) {
		cout << "Do not use pointers with null or default constructed pointers!\n";
	}
	char Base::* char_ptr4{};
	if (char_ptr4 == nullptr) {
		cout << "Do not use default constructed pointers!\n";
	}

	cout << "\n****** pointer to member and pointer ******\n"
			"Pointer to member can not be assigned to a 'void *'\n";
	// void * vptr = func_ptr1; //error: cannot convert ‘void (Base::*)(char)’ to ‘void*’ in initialization

	cout << "END" << endl;

	return 0;
}
