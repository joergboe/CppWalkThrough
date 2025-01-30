/*
 * Include pre-processor directive
 */

/*
 * Use header files to represent interfaces and to emphasize logical structure.
 * Header files are included into the source files by means of the preprocessor 
 * directive #include.
 * The #include directive exists in two forms using the angle (<>) or quoted ("") syntax.*
 * 
 * Use the quoted form for including files that exist at a relative path to the file containing
 * the #include statement (from within the same component or project)
 * and to use the angle bracket form everywhere else.
 */
/* To include other headers of the same project use the quoted form of include:
 * #include "..."
 * The search for this files starts at a relative to the file containing the #include statement and
 * second in the library search path. To ensure that the project internal header
 * file is included, use the relative path from source-file to the header-file.
 */
#include "header2.h"
#include "../internals/header1.h"
/*
 * The compiler option -iquote provides a search path to only to the quote form of the #include directive.
 */
#include "header3.h"

/*
 * Since the path of the source file is part of the library search path, the angle syntax may also work,
 * but this may cause name clashes
 */
//#include <header2.h>

/*
 * to include c++ standard library headers use the include directive with the angle syntax:
 * #include <...>
 * These header files are searched in the library header search path. (compiler option -I)
 */
#include <string>

/*
 * Nevertheless the qoutes syntax will also work in the most cases.
 * But may be a source of confusion.
 */
//#include "string"

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

/* namespaces may be sliced */
namespace myns2 {
	void myfunction() {
		Named_point np;
		np.name = "Name1"; np.x = 1; np.y = 11;
		Typed_point tp;
		tp.type = "Type1"; tp.x = 100; tp.y = 110;
		/* here the using namespace myns1 directive is still effective!!!
		 * Point may be used without ns qualifier. */
		Point p;
		p.x = 5; p.y = -1;
		std::printf("Named point: name=%s, x=%d, y=%d\n", np.name.c_str(), np.x, np.y);
		std::printf("Typed point: type=%s, x=%d, y=%d\n", tp.type.c_str(), tp.x, tp.y);
		std::printf("Point: x=%d, y=%d\n", p.x, p.y);
	}
}

int main() {
	std::string hello{"Hello IncludeHeaders\n"};
	std::printf("%s", hello.c_str());
	printf("The inclusion of the c.. versions of the standard c library headers\n"
			"makes the header declarations available in global name-space and in name-space std\n");

	myns2::myfunction();
	std::printf("END");
	return EXIT_SUCCESS;
}
