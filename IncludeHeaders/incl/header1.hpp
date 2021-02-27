/*
 * header1.hpp
 *
 *  Created on: Feb 27, 2021
 *      Author: joergboe
 */

#ifndef INCL_HEADER1_HPP_
#define INCL_HEADER1_HPP_

namespace myns1 {
	char const identifier1[] = "Identifier1 from header1.hpp";
	char const identifier2[] = "Identifier2 from header1.hpp";
}

/* avoid using in header files to prevent name-space pollution */
//using namespace myns1;

#endif /* INCL_HEADER1_HPP_ */
