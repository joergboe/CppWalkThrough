//============================================================================
// Name        : FunctionPointers.cpp
// Author      : joergboe
//============================================================================

#include <iostream>
#include <exception>
#include <typeinfo>

using namespace std;

int f1(int inp);
int f1ne(int inp) noexcept;
int * f2(int inp);
int const * f3(int inp);
int & f4(int inp);
int const & f5(int inp);

int resf2, resf3, resf4, resf5;


int main() {
	cout << "Hello FunctionPointers" << endl;
	cout << "define a function pointer to a function and use it\n";
	int (* fp1)(int) = &f1;
	int res = (*fp1)(4);
	cout << "(*fp1)(4) = " << res << endl;
	cout << "The & to obtain the address of the function is optional and the * to the execute function is optional\n";
	fp1 = f1;
	cout << "fp1(4) = " << fp1(4) << endl;
	cout << "The function assigned to the pointer must have the same number and type of parameters and return type\n";
	cout << "noexcept specification is part of the function type. A normal pointer may point to a noexcept funtion\n";
	int (* fp1ne)(int) noexcept = &f1ne;
	res = (*fp1ne)(4);
	cout << "res=" << res << endl;
	cout << "A noexcept pointer must not point to a normal function (which may throw an execpion)\n";
	fp1ne = &f1;
	cout << "This may be a problem with (GCC) 4.8.5\n";
	res = (*fp1ne)(4);
	cout << "res=" << res << endl;

	//fp1 = &f2; //error: invalid conversion from ‘int* (*)(int)’ to ‘int (*)(int)’ [-fpermissive]
	//fp1 = &f3; //dito error
	//fp1 = &f4; //dito error
	//fp1 = &f5; //dito error

	cout << "Define and use a constant function pointer\n";
	int (* const fp2)(int) = &f1;
	res = (*fp2)(5);
	cout << "res=" << res << endl;
	//fp2 = &f1; //error: assignment of read-only variable ‘fp2’

	cout << "Define and use a constant function pointer with return type pointer to constant value\n";
	int const * (* const fp3const)(int) = &f3;
	int const * const res3px = (*fp3const)(4);
	cout << "*res3px=" << *res3px << endl;

	cout << "Define and use a constant function pointer with return type constant reference and use type alias\n";
	int const & (*fp5)(int inp) = &f5;
	cout << "resfp5=" << (*fp5)(4) << endl;

	cout << "Use type alias for function pointer old stype\n";
	typedef int (*Palias1)(int);
	Palias1 pa1 = &f1;
	cout << "(*pa1)(2)=" << (*pa1)(2) << endl;

	cout << "Use type alias for function type old stype and use it as pointer\n";
	typedef int Alias1(int);
	Alias1 * pa2 = &f1;
	cout << "(*pa2)(2)=" << (*pa2)(2) << endl;

	cout << "Use type alias for function pointer new stype\n";
	using Palias2 = int(*)(int);
	Palias2 pa3 = f1;
	cout << "pa3(3)=" << pa3(3) << endl;

	cout << "Use type alias for function type and use it as pointer new stype\n";
	using Alias2 = int (int);
	Alias2 * pa4 = f1;
	cout << "pa4(3)=" << pa4(3) << endl;

	cout << "Exception specification should not be part of the alias. Problem with (GCC) 4.8.5\n";
	using Alias3 = int(*)(int) noexcept;
	cout << "This assignement shjould not be possible. Problem with (GCC) 4.8.5\n";
	Alias3 pa5 = &f1;
	cout << "(*pa5)(3)=" << (*pa5)(3) << endl;

	cout << "typeinfo fp1     : " << typeid(fp1).name() << endl;
	cout << "typeinfo fp1ne   : " << typeid(fp1ne).name() << endl;
	cout << "typeinfo fp2     : " << typeid(fp2).name() << endl;
	cout << "typeinfo fp3const: " << typeid(fp3const).name() << endl;
	cout << "typeinfo fp5     : " << typeid(fp5).name() << endl;
	cout << "typeinfo Palias1 : " << typeid(Palias1).name() << endl;
	cout << "typeinfo Palias2 : " << typeid(Palias2).name() << endl;
	cout << "typeinfo Alias1  : " << typeid(Alias1).name() << endl;
	cout << "typeinfo Alias2  : " << typeid(Alias2).name() << endl;

	cout << "END" << endl;
	return 0;
}

int f1(int inp) {
	int res = inp + inp + 1;
	if (res > 15) throw exception();
	return res;
}
int f1ne(int inp) noexcept {
	return inp + inp + 1;
}
int * f2(int inp) {
	resf2 = inp + inp + 2;
	return &resf2;
}
int const * f3(int inp) {
	resf3 = inp + inp + 3;
	return &resf3;
}
int & f4(int inp) {
	resf4 = inp + inp + 4;
	return resf4;
}
int const & f5(int inp) {
	resf5 = inp + inp + 5;
	return resf5;
}
