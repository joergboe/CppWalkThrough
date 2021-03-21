/*
 * 2)
 * One and only one definition of every non-inline function or variable that is odr-used (see below)
 * is required to appear in the entire program (including any standard and user-defined libraries).
 * The compiler is not required to diagnose this violation, but the behavior of the program
 * that violates it is undefined.
 *
 */

#include <cstdlib>
#include <cstdio>

// declaration of values which are defined in another translation unit with keyword 'extern'
extern int i;
extern const int ci;

// function declaration - definition in module externals
// extern is redundant but sometimes considered good style.
extern void foo();

// definition of an function (default storage class: extern)
void bar() {
	printf("Hello %s\n", __func__);
}

// Rule 2 : violation but may be accepted with internal binding
const int anotherConstant = 10000;
// Rule 2 : violation with external binding provokes likage error
// int anotherInt; // multiple definition of `anotherInt'

int main(int argc, char **argv) {
	printf ("Hello ODR2\n");
	printf ("i=%i ci=%i\n", i, ci);
	foo();
	bar();
	printf("main - anotherConstant=%i", anotherConstant);
	return 0;
}
