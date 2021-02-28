/*
 * Module3.hpp
 */

#ifndef MODULE3_HPP_
#define MODULE3_HPP_

#include <iostream>

extern int i2;
extern int const ci2;

void bar();

// Inline functions can not be linked !
// undefined reference to `inlinefuc()'

// also inline functions must not be defined twice!
//inline void inlinefuc() { //error: redefinition of ‘void inlinefuc()’
//	std::cout << "inlinefuc()\n";
//}

#endif /* MODULE3_HPP_ */
