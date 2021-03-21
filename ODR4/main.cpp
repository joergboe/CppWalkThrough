#include <cstdlib>
#include <iostream>

class C1 { // definition
};

class C2; // declaration

int main(int argc, char **argv) {
	std::cout << "ODR4\n"
			"One and only one definition of a class is required to appear "
			"in any translation unit where the class is used in a way that "
			"requires it to be complete.\n";

	C1 c1; // definition of a class variable requires the type C1 to be complete
	// C2 c2; // error: aggregate ‘C2 c2’ has incomplete type and cannot be defined

	C2 * c2p; // the definition of a pointer type is possible with an incomplete type

	std::cout << "size c1: " << sizeof c1 << " size c2p: " << sizeof c2p << std::endl;
	return EXIT_SUCCESS;
}
