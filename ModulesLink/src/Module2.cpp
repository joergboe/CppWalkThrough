/*
 * Module2.cpp
 */

#include "../incl/Module2.hpp"

int i2 = 20;
int const ci2 = 27;

void bar() {
	std::cout << "bar() Module2\n";
}

// Inline functions can not be linked !
// undefined reference to `inlinefuc()'
/* inline void inlinefuc() {
	std::cout << "inlinefuc()\n";
} */

// fo is already defined
//void MyClass::foo() { // error: redefinition of ‘void MyClass::foo()’
//	std::cout << __func__ << std::endl;
//}
