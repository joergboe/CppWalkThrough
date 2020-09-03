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
struct MyBuggyClass {
	int i, j;
	MyBuggyClass(): i{56} {};
};

int ig;                      //defined value 0

MyClass myClassg;

char buffg[BUFFSIZE];            //defined ?

int main(int argc, char **argv) {
	cout << "Hello Definitions" << endl;

	{
		cout << "Global values are defined:" << endl;
		cout << "ig=" << ig << " myClassg.i=" << myClassg.i << endl;
		size_t buffzeros = 0;
		for (size_t i=0; i<sizeof buffg; i++) {
			if ( buffg[i] == 0) {
				++buffzeros;
			}
		}
		cout << "buffg contains " << buffzeros << " zero characters in buffer with length=" << sizeof buffg << endl;
	}

	cout << "Variables on stack are not defined when not initialized!" << endl;
	{
		int is;                    //not defined
		char buffs[BUFFSIZE];           //not defined
		cout << "is=" << is << endl;
		size_t buffzeros = 0;
		for (size_t i=0; i<sizeof buffs; i++) {
			if (buffs[i] == 0) {
				++buffzeros;
			}
		}
		cout << "buffs contains " << buffzeros << " zero characters in buffer with length=" << sizeof buffs << endl;
	}

	cout << "Variables on heap are not defined when not initialized!" << endl;
	{
		int* ph{new int};          // *ph not defined
		char* buffh{ new char[BUFFSIZE]}; //buffh[i] not defined
		cout << "*ph=" << *ph << endl;
		size_t buffzeros = 0;
		for (size_t i=0; i<sizeof(char[BUFFSIZE]); i++) {
			if (buffh[i] == 0) {
				++buffzeros;
			}
		}
		cout << "buffh contains " << buffzeros << " zero characters in buffer with length=" << sizeof(char[BUFFSIZE]) << endl;
		buffh[55] = 'a';
		cout << "huffh[55]=" << buffh[55] << endl;
		delete ph;
		delete buffh;
	}

	cout << "Explicit Initialization/Definition is required for heap and stack values!" << endl;
	{
		int is2{};                      //defined value 0
		cout << "is2=" << is2 << endl;
		char buffs2[BUFFSIZE]{};            //defined values 0
		size_t buffzeros = 0;
		for (size_t i=0; i<sizeof buffs2; i++) {
			if (buffs2[i] == 0) {
				++buffzeros;
			}
		}
		cout << "buffs2 contains " << buffzeros << " zero characters in buffer with length=" << sizeof buffs2 << endl;

		int* ph2{new int{}};            //defined value 0
		char* buffh2{ new char[BUFFSIZE]{}}; //defined values 0
		buffzeros = 0;
		for (size_t i=0; i<sizeof(char[BUFFSIZE]); i++) {
			if (buffh2[i] == 0) {
				++buffzeros;
			}
		}
		cout << "buffh2 contains " << buffzeros << " zero characters in buffer with length=" << sizeof(char[BUFFSIZE]) << endl;
		delete ph2;
		delete buffh2;
	}

	cout << "User types use always constructors" << endl;
	string s;            //empty string
	string* ps{new string}; //*ps is empty string
	cout << "s.empty()=" << s.empty() << endl;
	cout << "*ps.empty()=" << ps->empty() << endl;

	cout << "Constructor MyClass() is called for all cg (at the beginning) cl ca[0], ca[1], ca[2], cp (6 *)" << endl;
	MyClass cl;
	MyClass ca[3];
	MyClass * cp = new MyClass;

	cout << "But if constructor is not complete ..." << endl;
	vector<MyBuggyClass*> v;
	size_t count = 0;
	MyBuggyClass* x;
	do {
		x = new MyBuggyClass;
		v.push_back(x);
		++count;
	} while((count < 100000) && (x->i == 56) && (x->j == 0));
	if (count < 100000) {
		cout << "First uninitialized value found at count=" << count << "x->i=" << x->i << "x->j=" << x->j << endl;
	} else {
		cout << "No uninitialized value found" << endl;
	}
	for ( MyBuggyClass* i : v)
		delete i;

	delete ps;
	delete cp;

	cout << "End!" << endl;
	return EXIT_SUCCESS;
}

