/*
 * Module2.hpp
 */

#ifndef MODULE2_HPP_
#define MODULE2_HPP_

#include <iostream>

extern int i2;
extern int const ci2;

void bar();

inline void inlinefuc();

// Inline functions can not be linked !
// must be defined in header file
inline void inlinefuc() {
	std::cout << __func__ << "() Module1\n";
}

class MyClass {
public:
	int i;
	void foo() {
		std::cout << __func__ << "() i=" << i << std::endl;
	}
};

#endif /* MODULE2_HPP_ */
