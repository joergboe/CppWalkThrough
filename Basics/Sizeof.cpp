/*
 * Demonstrating the basic principles of sizeof operator in c++
 */

#include <iostream>
using namespace std;

template<typename ...Ts>
void f1(Ts...);

int main() {
	cout << "Sizeof Operator\n\n"
			"sizeof is an operator but when used with types braces are required. "
			"This is to avoid ambiguity.\n\n"
			"sizeof unary-expression\n"
			"sizeof ( type-name )\n\n";
	int i = 55;
	char c = 'a';
	cout << "sizeof i is: " << sizeof i << endl;
	cout << "sizeof c is: " << sizeof c << endl;
	cout << "sizeof(int) is: " << sizeof(int) << endl;
	cout << "sizeof(int*) is: " << sizeof(int*) << endl;
	cout << "sizeof i * 4 is: " << sizeof i * 4 << endl;
	cout << "sizeof(int) * 4 is: " << sizeof(int) * 4 << endl;
	cout << "sizeof(int*) * +4 is: " << sizeof(int*) * +4 << endl;
	cout << "if there were no bracket, this expression would be ambiguous\n"
			"sizeof int * +4 ---- is it sizeof (int *) +4 or sizeof (int) * +4  ?\n"
			"This ambiguity doesn't arise for unary expressions, as an asterisk appended to an expression isn't an expression (but for some type names, appending one, is again a type name).\n" << endl;

	cout << "There is no easy way to get the size of an reference.\n"
			"In an expression, the reference is silently converted to the value as usual in C++." << endl;
	cout << "sizeof r gives mainly the size of the thing where it points to" << endl;
	int & r = i;
	cout << "sizeof r is: " << sizeof r << endl;
	cout << "sizeof &r is: " << sizeof &r << " is the size of the address to i" << endl;
	cout << "sizeof(int &) is: " << sizeof(int&) << endl;
	cout << "Hack!" << endl;
	struct refstruct { int & r; };
	cout << "sizeof refstruct is: " << sizeof(refstruct) << endl;

	cout << "\nArrays" << endl;
	char ca[] = "abcd";
	cout << "sizeof ca is: " << sizeof ca << endl;
	const char * cp = &ca[0];
	cout << "sizeof cp is: " << sizeof cp << endl;
	cout << "sizeof *cp is: " << sizeof *cp << endl;

	cout << "Array reference:" << endl;
	char (&ra)[sizeof ca] = ca;
	cout << "sizeof ra is: " << sizeof ra << endl;

	for (auto x : ca)
		cout << x << endl;

	cout << "\nsizeof...( parameter_pack )		(since C++11)\n"
			"returns the number of parameters in a parameter pack.\n";
	f1(1);
	f1(2,'a',22.3,&cout);
	f1();

	cout << "End!" << endl;
	return 0;
}

template<typename ...Ts>
void f1(Ts... ) {
	int s = sizeof...(Ts);
	cout << "f1: has " << s << " arguments\n";
}
