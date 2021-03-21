#include <iostream>

// Definitions of these objects are
struct C1 {
	void foo() {
		std::cout << "C1::foo() ONE\n";
	}
};

struct C2 {
	void foo();
};
void C2::foo() {
	std::cout << "C2::foo() ONE\n";
}

enum E1 : int { ONE, TWO, THREE };
enum class E2 : int { SCOPE_ONE, SCOPE_TWO, SCOPE_THREE };
template<typename T>
void foo(T inp) {
	std::cout << "foo(" << inp << ") ONE" << std::endl;
}

// as exception from rule 1 definition of constants is allowed in more than one translation unit
int const ci = 55;

void modulfunction1() {
	std::cout << "modulfunction1\n";
	C1 c1;
	c1.foo();
	C2 c2;
	c2.foo();
	E1 e1 = TWO;
	E2 e2 = E2::SCOPE_TWO;
	std::cout << "size e1 " << sizeof e1 << " value " << e1 << std::endl;
	std::cout << "size e2 " << sizeof e2 << " value " << static_cast<int>(e2) << std::endl;
	foo(11);
	std::cout << "ci " << ci << std::endl;
}
