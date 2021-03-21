/*
 * module for external stored vars and functions
 */
#include <cstdio>

// Definitions of variables and function required in 'main.cpp'
// standard binding for variables in namespace/global scope is extern;
// extern storage class specifier is optional here
int i = 55;
// the type check over modules is not required to be checked from the tool chain
// so a definition like 'short i = 55;' is probably accepted but is incorrect.
// so use for real programs header files for type definitions and include header files
// where the variables, types, or templates are required.

// standard binding for consts is internal
// extern storage class specifier is required for constants
extern const int ci = 56;

// Rule 2: violation for an external object is dismissed from the linker - void bar() is defined in man.cpp
//void bar() { // multiple definition of `bar()'
//	printf("Hello %s", __func__);
//}

// Rule 2 : violation
// second definition but internal binding
// redefinition of internal/static values is not checked from linker
int const anotherConstant = 27;
int anotherInt; // definition !

// Rule 2 : violation second definition of bar() but with internal binding
static void bar() { // multiple definition of `bar()'
	printf("Hello %s number TWO\n", __func__);
}

// standard binding for functions is external
// extern is not required here
// a complete type check over modules is not required to be checked from the tool chain
// and most probably not provided from your linker
// thus something like
// int foo () {
// is probably possible (return value is not part of the function signature)
void foo() {
	printf("Hello extern.cpp %s\n", __func__);
	printf("extern.cpp - anotherConstant=%i\n", anotherConstant);
	bar();
	//return 0;
}
