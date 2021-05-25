/*
 * Definitions.cpp
 *
 * More about variable default initialization
 * that is variable initialization without initializer
 *
 *      Author: joergboe
 */

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

constexpr size_t BUFFSIZE = 1024000;

/* A class with default constructor that makes a printout */
class MyClass {
	static int instanceCount;
public:
	const int instance;
	int i;
	MyClass(): instance(instanceCount), i(55) {
		cout << "MyClass() instance=" << instance << endl;
		++instanceCount;
	}
	~MyClass() {
		cout << "~MyClass()) instance=" << instance << endl;
	}
};

/* A class with default constructor which does not initialize all members */
struct MyClassPartInit {
	int i, j;
	MyClassPartInit(): i{56} {}
};

/* Compiler defined constructors do not initialize POD members */
struct MyTrivialConstructedClass {
	int i, j;
};

/* helper functions */
bool checkAllZerosInArray(char const (& arr)[BUFFSIZE], bool silent = true); //Function declaration

/* A function that uses static variables */
void useStaticVars();

/* global variable definitions
 * Global variables are placed in a special memory segment, that is zero initialized.
 * if global variables do not have an initializer, they are always zero initialized-
 * Initialization takes place during program startup. If the program runs more than one
 * thread the initialization may run concurrently.
 */
int ig;                  // zero initialized
char buffg[BUFFSIZE];    // all zero initialized
MyClass myClassg;        // instance #1
MyClass myClassarr[2];   // constructors are executed for all aggregate members
MyClassPartInit myClassPartInitg; // all zero initialized
MyTrivialConstructedClass myTrivialConstructedClassg; // all zero initialized

/* Thread local
 * Thread local variables are placed in a special memory segment, that is zero initialized.
 * */
int thread_local it; // zero initialized
MyClass thread_local myClasst;
MyClassPartInit thread_local myClassPartInitt;

