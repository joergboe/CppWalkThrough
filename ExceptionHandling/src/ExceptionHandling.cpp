//============================================================================
// Name        : ExceptionHandling.cpp
// Author      : jb
//============================================================================

#include <iostream>
#include <exception>

using std::cout;
using std::cerr;
using std::endl;

void checkCurrentException(std::exception_ptr ep);

void isEqual(std::exception_ptr p1, std::exception_ptr p2);

void reThrowExceptionPointer(std::exception_ptr ep);

void examinateCurrentException();

void printException(std::exception const & e, int level = 0);

int main() {
	cout << "Basic Exception Handling (since C++11)" << endl;

	cout << "The type 'std::exception_ptr' is pointer-like type that manages an exception object which has been thrown.\n"
			"The value for a 'std::exception_ptr' is captured with function 'std::current_exception()'.\n"
			"A default-constructed std::exception_ptr is a null pointer and thus points to no exception object.\n"
			"An instance of 'std::exception_ptr' may be passed to another function for further processing.\n"
			"An instance of 'std::exception_ptr' may be passed to another thread.\n"
			"'std::exception_ptr' is implicitly convertible to a bool, and will evaluate to false if it is null, true otherwise.\n"
			"The exception object referenced by an std::exception_ptr remains valid as long as there remains at least one\n"
			"std::exception_ptr that is referencing it: std::exception_ptr is a shared-ownership smart pointer\n";

	try {
		cout << "\n****** std::current_exception() ******\n";

		cout << "If this function is called during exception handling, it captures the current exception object\n"
				"and creates an std::exception_ptr that holds either a copy or a reference\n"
				"to that exception object. The referenced object remains valid at least\n"
				"as long as there is an exception_ptr object that refers to it.\n"
				"If something went wrong during exception copy, the result may contain a\n"
				"reference or an instance of std::bad_alloc or std::bad_exception\n.";

		cout << "\nIf the function is called when no exception is active, a nullptr is returned.\n";
		std::exception_ptr ep = std::current_exception();
		cout << "Conversion to bool:\n";
		if (! ep) {
			cout << "evaluate to false if it is null\n";
		}
		throw 55;
	} catch (int const & e) {
		cout << "catch (int const & e)\n";
		std::exception_ptr ep = std::current_exception();
		cout << "Handover to function:\n";
		checkCurrentException(ep);
		cout << "'std::exception_ptr' is not implicitly convertible\n";
		//void * vpt = ep; //std::__exception_ptr::exception_ptr’ to ‘void*’  in initialization
	}

	{
		cout << "\n****** std::current_exception and exception nesting ******\n" << endl;
		std::exception_ptr ep0, ep1, ep2, ep3;
		try {
			ep0 = std::current_exception();
			throw 1;
		} catch (int const & e1) {
			cout << "---- catch " << e1 << endl;
			try {
				ep1 = std::current_exception();
				isEqual(ep0, ep1);
				throw 2;
			} catch (int const & e2) {
				cout << "---- catch " << e2 << endl;
				try {
					ep2 = std::current_exception();
					isEqual(ep1, ep2);
					std::throw_with_nested(3); // !!!! Throws a int exception due to 3 is nop class type !!
				} catch (int const & e3) {
				//} catch (std::nested_exception const & e3) {
					cout << "---- catch " << e3 << endl;
					ep3 = std::current_exception();
					isEqual(ep2, ep3);
				}
				cout << "------\n";
				isEqual(ep2, std::current_exception());
			}
			cout << "------\n";
			isEqual(ep1, std::current_exception());
		}
		cout << "------\n";
		isEqual(ep0, std::current_exception());
	}
	try {
		cout << "\n****** std::make_exception_ptr() ******\n";

		cout << "template<class E>\n"
				"std::exception_ptr make_exception_ptr(E e) noexcept\n"
				"This function template creates an std::exception_ptr that holds a reference to a copy of e.\n";
		throw 56;
	} catch (int const & e) {
		cout << "catch (int const & e)\n";
		std::exception_ptr ep = std::make_exception_ptr(e);
		cout << "Handover to function:\n";
		checkCurrentException(ep);
	}

	try {
		cout << "\n****** void std::rethrow_exception(std::exception_ptr ep) noreturn ******\n";
		cout << "Throw a previously captured exception object with 'std::rethrow_exception'.\n"
				"ep must point to an exception object!\n";

		std::exception_ptr ep = std::current_exception();
		checkCurrentException(ep);
		//std::rethrow_exception(ep); //This terminates the program!
		throw 'a';
	} catch (char e) {
		cout << "Exception : " << e << " catched.\n";
		std::exception_ptr ep = std::current_exception();
		try {
			reThrowExceptionPointer(ep);
		} catch (char e) {
			cout << "Exception : " << e << " catched twice.\n";
		}
	}

	cout << "\n****** std::nested_exception, std::throw_with_nested and std::rethrow_if_nested ******\n";
	cout << "'std::nested_exception' is a polymorphic mixin class which can capture and store\n"
			"the current exception, making it possible to nest exceptions of arbitrary types within each other.\n"
			"The class has virtual members (destructor)\n"
			"Members:\n"
			"- Default constructor. Stores an exception object obtained by calling std::current_exception() within the new nested_exception object.\n"
			"- Copy constructor: Copies content from another.\n"
			"- Destructor: virtual"
			"- operator=: repaces content.\n"
			"- void rethrow_nested() const: Rethrows the stored exception.\n"
			"		If there is no stored exceptions (i.e. nested_ptr() returns null pointer), then std::terminate is called.\n"
			"std::exception_ptr nested_ptr() const noexcept: Returns a pointer to the stored exception, if any.\n\n"
			""
			"template< class T >\n"
			"[[noreturn]] void throw_with_nested( T&& t )\n"
			"This function template throws an nested exception object of type T and with the current exception captured.\n"
			"NOTE: T must be a non-final non-union class type that is neither std::nested_exception nor derived from std::nested_exception!\n\n"
			""
			"template< class E >\n"
			"void rethrow_if_nested( const E& e )\n"
			"This function template throws the nested exception. If e is not a nested exception, the function has no effect.\n"
			"Unlike many related functions, this function is not intended to be called with a 'std::exception_ptr' but rather an actual exception reference.\n"
			"NOTE: If E is not a polymorphic class type, or if std::nested_exception is an inaccessible or ambiguous base class of E, there is no effect!\n\n"
			""
			"NOTE: Exception nesting makes sense only if the used exceptions are of type std::exception or public derived from std::exception.\n\n";

	try {
		cout << "throw  std::runtime_error(\"ex 1\")\n";
		throw std::runtime_error("ex 1");
	} catch (std::exception const & e1) {
		cout << "catch (std::exception const & e1): " << e1.what() << endl;
		try {
			cout << "std::throw_with_nested(std::runtime_error(\"ex 2\"))\n";
			std::throw_with_nested(std::runtime_error("ex 2"));
		} catch (std::exception const & e2) {
			cout << "catch (std::exception const & e2): " << e2.what() << endl;
			try {
				cout << "std::rethrow_if_nested(e2)\n";
				std::rethrow_if_nested(e2);
				cerr << "Nothing thrown!\n";
			} catch (std::exception const & e3) {
				cout << "catch (std::exception const & e3): " << e3.what() << endl;
				cout << "std::rethrow_if_nested(e3)\n";
				std::rethrow_if_nested(e3);
				cout << "Nothing thrown! and END\n";
			}
		}
	}

	cout << "\nDefault constructor of std::nested_exception stores the current exception!\n";

	try {
		throw std::runtime_error("error 1");
	} catch (std::exception const & e) {
		cout << "catched std::exception: " << e.what() << endl;
		cout << "Make default constructed std::nested_exception()\n";
		std::nested_exception ne1;
		if (ne1.nested_ptr()) {
			cout << "ne1.rethrow_nested()\n";
			try {
				ne1.rethrow_nested();
			}catch (std::exception const & e) {
				cout << "catched std::exception: " << e.what() << endl;
			}
		}
	}

	cout << "\nTo check whether an exception is with nested, catch std::nested_exception and re-throw.\n";

	try {
		throw std::runtime_error("error 1");
	} catch (std::exception const & e) {
		examinateCurrentException();
		try {
			std::throw_with_nested(std::runtime_error("error 2"));
		} catch (std::exception const & e) {
			examinateCurrentException();
			try {
				std::throw_with_nested(std::runtime_error("error 3"));
			} catch (std::exception const & e) {
				examinateCurrentException();
				printException(e);
			}
		}
	}

	cout << "\nEND" << endl;
	return 0;
}

