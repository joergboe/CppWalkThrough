/*
 * ODR - one definition rule
 *
 * source https://en.cppreference.com/w/cpp/language/definition
 *
 * 3)
 * For an inline function or inline variable (since C++17), a definition is required
 * in every translation unit where it is odr-used.
 *
 */

#include <cstdlib>
#include <iostream>

using namespace std;

inline void foo() {
	cout << "foo(): Hello!\n";
}

// declaration of bar is not sufficient
extern inline void bar();
// extern makes no sense for inline functions

inline void bar() { // definition is required
	std::cout << "bar(): Hello!\n";
}

extern void ext_funct();

int main() {
	cout << "Hello ODR3\n"
			"One definition of an inline functions is required in every translation unit!" << endl;
	foo();
	bar();
	ext_funct();
	cout << "END" << endl;
	return EXIT_SUCCESS;
}

// only one definition permitted
//inline void foo() { // error: redefinition of ‘void foo()’
//	cout << "foo(): Hello!\n";
//}