int main() {
	cout << "****** START Main DefaultInitialization ******" << endl;
	{
		cout << "\n**** Global variables ****\n";
		cout << "* Global variables without initializer are always initialized with 0:" << endl;
		cout << "ig=" << ig << endl;
		checkAllZerosInArray(buffg, false);
		cout << "myClassg.i=" << myClassg.i << " instance=" << myClassg.instance << endl;
		cout << "* That also true for class/struct types with incomplete constructors!\n";
		cout << "myClassPartInitg: i=" << myClassPartInitg.i << " j=" << myClassPartInitg.j << endl;
		cout << "myTrivialConstructedClassg: i=" << myTrivialConstructedClassg.i << " j=" << myTrivialConstructedClassg.j << endl;
	}
	{
		cout << "\n\n**** Local variables ****\n";
		cout << "* Local variables (on stack) without initializer have no defined value!" << endl;
		int il;                    //not defined
		char buffl1[BUFFSIZE];     //not defined
		cout << "il=" << il << endl;
		checkAllZerosInArray(buffl1, false);
		char buffl2[BUFFSIZE];           //not defined
		checkAllZerosInArray(buffl2, false);
		char buffl3[BUFFSIZE];           //not defined
		checkAllZerosInArray(buffl3, false);

		cout << "\n* For class/struct types, the constructor is always called.\n"
				"* But if the constructor fails to initialize all (non-static) members, the values are undefined!\n";
		MyClass myClassl; // instance #4
		MyClassPartInit myClassPartInitl;
		MyTrivialConstructedClass myTrivialConstructedClassl;
		cout << "myClassl.i=" << myClassl.i << " instance=" << myClassl.instance << endl;
		cout << "myClassPartInitl: i=" << myClassPartInitl.i << " j=" << myClassPartInitl.j << endl;
		cout << "myTrivialConstructedClassl: i=" << myTrivialConstructedClassl.i << " j=" << myTrivialConstructedClassl.j << endl;
		cout << "* The destructor of local variables is called when the variables go out of scope.\n";
	}

	cout << "\n\n **** Static Variables ****\n";
	cout << "* Static variables without initializer are always initialized.\n"
			"* The point of initialization is the first usage.\n"
			"* The initialization but only the initialization of static variables is thread save.\n";
	useStaticVars();
	useStaticVars();

	cout << "\n\n **** Thread local variables ****\n"
			"* thread-local variables get zero initialized.\n"
			"* All non-local variables with thread-local storage duration are\n"
			"initialized as part of thread launch, sequenced-before the execution of the thread function begins.\n";
	cout << "it=" << it << endl;
	cout << "myClasst: i=" << myClasst.i << " instance=" << myClasst.instance << endl;
	cout << "myClassPartInitt: i=" << myClassPartInitt.i << " j=" << myClassPartInitt.j << endl;
	{
		static thread_local MyClass myClassst; // instance #7
		static thread_local MyClassPartInit myClassPartInitst;
		cout << "myClassst: i=" << myClassst.i << " instance=" << myClassst.instance << endl;
		cout << "myClassPartInitst: i=" << myClassPartInitst.i << " j=" << myClassPartInitst.j << endl;
	}

	{
		cout << "\n\n **** Dynamic Variables ****\n";
		cout << "* Dynamic Variables (on heap memory) without initializer have no defined value guaranteed!\n";
		cout << "\n*** Check initialization of int variables on heap ihp = new int\n";
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
		if (count1 < 1000000)
			cout << "first value different from zero at attempt " << count1 << " *ihp=" << *ihp << endl;
		else
			cerr << "no different from zero found. This may happen\n";
		for (int* x : heapints)
			delete x;

		cout << "\n*** Check char* buffhp{new char[BUFFSIZE]}\n";
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
		if (count2 == 1000000)
			cerr << "No value different from zero found. This may happen.\n";
		for (char* buff: heapbuffers)
			delete[] buff;
	}
	{
		cout << "\n* Explicit Initialization is required for heap and stack values!" << endl;
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

	{
		cout << "\n**** User defined types use always constructors\n";
		cout << "\n* Constructor MyClass() is called for all cg (at the beginning) an for cl and cp now.\n";
		MyClass cl; // instance 8
		MyClass * cp = new MyClass; // instance #9
		cout << "Destruction is done when dynamic memory is deleted.\n";
		delete cp;
		cout << "Destruction is done when local variables go out of scope.\n";
	}
	{
		cout << "\n**** User defined types use always constructors in arrays!\n";
		cout << "Construct ca[0], ca[1], ca[2]" << endl;
		MyClass ca[3];
		cout << "Now new MyClass[4]\n";
		MyClass * cp = new MyClass[4];
		cout << "delete[] cp\n";
		delete[] cp;
		cout << "MyClass ca[3] goes out of scope\n";
	}
	{
		cout << "\n* But if a user defined constructor fails to initialize all members ..." << endl;
		vector<MyClassPartInit*> v;
		size_t count = 0;
		MyClassPartInit* x;
		do {
			x = new MyClassPartInit;
			v.push_back(x);
			++count;
		} while((count < 100000) && (x->i == 56) && (x->j == 0));
		if (count < 100000) {
			cout << "First uninitialized value found at count=" << count << " : x->i=" << x->i << " x->j=" << x->j << endl;
		} else {
			cerr << "No uninitialized value found. This may happen." << endl;
		}
		for ( MyClassPartInit* i : v)
			delete i;
	}

	cout << "\n*** Recommendation ***\n"
			"Use always initializers!\n\n"
			"The only reasonable exception from this rule are buffers, where the\n"
			"initialization is not necessary and might be expensive.\n\n"
			"Default initialization of non-class variables with automatic and dynamic\n"
			"storage duration produces objects with indeterminate values.\n"
			"static and thread-local variables get zero initialized.\n"
			"References and const scalar objects cannot be default-initialized.\n\n"
			"User defined class variables are always constructed either with\n"
			"a compiler generated constructor or with a user defined constructor.\n\n"
			"If the program runs more than one thread, global variables and\n"
			"static function variables may be accessed concurrently.\n\n"
			"The initialization of global variables is made during program start.\n"
			"If the program runs more than one thread this initialization may run concurrently.\n"
			"The initialization of static variables in function scope is thread save.\n\n"
			"Global and static function variables are destructed during program shutdown\n\n";

	cout << "END" << endl;

	return EXIT_SUCCESS;
}

/* A function that uses static variables */
void useStaticVars() {
	cout << "Enter useStaticVars\n";
	static int is;
	static char buffs[BUFFSIZE];
	static MyClass myClasss;

	cout << "is=" << is << " myClasss.i=" << myClasss.i << " instance=" << myClasss.instance << endl;
	checkAllZerosInArray(buffs, false);

	cout << "Leave useStaticVars\n";
}

bool checkAllZerosInArray(char const (&arr)[BUFFSIZE], bool silent) {
	size_t buffzeros = 0;
	for (size_t i = 0; i < sizeof arr; i++) { //sizeof(char) is per definition 1
		if ( arr[i] == 0) {
			++buffzeros;
		}
	}
	bool retval = buffzeros == sizeof arr;
	if ( ! retval || ! silent)
		cout << "buffer of length " << sizeof arr << " contains " << buffzeros << " zeros." << endl;
	return retval;
}

int MyClass::instanceCount = 1;