void checkCurrentException(std::exception_ptr ep) {
	if (ep) {
		cout << "current_exception in ep\n";
	} else {
		cout << "current_exception is null\n";
	}
}

void isEqual(std::exception_ptr p1, std::exception_ptr p2) {
	if (p1 == p2) {
		cout << "equal\n";
	} else {
		cout << "not equal\n";
	}
	if (not p1) cout << "p1 is null\n";
	if (not p2) cout << "p2 is null\n";
}

void reThrowExceptionPointer(std::exception_ptr ep) {
	if (ep) {
		std::rethrow_exception(ep);
	}
}

void examinateCurrentException() {
	bool nested = false;
	try {
		throw;
	} catch (std::nested_exception const &) {
		nested = true;
	} catch (...) {
	}
	try {
		throw;
	} catch (std::exception const & e) {
		cout << "catched std::exception: " << e.what();
	} catch (...) {
		cerr << "unexpected exception!";
	}
	if (nested) {
		cout << " nested exception";
	}
	cout << endl;
}

void printException(std::exception const & e, int level) {
	std::cout << std::string(level, '\t') << "std::exception: " << e.what() << '\n';
	try {
		std::rethrow_if_nested(e);
	} catch(const std::exception& e) {
		printException(e, level+1);
	} catch(...) {
		cerr << "unexpected exception!";
	}
}
