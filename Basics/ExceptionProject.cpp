//============================================================================
// Name        : ExceptionProject.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::invalid_argument;

/*
 * myfunc throws exceptions depending on the input value
 */
void myfunc(int inp);

/*
 * A user defined data type to be thrown
 */
class MyClass {
public:
	MyClass(char const * reason_, int i_) :
		reason(reason_),
		i(i_) {
		cout << "MyClass(char const * reason, int i)\n";
	}
	MyClass(MyClass const & myclass) :
		reason(myclass.reason),
		i(myclass.i) {
		cout << "MyClass(MyClass const & myclass)\n";
	}
	// TODO: Is copy constructor sufficient ?
	MyClass& operator=(MyClass const & myclass) = delete;

	~MyClass() {
		cout << "~MyClass()\n";
	}
	char const * reason;
	int const i;
};

int main() {
	cout << "Demonstration of basic exception principles\n"
			"ExceptionProject START\n\n";

	cout << "Throw different types and catch by value\n"
			"*********************************************************\n"
			"The exception of type E is caught in the catch-clause of type H if any of the following is true:\n"
			"1. E and H are the same type (ignoring top-level cv-qualifiers on H)\n\n";
	for (int i=0; i<=9; i++) {
		try {
			myfunc(i);
		} catch (int e) {
			cout << "catch (int e)\n"
					"e: " << e << " typeid: " << typeid(e).name() << "\n";
			if (e != 0)
				cout << "Note: const qualifier from int const is discarded during type deduction in throw statement!\n";
		} catch (char e) {
			cout << "catch (char e)\n"
					"e: " << e << " typeid: " << typeid(e).name() << "\n";
			if (e != 'x')
				cout << "Note: const qualifier is discarded during type deduction in throw statement!\n";
		} catch (float e) {
			cout << "catch (float e)\n"
					"e: " << e << " typeid: " << typeid(e).name() << "\n";
			if (e > 12.0f)
				cout << "Note: const qualifier is discarded during type deduction in throw statement!\n";
		} catch (string e) {
			cout << "catch (string e)\n"
					"e: " << e << " typeid: " << typeid(e).name() << "\n";
			if (e.compare("Reason inp=8") == 0)
				cout << "Note: const qualifier is discarded during type deduction in throw statement!\n";
		} catch (MyClass e) {
			cout << "catch (MyClass e)\n"
					"e.reason: " << e.reason << " typeid: " << typeid(e).name() << "\n"
					"Note: Exception objects are copied! So e must be copyable.\n";
			if (e.i == 9)
				cout << "Note: const qualifier is discarded during type deduction in throw statement!\n";
		}
		cout << endl;
	}

	cout << "\n"
			"The top level cv-qualifier in the catch-clause is ignored during exception handler detection.\n"
			"It prevents us from changing e\n";
	for (int i : {0, 1, 4, 5, 6, 9}) {
		try {
			myfunc(i);
		} catch (const int e) {
			cout << "catch (int const e)\n"
					"e: " << e << "\n";
			//e = 15; //error: assignment of read-only variable ‘e’
			if (e != 0)
				cout << "Note: const qualifier from int const is discarded during type deduction in throw statement!\n";
		} catch (char const e) {
			cout << "catch (char const e)\n"
					"e: " << e << "\n";
			if (e != 'x')
				cout << "Note: const qualifier is discarded during type deduction in throw statement!\n";
		} catch (MyClass const e) {
			cout << "catch (MyClass const e)\n"
					"e.reason: " << e.reason << "\n";
			if (e.i == 9)
				cout << "Note: const qualifier is discarded during type deduction in throw statement!\n";
		}
		cout << endl;
	}

	cout << "\n*********************************************************\n"
			"The exception of type E is caught in the catch-clause of type H if any of the following is true:\n"
			"1. E and H are the same type (ignoring top-level cv-qualifiers on H)\n"
			"2. H is an unambiguous public base class of E\n\n";

	for (int i : {12, 13}) {
		try {
			myfunc(i);
		} catch (invalid_argument e1) {
			cout << "catch (invalid_argument e1)\n"
				"e1.what(): " << e1.what() << endl;
		} catch (exception e2) {
			cout << "catch (exception e2)\n"
				"e2.what(): " << e2.what() << endl;
		}
		cout << endl;
	}
	cout << "The order of the catch-clauses matters. Put siblings before base.\n"
			"Otherwise the clause with the base consumes all exceptions.\n"
			"\nTo catch class types by value is not recommended because e is not polymorphous\n\n";

	cout << "\n*********************************************************\n"
			"Catch by reference:\n"
			"The exception of type E is caught in the catch-clause of type H if any of the following is true:\n"
			"1. E and H are the same type (ignoring top-level cv-qualifiers on H)\n"
			"2. H is an unambiguous public base class of E\n"
			"3. H is an lvalue-reference to (possibly cv-qualified) E\n"
			"4. H is a reference to an unambiguous public base class of E\n\n";

	for (int i : {0, 12, 13}) {
		try {
			myfunc(i);
		} catch (invalid_argument & e) {
			cout << "catch (invalid_argument & e)\n"
				"e.what(): " << e.what() << endl;
		} catch (exception const & e) {
			cout << "catch (exception const & e)\n"
				"e.what(): " << e.what() << endl;
		} catch (int const & e) {
			cout << "catch (int const & e)\n"
				<< "e: " << e << endl;

		}
		cout << endl;
	}
	cout << "The order of the catch-clauses matters. Put the sibling before the base.\n"
			"Otherwise the clause with the base consumes all exceptions.\n\n";

	cout << "\n*********************************************************\n"
			"Catch by reference:\n"
			"The exception of type E is caught in the catch-clause of type H if any of the following is true:\n"
			"1. E and H are the same type (ignoring top-level cv-qualifiers on H)\n"
			"2. H is an unambiguous public base class of E\n"
			"3. H is an lvalue-reference to (possibly cv-qualified) E\n"
			"4. H is a reference to an unambiguous public base class of E\n"
			"5. H is (possibly cv-qualified) U, and U is a pointer type, and E is also a pointer type that is implicitly convertible to U by one or more of\n"
			"		* a standard pointer conversion other than one to a private, protected, or ambiguous base class\n"
			"		* a qualification conversion\n\n";

	int arr4[] = {10, 11, 14, 15};
	for (int i : arr4) {
		try {
			myfunc(i);
		} catch (char const * e) {
			cout << "catch (char const * e) or catch (char const * const e)\n"
					"e: " << e << endl <<
					"This catches both exceptions of type 'car *' and 'char const *'\n"
					"'char *' can be converted to 'char const *' (qualification conversion)\n";
		} catch (exception * e) {
			cout << "catch (exception * e)\n"
					"e.what(): " << e->what() << endl <<
					"This catches all exceptions with pointer type to 'std::exception' and descendant types.\n"
					"'invalid_argument *' can be converted to 'exception *' (standard pointer conversion)\n"
					"This clause is polymorphous: the type where e points to may be std::exception or descendant classes"
					"Note: clean up memory!\n";
			delete e;
		}
		cout << endl;
	}

	cout << "\nThis works also with a top level const qualification for e:\n";
	for (int i : arr4) {
		try {
			myfunc(i);
		} catch (char const * const e) {
			cout << "catch (char const * const e)\n"
					"e: " << e << endl;
		} catch (exception * const e) {
			cout << "catch (exception * const e)\n"
					"e.what(): " << e->what() << endl;
			delete e;
		}
		cout << endl;
	}

	cout << "\n*********************************************************\n"
			"Catch all:\n"
			"Handler with unnamed parameter:\n"
			"\nA 'char const *' can not be converted to a 'cahr *', thus #11 falls through!\n"
			"But the ellipsis '...' catches all exceptions.\n";
	for (int i : {10, 11, 16}) {
		try {
			myfunc(i);
		} catch (char * e) {
			cout << "catch (char * e)\n"
					"e: " << e << endl;
		} catch (void*) {
			cout << "catch (void*)\n"
					"catch-clause with unnamed parameter.\n";
		} catch (...) {
			cout << "catch (...)\n";
		}
		cout << endl;
	}

	cout << "\n*********************************************************\n"
			"Re-throw exceptions:\n"
			"\nA use throw to re-throw an exception.\n";

	int counter = 0;
	for (int i : {13, 13, 13}) {
		try {
			try {
				myfunc(i);
			} catch (exception const & e) {
				++counter;
				if (counter == 1) {
					cout << "throw\n";
					throw;
				} else if (counter == 2){
					cout << "throw e\n";
					throw e;
				} else {
					cout << "throw 125\n";
					throw 125;
				}
			}
		} catch (exception const & error) {
			cout << "error.what(): " << error.what() << endl;
			cout << "typeid: " << typeid(error).name() << endl;;
		} catch (int & e) {
			cout << "catch (int & e)\n"
					"e: " << e << endl;

		}
		cout << endl;
	}

	cout << "\n'throw' re-throws the actual (polymorphous) type of e.\n"
			"'throw e' re-throws the static type of e (slicing!)\n";

	cout << "\n*********************************************************\n"
			"Recommendation:\n"
			"* throw descendant types of 'std::exception' by value,\n"
			"* catch by reference or const reference ('catch (std::exception const &)'),\n"
			"* re-throw with 'throw' or throw anything else. (Do not use 'throw e'),\n"
			"* use the final catch all clause ('catch(...)') if necessary";
	cout << endl;

	cout << "Unhandled exceptions terminate the program!\n\n";
	//throw 88;

	cout << "ExceptionProject END" << endl;
	return 0;
}

