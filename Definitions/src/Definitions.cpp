/*
 * Definitions.cpp
 *
 * More about variable definition and initialization.
 *
 *  Created on: Nov 24, 2019
 *      Author: joergboe
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

constexpr size_t BUFFSIZE = 1024000;

/* A class with default constructor that makes a printout */
class MyClass {
public:
	int i;
	MyClass(): i(55) {
		cout << "MyClass()" << endl;
	}
	~MyClass() {
		cout << "~MyClass()" << endl;
	}
};

/* A class with default constructor which does not initialize all members */
struct MyInaccurateClass {
	int i, j;
	MyInaccurateClass(): i{56} {};
};

/* global variable definitions
 * if global variables do not have an initializer, they are always zero initialized-
 * Initialization takes place during program startup (thread save)
 */
int ig;                //global variable - defined value 0
char buffg[BUFFSIZE];  //global array defined ?
MyClass myClassg;      //global user defined type

/* helper functions */
bool checkAllZerosInArray(char const (& arr)[BUFFSIZE], bool silent = true); //Function definition


/* A function that uses static variables */
void useStaticVars() {
	cout << "Enter useStaticVars\n";
	static int is;
	static char buffs[BUFFSIZE];
	static MyClass myClasss;

	cout << "is=" << is << " myClasss.i=" << myClasss.i << endl;
	checkAllZerosInArray(buffs, false);

	cout << "Leave useStaticVars\n";
}

int main(int argc, char **argv) {
	cout << "****** Definitions ******" << endl;

	{
		cout << "\nGlobal variables without initializer are always initialized with 0:" << endl;
		cout << "ig=" << ig << " myClassg.i=" << myClassg.i << endl;
		checkAllZerosInArray(buffg, false);
	}
	{
		cout << "\nLocal variables (on stack) without initializer have no defined value!" << endl;
		int il;                    //not defined
		char buffl1[BUFFSIZE];           //not defined
		cout << "il=" << il << endl;
		checkAllZerosInArray(buffl1, false);
		char buffl2[BUFFSIZE];           //not defined
		checkAllZerosInArray(buffl2, false);
		char buffl3[BUFFSIZE];           //not defined
		checkAllZerosInArray(buffl3, false);
	}
	{
		cout << "\nVariables on heap without initializer have no defined value guaranteed!" << endl;
		cout << "Check ihp = new int\n";
		vector<int*> heapints;
		int count1 = 0;
		int* ihp;
		do {
			ihp = new int;          // *ihp not defined
			heapints.push_back(ihp);
			if ((count1 % 1000) == 0)
				cout << count1 << " " << std::flush;
			if ((count1 % 100000) == 0)
				cout << endl;
			++count1;
		} while ((*ihp == 0) && (count1 < 1000000));
		cout << "first value different from zero at attempt " << count1 << " *ihp=" << *ihp << endl;
		for (int* x : heapints)
			delete x;

		cout << "Check char* buffhp{new char[BUFFSIZE]}\n";
		vector<char*> heapbuffers{};
		size_t count2 = 0;
		bool allZero;
		do {
			char* buffhp = new char[BUFFSIZE]; //buffh[i] not defined
			char (&buffhr)[BUFFSIZE] = reinterpret_cast<char (&)[BUFFSIZE]>(*buffhp);
			allZero = checkAllZerosInArray(buffhr, true);
			heapbuffers.push_back(buffhp);
			if ((count2 % 100) == 0)
				cout << count2 << " " << flush;
			if ((count2 % 1000) == 0)
				cout << endl;
			++count2;
		} while ((count2 < 1000000) && allZero);
		cout << count2 << " buffers checked!" << endl;
		for (char* buff: heapbuffers)
			delete[] buff;
	}
	{
		cout << "\nExplicit Initialization is required for heap and stack values!" << endl;
		int is2{};                      //defined value 0
		cout << "is2=" << is2 << endl;
		char buffs2[BUFFSIZE]{};            //defined values 0
		checkAllZerosInArray(buffs2, false);

		int* ph2{new int{}};            //defined value 0
		char* buffh2{ new char[BUFFSIZE]{}}; //defined values 0
		char (&buffhr2)[BUFFSIZE] = reinterpret_cast<char (&)[BUFFSIZE]>(*buffh2);
		checkAllZerosInArray(buffhr2, false);
		delete ph2;
		delete buffh2;
	}

	cout << "\nNow call useStaticVars...\n";
	cout << "Static variables without initializer are always initialized.\n"
			"The point of initialization is the first usage.\n";
	useStaticVars();
	useStaticVars();

	{
		cout << "\nUser defined types use always constructors" << endl;
		string s;            //empty string
		string* ps{new string}; //*ps is empty string
		cout << "s.empty()=" << s.empty() << endl;
		cout << "*ps.empty()=" << ps->empty() << endl;
		delete ps;

		cout << "\nConstructor MyClass() is called for all cg (at the beginning) cl ca[0], ca[1], ca[2], cp (4 *)" << endl;
		MyClass cl;
		MyClass ca[3];
		MyClass * cp = new MyClass[4];
		delete[] cp;
	}
	{
		cout << "\nBut if a user defined constructor fails to initialize all members ..." << endl;
		vector<MyInaccurateClass*> v;
		size_t count = 0;
		MyInaccurateClass* x;
		do {
			x = new MyInaccurateClass;
			v.push_back(x);
			++count;
		} while((count < 100000) && (x->i == 56) && (x->j == 0));
		if (count < 100000) {
			cout << "First uninitialized value found at count=" << count << " : x->i=" << x->i << " x->j=" << x->j << endl;
		} else {
			cout << "No uninitialized value found" << endl;
		}
		for ( MyInaccurateClass* i : v)
			delete i;
	}

	cout << "\n*** Recommendation ***\n"
			"Use always initializers!\n\n"
			"The only reasonable exception from this rule are buffers, where the\n"
			"initialization is not necessary and might be expensive.\n\n"
			"User defined class variables are always constructed either with\n"
			"a compiler generated constructor or with a user defined constructor.\n\n"
			"If the program runs more than one thread, global variables and\n"
			"static function variables may be accessed concurrently.\n\n"
			"The initialization of global variables is made during program start and is thread save.\n"
			"Global and static function variables are destructed during program shutdown\n\n";

	cout << "END" << endl;

	return EXIT_SUCCESS;
}

bool checkAllZerosInArray(char const (&arr)[BUFFSIZE], bool silent) {
	size_t buffzeros = 0;
	for (size_t i = 0; i < sizeof arr; i++) { // //sizeof(char) is per definition 1
		if ( arr[i] == 0) {
			++buffzeros;
		}
	}
	bool retval = buffzeros == sizeof arr;
	if ( ! retval || ! silent)
		cout << "buffer of length " << sizeof arr << " contains " << buffzeros << " zeros." << endl;
	return retval;
}
