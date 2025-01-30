/* header2.hpp */

/* use include guards to avoid re-definitions and to speed up the compilation */
#ifndef SRC_HEADER2_H_
#define SRC_HEADER2_H_

#include "../internals/header1.h"
#include <string>

/* Avoid global using in header files to prevent name-space pollution.
 * Using directive in header files can cause name clashes in other files. */
//using namespace myns1;

namespace myns2 {
	/* Also avoid name-space scoped using declarations in header files!
	 * This dircetive is effective also in other slices of the name-space
	 * also in other files! */
	using namespace myns1;
	struct Named_point : Point {
		std::string name;
		Named_point() :name() {}
	};
}

#endif /* SRC_HEADER2_H_ */
