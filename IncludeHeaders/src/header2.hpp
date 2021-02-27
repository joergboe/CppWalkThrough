/*
 * header2.hpp
 */

/* use include guards to avoid re-definitions and to speed up the compilation */
#ifndef HEADER2_HPP_
#define HEADER2_HPP_

#include "../incl/header1.hpp"

/* avoid global using in header files to prevent name-space pollution */
//using namespace myns2;

namespace myns2 {
	/*
	 * avoid also name-space scoped using declarations
	 * this is effective also in other slices of the name-space
	 */
	using namespace myns1;
	char const identifier1[] = "Identifier from header2.hpp";

	char const * getIdentFromHeader1() {
		return identifier1; //myns1::identifier1 takes precedence
	}
	char const * getIdent2FromHeader1() {
		return identifier2;
	}
}

#endif /* HEADER2_HPP_ */
