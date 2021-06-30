/*
 * Include pre-processor directive
 */

/*
 * to include c++ standard library headers use #include <...>
 * These header files are searched in the library header search path.
 */
#include <string> // std::string ...
//#include "string" // also works also

/*
 * For every c-library header X.h a c++ header cX is available.
 * These the headers make c-header declarations available in name-space std
 * and due to compatibility reasons often also in global name-space.
 * Some examples:
 * cassert, cctype, cerrno, cfloat, climits, cmath, cstdarg, cstdint, cstddef, cstdio,
 * cstring, ctime, cuchar, cwchar
 *
 * In c++ programs the c-headers (stdio.h, ...) should not be used.
 */
#include <cstdlib>
#include <cstdio>

/* To include other headers of the same project use the form
 * #include "..."
 * The search for this files starts in the source directory and
 * second in the library search path. To ensure that the project internal header
 * file is included, use the full path to the header.
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
		std::printf("Access from myns2 with using myns1 declaration identifier1: %s\n", identifier1);
		//the using declaration in in myns2 is effective !
		std::printf("Access from myns2 with using myns1 declaration identifier2: %s\n", identifier2);
	}
}

int main() {
	std::printf("Hello IncludeHeaders\n");
	printf("The inclusion of the c.. versions of the standard c library headers\n"
			"makes the header declarations available in global name-space and in name-space std\n");

	std::printf("Full qualified access myns1::identifier1 %s\n", myns1::identifier1);
	std::printf("Full qualified access myns2::identifier1 %s\n", myns2::identifier1);
	std::printf("Access from myns2 with using myns1 declaration getIdentFromHeader1(): %s\n", myns2::getIdentFromHeader1());
	std::printf("Access from myns2 with using myns1 declaration getIdent2FromHeader1(): %s\n", myns2::getIdent2FromHeader1());
	myns2::myfunction();
	std::printf("END");
	return EXIT_SUCCESS;
}
