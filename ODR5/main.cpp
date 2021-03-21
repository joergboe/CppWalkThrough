/*
 * ODR - one definition rule
 *
 * source https://en.cppreference.com/w/cpp/language/definition
 *
 * 1)
 * Only one definition of any variable, function, class type, enumeration type,
 * concept (since C++20) or template is allowed in any one translation unit
 * (some of these may have multiple declarations, but only one definition is allowed).
 *
 * 2)
 * One and only one definition of every non-inline function or variable that is odr-used (see below)
 * is required to appear in the entire program (including any standard and user-defined libraries).
 * The compiler is not required to diagnose this violation, but the behavior of the program
 * that violates it is undefined.
 *
 * 3)
 * For an inline function or inline variable (since C++17), a definition is required
 * in every translation unit where it is odr-used.
 *
 * 4)
 * One and only one definition of a class is required to appear in any translation unit
 * where the class is used in a way that requires it to be complete.
 *
 * 5)
 * There can be more than one definition in a program of each of the following:
 * class type, enumeration type, inline function, inline variable (since C++17),
 * templated entity (template or member of template, but not full template specialization),
 * as long as all of the following is true:
 *     * each definition appears in a different translation unit
 *     * the definitions are not attached to a named module (since C++20)
 *     * each definition consists of the same sequence of tokens (typically, appears in the same header file)
 *     * name lookup from within each definition finds the same entities (after overload-resolution), except that
 *         - constants with internal or no linkage may refer to different objects as long as they are not ODR-used and have the same values in every definition
 *     * lambda-expressions that are not in a default argument or a default template argument (since C++20) are uniquely identified by the sequence of tokens used to define them (since C++11)
 *     * overloaded operators, including conversion, allocation, and deallocation functions refer to the same function from each definition (unless referring to one defined within the definition)
 *     * the language linkage is the same (e.g. the include file isn't inside an extern "C" block)
 *     * the three rules above apply to every default argument used in each definition
 *     * if the definition is for a class with an implicitly-declared constructor, every translation unit where it is odr-used must call the same constructor for the base and members
 *     * if the definition is for a class with a defaulted three-way comparison, every translation unit where it is odr-used must call the same comparison operator for the base and members (since C++20)
 *     * if the definition is for a template, then all these requirements apply to both names at the point of definition and dependent names at the point of instantiation
 *
 * If all these requirements are satisfied, the program behaves as if there is only one
 * definition in the entire program. Otherwise, the program is ill-formed, no diagnostic required.
 */

#include <cstdlib>
#include <cstdio>

using namespace std;

// Definitions of these objects are
class C1;
class C2;
enum E1 : int; // opaque declaration of unscoped enum requires underlying type but does not define E1 (since c++11)
enum class E2; // default underlying type of scoped enum is int
template<typename T>
void foo(T inp);

// Used functions from odr1.cpp and odr2.cpp
void modulfunction1();
void modulfunction2();

// defined vars
E1 e1;
E2 e2;

int main(int argc, char **argv) {
	printf("Hello ODR5\n");

	printf("size e1 %i value %i\n", sizeof e1, e1);
	printf("size e2 %i value %i\n", sizeof e2, e2); // seems that printf does not require the cast to int !?

	modulfunction1();
	modulfunction2();

	printf("END\n");
	return EXIT_SUCCESS;
}
