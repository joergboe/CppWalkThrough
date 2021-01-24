/*
 * Definitions.cpp
 *
 *  Created on: Nov 24, 2019
 *      Author: joergboe
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

constexpr size_t BUFFSIZE = 1024000;

//A class with default constructor that makes a printout
class MyClass {
public:
	int i;
	MyClass(): i(55) {
		cout << "MyClass()" << endl;
	}
};

//A class with default constructor which does not initialize all members
struct MyInaccurateClass {
	int i, j;
	MyInaccurateClass(): i{56} {};
};

int ig;                     //global variable - defined value 0

MyClass myClassg;           //global userderfined type

char buffg[BUFFSIZE];       //global array defined ?

void checkZerosInArray(char arr[BUFFSIZE], char const * name); //Function definition

bool allZerosInArray(char arr[BUFFSIZE], size_t number); //Function definition

int main(int argc, char **argv) {
	cout << "****** Definitions ******" << endl;

	{
		cout << "\nGlobal variables without initializer are always initialized with 0:" << endl;
		cout << "ig=" << ig << " myClassg.i=" << myClassg.i << endl;
		checkZerosInArray(buffg, "buffg");
	}
	{
		char buffx[BUFFSIZE];
		for (size_t i = 0; i < BUFFSIZE; i++) {
			buffx[i] = '@';
		}
		checkZerosInArray(buffx, "buffx");
		char * buffy = new char[BUFFSIZE];
		for (size_t i = 0; i < BUFFSIZE; i++) {
			buffy[i] = '@';
		}
		checkZerosInArray(buffy, "buffy");
		delete buffy;
	}
	{
		cout << "\nLocal variables (on stack) without initializer have no defined value!" << endl;
		int il;                    //not defined
		char buffl[BUFFSIZE];           //not defined
		cout << "il=" << il << endl;
		checkZerosInArray(buffl, "buffl");
	}
	{
		cout << "\nVariables on heap without initializer have no defined value!" << endl;
		int* ph{new int};          // *ph not defined
		cout << "*ph=" << *ph << endl;
		vector<char*> heapbuffers{};
		size_t count = 0;
		bool allZero;
		do {
			char* buffh{ new char[BUFFSIZE]}; //buffh[i] not defined
			allZero = allZerosInArray(buffh, count);
			heapbuffers.push_back(buffh);
			++count;
		} while ((count < 10000) && allZero);
		cout << count << " buffers checked!" << endl;
		delete ph;
		for (char* buff: heapbuffers)
			delete[] buff;
	}
	{
		cout << "\nExplicit Initialization is required for heap and stack values!" << endl;
		int is2{};                      //defined value 0
		cout << "is2=" << is2 << endl;
		char buffs2[BUFFSIZE]{};            //defined values 0
		checkZerosInArray(buffs2, "buffs2");

		int* ph2{new int{}};            //defined value 0
		char* buffh2{ new char[BUFFSIZE]{}}; //defined values 0
		checkZerosInArray(buffh2, "buffh2");
		delete ph2;
		delete buffh2;
	}

	cout << "\nUser defined types use always constructors" << endl;
	string s;            //empty string
	string* ps{new string}; //*ps is empty string
	cout << "s.empty()=" << s.empty() << endl;
	cout << "*ps.empty()=" << ps->empty() << endl;

	cout << "\nConstructor MyClass() is called for all cg (at the beginning) cl ca[0], ca[1], ca[2], cp (6 *)" << endl;
	MyClass cl;
	MyClass ca[3];
	MyClass * cp = new MyClass;

	cout << "\nBut if a user defined constructor is not complete ..." << endl;
	vector<MyInaccurateClass*> v;
	size_t count = 0;
	MyInaccurateClass* x;
	do {
		x = new MyInaccurateClass;
		v.push_back(x);
		++count;
	} while((count < 100000) && (x->i == 56) && (x->j == 0));
	if (count < 100000) {
		cout << "First uninitialized value found at count=" << count << " x->i=" << x->i << " x->j=" << x->j << endl;
	} else {
		cout << "No uninitialized value found" << endl;
	}
	for ( MyInaccurateClass* i : v)
		delete i;

	delete ps;
	delete cp;

	cout << "Use always initializers!\n"
			"The only reasonable exception from this rule are buffers, where the initialization is not necessary and might be expensive.\n"
			"End!" << endl;
	return EXIT_SUCCESS;
}

void checkZerosInArray(char arr[BUFFSIZE], char const * name) { //Function declaration
	size_t buffzeros = 0;
	for (size_t i = 0; i < BUFFSIZE; i++) {
		if ( arr[i] == 0) {
			++buffzeros;
		}
	}
	cout << name << " contains " << buffzeros << " zero characters in buffer with length=" << BUFFSIZE << endl;
}

bool allZerosInArray(char arr[BUFFSIZE], size_t number) {
	size_t buffzeros = 0;
	for (size_t i = 0; i < BUFFSIZE; i++) {
		if ( arr[i] == 0) {
			++buffzeros;
		}
	}
	if (buffzeros == BUFFSIZE) {
		return true;
	} else {
		cout << "buffer number: " << number << " contains " << buffzeros << " zero characters in buffer with length=" << BUFFSIZE << endl;
		return false;
	}
}
