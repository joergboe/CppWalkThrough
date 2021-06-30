/*
 * header2.hpp
 */

/* use include guards to avoid re-definitions and to speed up the compilation */
#ifndef HEADER2_HPP_
#define HEADER2_HPP_

#include "../incl/header1.hpp"

/* Avoid global using in header files to prevent name-space pollution.
 * Using directive in header files can cause name clashes in other files. */
//using namespace myns1;

namespace myns2 {
	/* Also avoid name-space scoped using declarations
	 * this is effective also in other slices of the name-space. */
	using namespace myns1;
	char const identifier1[] = "myns2::identifier1 from header2.hpp";

	char const * getIdentFromHeader1() {
		return identifier1; //myns1::identifier1 takes precedence
	}
	char const * getIdent2FromHeader1() {
		return identifier2;
	}
}

#endif /* HEADER2_HPP_ */