void myfunc(int inp) {
	cout << "myfunc(" << inp << ")" << endl;
	static char cparray[] = "Reason inp=11";
	switch (inp) {
		case 0: {
			cout << "inp=0: throw fundamental type int\n";
			int e = 0;
			throw e;
		}
		case 1: {
			cout << "inp=1: throw fundamental type char\n";
			char e = 'x';
			throw e;
		}
		case 2: {
			cout << "inp=2: throw fundamental type float\n";
			float e = 11.1f;
			throw e;
		}
		case 3:
			cout << "inp=3: throw library type string\n";
			throw string("Reason inp=3");
		case 4:
			cout << "inp=4: throw user defined type MyClass\n";
			throw MyClass("inp=4", 4);
		case 5: {
			cout << "inp=5: throw fundamental type int const" << endl;
			int const e = 5;
			throw e;
		}
		case 6: {
			cout << "inp=6: throw fundamental type char const\n";
			char const e = 'y';
			throw e;
		}
		case 7: {
			cout << "inp=7: throw fundamental type float const\n";
			float const e = 22.2f;
			throw e;
		}
		case 8: {
			cout << "inp=8: throw library type string const\n";
			string const e = "Reason inp=8";
			throw e;
		}
		case 9: {
			cout << "inp=9: throw user defined type MyClass const\n";
			MyClass e("inp=9", 9);
			throw e;
		}
		case 10: {
			cout << "inp=10: throw pointer to fundamental type char const *\n";
			char const * cp = "Reason inp=10";
			throw cp;
		}
		case 11: {
			cout << "inp=11: throw pointer to fundamental type char *\n";
			char * cp = cparray;
			throw cp;
		}
		case 12:
			cout << "inp=12: throw std::exception" << endl;
			throw exception();
		case 13:
			cout << "inp=13: throw std lib error type a sibling from std::exception\n";
			throw invalid_argument("Reason inp=13");
		case 14:
			cout << "inp=14: throw exception pointer type std::exception\n";
			throw new exception();
		case 15:
			cout << "inp=15: throw exception pointer with std lib error type a sibling from std::exception\n";
			throw new invalid_argument("Reason inp=15");
		case 16: {
			cout << "inp=16: throw a void pointer\n";
			void *ptr = cparray;
			throw ptr;
		}
		default:;
	};
}
