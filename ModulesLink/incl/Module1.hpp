/*
 * Modul1.hpp
 *
 *  Created on: Feb 26, 2021
 *      Author: joergboe
 */

#ifndef MODUL1_HPP_
#define MODUL1_HPP_

#include <iostream>

// Only one definition per compilation unit
extern int i; // no definition
extern int const ic; // no definition

void foo() {
	std::cout << "foo()\n";
	std::cout << "i=" << i << " ic=" << ic << std::endl;
}

#endif /* MODUL1_HPP_ */
