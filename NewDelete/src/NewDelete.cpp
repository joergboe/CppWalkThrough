//============================================================================
// Name        : NewDelete.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
using namespace std;

class MyClass {
public:
	MyClass() {
		cout << "Constructor MyClass()\n";
	}
	~MyClass() {
		cout << "Destructor MyClass()\n";
	}
};

int main() {
	cout << "Memory allocation with new an memory release with delete" << endl;

	cout << "\nAllocation with operator 'new type' returns a pointer to the allocated object or variable.\n";
	int * ip = new int;
	*ip = 55;
	cout << "ip=" << ip << " *ip=" << *ip << endl;
	cout << "Release acquired resource with operator 'delete'.\n";
	delete ip;
	cout << "The pointer points still to the memory location.\n";
	cout << "ip=" << ip << " *ip=" << *ip << endl;
	ip = nullptr;
	cout << "ip=" << ip << endl;

	cout << "\nAllocation of array use 'new type[n]'. Where n must be determined on compile time.\n";
	char * cp = new char[5];
	cout << cp << endl;
	cout << "\nRelease array type memory with operator 'delete[]'\n"
			"Never release a memory block twice!\n";
	delete[] cp;

	cout << "\nThe deletion of a pointer with value 'nullptr' does nothing.\n";
	int * nptr = nullptr;
	delete nptr;
	cout << endl;

	MyClass * mclp = new MyClass[3];
	cout << "To release all 5 objects use operator 'delete[]'. With operator 'delete' only the first object is released!\n";
	//delete mclp;
	delete[] mclp;

	cout << "The new operator may have a initialization list in { }\n";
	int const * icp1 = new int {}; //default initialized
	int const * icp2 = new int {55};
	char const * ccp = new char[5]{'a', 'b', 'c', 'd'}; // missing fields in the initializer list are default constructed?
	cout << "*icp1=" << *icp1 << " *icp2=" << *icp2 << endl <<
			"ccp=" << ccp << endl;
	delete icp1;
	delete icp2;
	delete[] ccp;

	cout << "End" << endl;
	return 0;
}
