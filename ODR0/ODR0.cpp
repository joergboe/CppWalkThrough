/*
 * When must symbols be defined
 * When must symbols be declared
 */

#include <iostream>
#include <cstdlib>

using namespace std;

// declarations
extern int ig1; // extern makes the definition
extern int const ic1;
void foo();
static void foo_static();

// inline functions must be defined ??
inline void inline_func() {
	cout << "Hello " << __func__ << endl;
}

// opaque definitions of enums
enum E1 : int;
enum class E2;

// template declaration
template<typename T>
void templ_foo(T inp);

// class declaration
class C1;

// class types must be defined before usage
struct S1 {
	void foo();
	virtual void foo_virt();
	virtual ~S1() = default;
};

template<typename T>
class C2;

template<typename T>
struct S2 {
	void foo(T inp);
};

int main(int argc, char **argv) {
	cout << "Hello ODR0!\n" << endl;
	// Every used identifier must be at least declared
	//undeclared_fiunction(); // error: ‘undeclared_fiunction’ was not declared in this scope

	// local variables must be defined before use (there is no way to declare a local var)
	int il; // definition but not initialized! not do this.
	cout << "il=" << il << endl;

	// to use a global variable, it must be declared, declaration may be n scope
	extern int ig2;
	extern int const ic2;
	cout << "ig1=" << ig1 << " ig2=" << ig2 << " ic1=" << ic1 << " ic2=" << ic2 << endl;

	// to use a function, it must be declared
	foo();
	foo_static();
	void bar(); // declaration may be in scope
	bar();
	inline_func();

	// variables of defined enums can be used
	E1 e1;
	E2 e2;
	// but can not do much with this variables
	//e1 = TWO; // error: ‘TWO’ was not declared in this scope
	//e2 = E2::SCOPED_TWO; // 11: error: ‘SCOPED_TWO’ is not a member of ‘E2’

	// use a defined template
	templ_foo(11);

	// Can not do much with a declared class
	//C1 c1; //  error: aggregate ‘C1 c1’ has incomplete type and cannot be defined
	C1 * c1p = nullptr;
	cout << "c1p=" << c1p << endl;

	// Usage of a defined class/struct
	S1 s1;
	s1.foo();
	S1 * s1p = &s1;
	s1p->foo_virt();

	// Can not do much with a declared class template
	//C2<int> c2; //error: aggregate ‘C2<int> c2’ has incomplete type and cannot be defined
	C2<int> *c2p = nullptr;
	cout << "c2p=" << c2p << endl;

	// use a defined template class
	S2<char> s2;
	s2.foo('a');

	cout << "END\n";
	return EXIT_SUCCESS;
}

// Used objects must be defined somewhere in the program
int ig1 = 55;
int ig2 = 56;
int const ic1 = 11;
extern int const ic2 = 12;

void foo() {
	cout << "Hello " << __func__ << endl;
}

void foo_static() {
	cout << "Hello " << __func__ << endl;
}

void bar() {
	cout << "Hello " << __func__ << endl;
}

enum E1 : int { ONE, TWO, THREE };
enum class E2 : int { SCOPED_ONE, SCOPED_TWO, SCOPED_THREE };

template<typename T>
void templ_foo(T inp) {
	cout << "Hello " << __func__<< " inp=" << inp << endl;
}

// method definition may follow later
void S1::foo() {
	cout << "Hello " << __func__<< endl;
}

void S1::foo_virt() {
	cout << "Hello " << __func__<< endl;
}

// same for class templates
template<typename T>
void S2<T>::foo(T inp) {
	cout << "Hello " << __func__ << " inp=" << inp << endl;
}
