//============================================================================
// Name        : ModulesLink.cpp
// Author      : jb
// Version     :
//============================================================================

/*
 * Name        : ModulesLink.cpp
 * Author      : jb
 *
 * Considerations to the One Definition Rule (ODR)
 *
 * In general, a translation unit shall contain no more than one definition of any type.
 *
 * Multiple declarations are allowed, but only one definition is allowed.
 *
 */


#include <cstdlib>
#include <iostream>

#include "../incl/Module1.hpp"
#include "../incl/Module2.hpp"
#include "../incl/Module3.hpp"

using namespace std;

int i; // definition initialized with 0!
int const ic = 7; // definition

// Only one definition per compilation unit
void foo(); //No definition
void foo(); //Multiple equal declarations are valid

void redeclaredFunction() {
	cout << __func__ << endl;
}

void redeclaredFunction(); // repeated declaration is possible but no re-definition

int main() {
	//int x; // error: redeclaration of ‘int x’
	cout << "!!!Hello World!!!" << endl;
	int x = 5;
	foo();
	cout << "x=" << x << endl;

	cout << "i2=" << i2 << " ci2=" << ci2 << endl;
	bar();
	inlinefuc();
	redeclaredFunction();
	MyClass mc;
	mc.foo();
	return EXIT_SUCCESS;
}
