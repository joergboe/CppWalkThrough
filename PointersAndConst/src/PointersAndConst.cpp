//============================================================================
// Name        : Pointers.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
using namespace std;

int main() {
	cout << "Pointer and constant demo" << endl;
	int i = 11;
	int inew = 155;
	cout << "declaration of an constant variable may be done with prefix or suffix const qualifier\n";
	const int ci = 55;
	//ci = 100; //error: assignment of read-only variable ‘ci’
	int const ci2 = 66;
	//ci2 = 100; //error: assignment of read-only variable ‘ci2’
	cout << "i=" << i << " ci=" << ci << " ci2=" << ci2 << endl;
	cout << "------------------------------------------------------" << endl;
	{
		cout << "Pointer to mutable variable: use int * name" << endl;
		int * ip = &i;
		//ip = &ci; //error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
		//ip = &ci2; //error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
		cout << "Pointer to constant variable: use const int * name or int const * name" << endl;
		const int * cip = &ci;
		int const * cip2 = &ci2;
		cout << "*ip=" << *ip << " *cip=" << *cip << " *cip2=" << *cip2 << endl;
		cout << "Changes of then variable is allowed with ip only\n";
		cout << "The compiler prevents changes of constant variables\n";
		(*ip)++;
		//(*cip)++; //error: increment of read-only location ‘* cip’
		//*cip2 = 166; //error: assignment of read-only location ‘* cip2’
		cout << "*ip=" << *ip << " *cip=" << *cip << " *cip2=" << *cip2 << endl;
		cout << "Pointers to variable or const variable are mutable\n";
		ip = &inew;
		cip = &ci2;
		cip2 = &ci;
		cout << "*ip=" << *ip << " *cip=" << *cip << " *cip2=" << *cip2 << endl;
		cout << "Declare a pointer to a pointer with int * * ipp = &ip\n";
		int * * ipp = &ip;
		cout << "**ipp=" << **ipp << "\nChange the value\n";
		++(**ipp);
		cout << "**ipp=" << **ipp << endl;
		cout << "Declare a pointer to a pointer to a const variable with int const * * ipp = &cip\n";
		int const * * cipp = &cip;
		cout << "**cipp=" << **cipp << " And the value can not be changed" << endl;
		//++(**cipp); //error: increment of read-only location ‘* * cipp’
	}
	cout << "------------------------------------------------------\n" << endl;
	{
		cout << "Constant Pointers are constant but the the variable may not" << endl;
		cout << "A constant pointer to a mutable value. Use: int * name\n";
		int * const ipc = &i;
		cout << "A constant pointer to a constant variable. Use: const int * const name or int const * const name\n";
		const int * const cipc = &ci;
		int const * const cipc2 = &ci2;
		cout << "*ipc=" << *ipc << " *cipc=" << *cipc << " *cipc2=" << *cipc2 << endl;
		cout << "The value where a const pointer points to is mutable\n";
		(*ipc)++;
		cout << "The value where pointer to const value points to are immutable\n";
		//(*cipc)++; //error: increment of read-only location ‘*(const int*)cipc’
		//(*cipc2)++; //error: increment of read-only location ‘*(const int*)cipc2’
		cout << "Const pointer are immutable\n";
		//ipc = &inew; //error: assignment of read-only variable ‘ipc’
		//cipc = &ci2; //error: assignment of read-only variable ‘cipc’
		//cipc2 = &ci; //error: assignment of read-only variable ‘cipc2’
		cout << "*ipc=" << *ipc << " *cipc=" << *cipc << " *cipc2=" << *cipc2 << endl;
	}
	cout << "------------------------------------------------------\n" << endl;
	{
		cout << "References and constant references" << endl;
		int & ir = i;
		const int & cir = ci;
		int const & cir2 = ci2;
		cout << "The value of a reference is mutable; The value of constant reference is immutable\n";
		ir++;
		//cir++; //error: increment of read-only reference ‘cir’
		//cir2++; //error: increment of read-only reference ‘cir2’
		cout << "ir=" << ir << " cir=" << cir << " cir2=" << cir2 << endl;
		cout << "The const reference of a mutable variable can not be used to change the value of the variable\n";
		int const & cmi = i;
		//cmi++; //error: increment of read-only reference
		cout << "cmi=" << cmi << endl;
		cout << "The assignment to an reference is always an assignment to the variable.\n";
		//cir = ci; //error: assignment of read-only reference ‘cir’
		cout << "You can not change the address where the reference points to. The assignment is always a change of the variable\n";
		int newI = -11;
		ir = newI;
		cout << "newI=" << newI << " ir=" << ir << " i=" << i << endl;
		const int & cirr = ci;
		int const & cirr2 = ci2;
		cout << "ir=" << ir << " cirr=" << cirr << " cirr2=" << cirr2 << endl;
		cout << "A reference is alway const. There is no such thing like int & const cirrr = i;";
		//int & const cirrr = i; //error: ‘const’ qualifiers cannot be applied to ‘int&’
		cout << "There is no such thing like a reference to a reference int & & ...\n";
		//int & & irr = ir; //error: cannot declare reference to ‘int&’
		cout << " && is since c++11 a r-value reference." << endl;
	}
	cout << "Eigentlich ist das const nachgestellt systematischer" << endl;
	cout << "END" << endl;
	return 0;
}
