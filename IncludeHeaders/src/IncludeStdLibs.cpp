/*
 * Name        : IncludeStdLibs.cpp
 * Author      : jb
 * Version     :
 * Copyright   : Your copyright notice
 * Include pre-processor directive
 */

/*
 * to include c++ standard library headers use #include <...>
 * These header files are searched in the library header search path.
 */
#include <string> // std::string ...
//#include "string" // also works also

/*
 * for every c-library header X.h a c++ header cX is available.
 * These the headers make c-header declarations available in name-space std
 * and due to compatibility reasons often also in global name-space.
 * Some examples:
 * cassert, cctype, cerrno, cfloat, climits, cmath, cstdarg, cstdint, cstddef, cstdio,
 * cstring, ctime, cuchar, cwchar
 *
 * In c++ programs the c-heasers (stdio.h, ...) should not be used.
 */
#include <cstdio>

/* to include other headers of the same project use the form
 * #include "..."
 * The search for this files starts in the source directory and
 * second in the library search path
 */
#include "header2.hpp"
#include "../incl/header1.hpp"

/*
 * this works only if the source directory was added to library search path
 * but this may cause name clashes
 */
//#include <header2.hpp>

/* namespaces may be sliced */
namespace myns2 {
	void myfunction() {
		std::printf("Identifier1 from myns1: %s\n", identifier1);
		//the using declaration in in myns2 is effective !
		std::printf("Identifier2 from myns1: %s\n", identifier2);
	}
}

int main() {
	std::printf("Hello IncludeStdLibs");
	printf("The inclusion of the c.. versions of the standard c library headers\n"
			"makes the header declarations available in global name-space and in name-space std\n");

	std::printf("Identifier1 from myns1: %s\n", myns1::identifier1);
	std::printf("Identifier1 from myns2: %s\n", myns2::identifier1);
	std::printf("Identifier1 from myns2 getIdentFromHeader1(): %s\n", myns2::getIdentFromHeader1());
	std::printf("Identifier2 from myns1 getIdent2FromHeader1(): %s\n", myns2::getIdent2FromHeader1());
	myns2::myfunction();
	std::printf("END");
	return 0;
}
