//============================================================================
// Name        : Lambdas.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

int main() {
	cout << "!!!Hello Lambdas!!!" << endl;

	cout << "Labda expression components:\n"
			"	* Capture list: []\n"
			"	* Argument list (optional): ()\n"
			"	* specifiers (optional): mutable noexept\n"
			"	* Return type declaration (optional): -> Type\n"
			"	* Body: {}\n";
	string s1 = "String 1";
	const string s2 = "String 2 const";
	int counter = 0;

	auto l1 = [] (int x) { cout << "l1(" << x << ")\n"; };
	l1(1);

	auto l2 = [&counter] (int x) -> int {cout << "l2(" << x << ") counter=" << counter << endl; ++counter; return x + x; };
	cout << "l2(2)=" << l2(2) << endl;

	auto l3 = [&s2, &counter] (int x) -> int {cout << "l3(" << x << ") counter=" << counter << " s2= " << s2 << endl; ++counter; return x + x; };
	cout << "l3(3)=" << l3(3) << endl;

	cout << "no such thing is possible in capture list const&s2\n";
	cout << "weird error messages if an reference to a const value is in capture list ant attempt to change\n";
	//auto l4 = [&2, &counter] (int x) -> int {s2 = string("bla"); cout << "l4(" << x << ") counter=" << counter << " s2= " << s2 << endl; ++counter; return x + x; };
	//error: no match for ‘operator=’ (operand types are ‘const string {aka const std::basic_string<char>}’ and ‘std::string {aka std::basic_string<char>}’)

	cout << "You can change mutable values in captured content\n";
	auto l5 = [s1, &counter] (int x)  mutable -> int {s1.append(" has changed"); cout << "l5(" << x << ") counter=" << counter << " s1= " << s1 << endl; ++counter; return x + x; };
	cout << "l5(5)=" << l5(5) << "s1 is still the old value=" << s1 << endl;

	cout << "But you cannot change const values in captured content\n";
	//auto l6 = [s2, &counter] (int x)  mutable -> int {s2.append(" has changed"); cout << "l5(" << x << ") counter=" << counter << " s2= " << s2 << endl; ++counter; return x + x; };
	cout << "error: no matching function for call to ‘std::basic_string<char>::append(const char [13]) const\n";

	cout << "typeid l1 : " << typeid(l1).name() << endl;
	cout << "typeid l2 : " << typeid(l2).name() << endl;

	cout << "Assignement to function pointer possible if nothing is in capture list" << endl;
	auto lfp1 = [] (int x) -> double { int res = x + x; return double(res); };
	double (*fp1)(int) = lfp1;
	cout << "(*fp1)(4)=" << (*fp1)(4) << endl;
	cout << "typeid fp1 : " << typeid(fp1).name() << " typeid lfp1 : " << typeid(lfp1).name() << endl;

	cout << "END!" << endl;
	return 0;
}
