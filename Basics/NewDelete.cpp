//============================================================================
// Name        : NewDelete.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
#include <array>

using namespace std;

constexpr size_t BLOCK_SIZE = 1024;

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

	cout << "\nAllocation of array use 'new type[n]'. Where n can be determined at runtime.\n";
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
	char const * ccp = new char[5]{'a', 'b', 'c', 'd'}; // missing fields in the initializer list are default constructed? Problem?
	cout << "*icp1=" << *icp1 << " *icp2=" << *icp2 << endl <<
			"ccp=" << ccp << endl;

	delete icp1;
	delete icp2;
	delete[] ccp;

	int const * const icp3 = new int[5]{};
	//double* p = new double[]{1,2,3}; // creates an array of type double[3] This code from https://en.cppreference.com/w/cpp/language/new does not work -> P1009R2
	cout << "icp3[]: ";
	for (int i = 0; i < 5; ++i)
		cout << icp3[i] << " ";
	cout << endl;
	delete icp3;

	cout << "Allocate new function pointer\n";
	int (**fp1)() = new (int (*)());
	cout << "Allocate new array of function pointers\n";
	int (**fp2)() = new (int (*[11])());

	delete fp1;
	delete[] fp2;

	cout << "\n!!! Danger the following program section allocates a very large amount of memory.\n"
			"This may corrupt our system. Proceed on your own risk!.\n"
			"To proceed press 'Y'\n";
	char r;
	cin >> r;
	if (r != 'Y') {
		cout << "END";
		return 0;
	}

	cout << "\nnew throws bad_alloc when not enough memory is available\n";
	{
		size_t blocksize = BLOCK_SIZE;
		try {
			while (true) {
				size_t kibyte = sizeof(int[BLOCK_SIZE]) / 1024;
				size_t mbyte = kibyte / 1024;
				cout << "try allocation new int[" << blocksize << "] with size: " << mbyte << " megabytes";
				int * buffptr = new int[blocksize];
				cout << " and use it ...\n";
				for (size_t i = 0; i < blocksize; ++i)
					*(buffptr + i) = 0;
				delete[] buffptr;
				blocksize <<= 1;
			}
		} catch (bad_alloc const & exc) {
			cout << "\n!! Exception catched: " << exc.what() << " !!" << endl;
		}
	}

	cout << "\nThe nothrow version return a nullptr if not enough memory is available instead of throwing the bad_alloc exception.\n";
	{
		size_t blocksize = BLOCK_SIZE;
		while (true) {
			size_t kibyte = sizeof(int[BLOCK_SIZE]) / 1024;
			size_t mbyte = kibyte / 1024;
			cout << "try allocation new(nothrow) int[" << blocksize << "] with size: " << mbyte << " megabytes";
			int * buffptr = new(nothrow) int[blocksize];
			if (buffptr == nullptr) {
				cout << "\n!! null returned - can not allocate mem of size " << mbyte << " megabytes !!\n";
				break;
			}
			cout << " and use it ...\n";
			for (size_t i = 0; i < blocksize; ++i)
				*(buffptr + i) = 0;
			delete[] buffptr;
			blocksize <<= 1;
		}
	}

	cout << "END" << endl;
	return 0;
}
