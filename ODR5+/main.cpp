/*
 * ODR - one definition rule
 * show an specific failure scenario
 *
 */

#include <cstdlib>
#include <cstdio>

#include "odr.h"

using namespace std;

int main(int argc, char **argv) {
	printf("Hello ODR5\n");

	Base *o1 = create_derived1();
	Base *o2 = create_derived2();

	// expected output
	// foo() ONE: Hello
	// foo() TWO: World
	o1->foo();
	o2->foo();

	delete o1;
	delete o2;

	printf("END\n");
	return EXIT_SUCCESS;
}
