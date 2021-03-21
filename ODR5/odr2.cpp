#include <iostream>

/*
 * the following definitions violate rule 5:
 * Multiple definitions of class types, enum and templates are allowed in several
 * translation units, however the definition must be the equal:
 * .. each definition consists of the same sequence of tokens (typically, appears in the same header file)
 * These definitions violates this rule but the violation is probably not prevented from compiler and linker
 */

/* Class definitions */
struct C1 {
	void foo() {
		std::cout << "C1::foo() TWO\n";
	}
};

struct C2 {
	void foo();
};
// for definitions of methods outside of the class body rule 1 applies
//void C2::foo() { // multiple definition of `C2::foo()'
//	std::cout << "C2::foo() TWO\n";
//}

/* Enum definitions */
enum E1 : char { A, B, C };
enum class E2 : char { SCOPE_A, SCOPE_B, SCOPE_C };
template<typename T>
void foo(T inp) {
	std::cout << "foo(" << inp << ") TWO" << std::endl;
}

/*
 * as exception from rule 1 definition of constants is allowed in more than one translation unit
 * however the definitions must be the equal!
 * This definition violates this rule but the violation is probably not prevented from compiler and linker
 */
int const ci = 57;

void modulfunction2() {
	std::cout << "modulfunction2\n";
	C1 c1;
	c1.foo();
	C2 c2;
	c2.foo();
	E1 e1 = C;
	E2 e2 = E2::SCOPE_C;
	std::cout << "size e1 " << sizeof e1 << " value " << e1 << std::endl;
	std::cout << "size e2 " << sizeof e2 << " value " << static_cast<int>(e2) << std::endl;
	foo(11);
	std::cout << "ci " << ci << std::endl;
}
