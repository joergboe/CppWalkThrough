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
 * .....
 *
 */

#include <cstdlib>
#include <cstdio>
#include <typeinfo>

/*
 * Rule 1 one definition in any translation unit
 */

/*** Definitions ***/
int def_int; // definition - initialized with 0
const int def_cint = 55; // definition

void def_f() { // definition
	printf("def_f(): Hello!\n");
}

enum Def_enum {read, yellow, green}; // enum type definition

class Def_class { // class type definition
public:
	// in class definitions a members may be used before it appear in class definition!
	void f() { printf("Def_class::f Hello! My member x=%i\n", x); }
private:
	int x;
};

template<typename T>
void def_templ_f(T x) {
	printf("def_templ_f(T x): type of x: %s\n", typeid(x).name());
}

/*** Declarations ***/
extern int decl_int; // declaration
extern const int decl_cint; // declaration

void decl_f(); // declaration - not a definition

enum Decl_enum : int; // Opaque enum declaration - size is now known

struct Decl_class; // declaration of struct/class type

template<int I>
void decl_templ_f();

// Use the declared types in other declarations
Decl_enum fenum(int);

/*** main ***/
int main(int argc, char **argv) {

	// every variable, function, type or template must be at least declared before it can be used
	//printf("Values of undeclared=%i\n", undeclared); // error: ‘undeclared’ was not declared in this scope

	printf("Values of defined variables: def_int=%i def_cint=%i\n", def_int, def_cint);
	def_f();
	int localvar; // variable is defined - memory is allocated but is not initialized!
	Def_enum e1 = yellow;
	printf("e1=%i localvar=%i\n", e1, localvar);
	//Def_enum e1; // error: redeclaration of ‘Def_enum e1’
	//int localvar; // error: redeclaration of ‘int localvar’
	Def_class c1;
	c1.f();
	def_templ_f(c1);

	printf("Values of declared variables: decl_int=%i decl_cint=%i\n", decl_int, decl_cint);
	decl_f();
	void decl_f2(); // declarations may be in scope!
	decl_f2();

	// but can not do much with not completely defined types
	// Decl_enum e2 = b; // error: ‘b’ was not declared in this scope
	// Decl_class c2; //  error: aggregate ‘Decl_class c2’ has incomplete type and cannot be defined
	Decl_enum e2 = fenum(1); // size is known - can allocate memory
	printf("Value of e2=%i\n", e2);

	void do_something_with_Decl_class();
	do_something_with_Decl_class();

	decl_templ_f<5>();

	return EXIT_SUCCESS;
}

/*** late declaration ***/
// declaration and definition of this variable is to late for usage in main
int undeclared = 11;

/*** definition of declared entities ***/
// the definition of an extern var may be given later!
// but avoid this is non intentional use!
const int decl_cint = 56;

void decl_f() { // definition
	printf("decl_f(): Hello!\n");
}

void decl_f2() { // definition
	printf("decl_f2(): Hello!\n");
}

enum Decl_enum : int {a, b, c};

Decl_enum fenum(int inp) {
	return Decl_enum(inp);
}

class Decl_class : public Def_class {
};

void do_something_with_Decl_class() {
	printf("sizeof(Decl_class)=%i\n", sizeof(Decl_class));
}

template<int I>
void decl_templ_f() {
	printf("decl_templ_f(): template param is : %i\n", I);
}

/*** redefinitions ***/
// int def_int; // error: redefinition of ‘int def_int’

//void def_f() { // redefinition of ‘void def_f()’
//}

//enum Def_enum {read, yellow, green}; // error: multiple definition of ‘enum Def_enum’

//class Def_class { // error: redefinition of ‘class Def_class’
//};

//template<typename T> //error: redefinition of ‘template<class T> void def_templ_f(T)’
//void def_templ_f(T x) {
//	printf("type : %s\n", typeid(x).name());
//}
