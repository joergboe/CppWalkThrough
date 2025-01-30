/* header3.h */

#ifndef INCLUDE_HEADER3_H_
#define INCLUDE_HEADER3_H_

#include "../internals/header1.h"
#include <string>

namespace myns2 {
	// here Point must be used fully qualified.
	struct Typed_point : myns1::Point {
		std::string type;
		Typed_point() : type() {}
	};
}

#endif /* INCLUDE_HEADER3_H_ */
