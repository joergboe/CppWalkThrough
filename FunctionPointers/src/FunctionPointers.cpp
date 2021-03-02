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

int (*retFpt())(int); // function that retruns a function pointer to int (*)(int)

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
	cout << "noexcept specification is part of the function type.\n"
			"A normal function pointer may point to a noexcept function\n";
	int (* fp1ne)(int) noexcept = &f1ne;
	res = (*fp1ne)(4);
	cout << "res=" << res << endl;
	cout << "But a noexcept pointer must not point to a normal function (which may throw an execpion)\n";
	fp1ne = &f1;
	cout << "This may be a problem with (GCC) 4.8.5\n"
			"The program may be terminated even if an exception handler is there! (due to violation of the nothrow promise)\n";
	try {
		res = (*fp1ne)(4);
		cout << "res=" << res << endl;
	} catch (exception const & e) {
		cout << "exception caught: " << e.what() << endl;
	}

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

	cout << "Use type alias for function pointer old style\n";
	typedef int (*Palias1)(int);
	Palias1 pa1 = &f1;
	cout << "(*pa1)(2)=" << (*pa1)(2) << endl;

	cout << "Use type alias for function type old style and use it as pointer\n";
	typedef int Alias1(int);
	Alias1 * pa2 = &f1;
	cout << "(*pa2)(2)=" << (*pa2)(2) << endl;

	cout << "Use type alias for function pointer new style\n";
	using Palias2 = int(*)(int);
	Palias2 pa3 = f1;
	cout << "pa3(3)=" << pa3(3) << endl;

	cout << "Use type alias for function type and use it as pointer new style\n";
	using Alias2 = int (int);
	Alias2 * pa4 = f1;
	cout << "pa4(3)=" << pa4(3) << endl;

	cout << "Exception specification should not be part of the alias. Problem with (GCC) 4.8.5\n";
	using Alias3 = int(*)(int) noexcept;
	cout << "This assignment should not be possible. Problem with (GCC) 4.8.5\n";
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
	cout << "typeinfo Alias3  : " << typeid(Alias3).name() << endl;

	cout << "\nUse a function that returns a function pointer\n";
	int resx = retFpt()(2);
	cout << "resx: " << resx << endl;
	cout << "typeinfo: " << typeid(retFpt).name() << endl;

	//Alias1 * (*ptrRetFpt)() = retFpt;
	Palias2 (*ptrRetFpt)() = retFpt;
	int resy = (*ptrRetFpt)()(4);
	cout << "resy: " << resy << endl;

	cout << "\nFunction pointers of same type can be compared:\n";
	if (fp1 == pa1) {
		cout << "Equal function pointers point to the same function.\n"
				"(*fp1)(7)=" << (*fp1)(7) << endl <<
				"(*pa1)(7)=" << (*pa1)(7) << endl;
	}
	cout << "Distinct pointer types without a cast can not be compared.\n";
	//if (fp1 == fp3const); //error: comparison between distinct pointer types ‘int (*)(int)’ and ‘const int* (*)(int)’ lacks a cast [-fpermissive]
	cout << "Top level cv-qualifiers are implicitly converted during compare:\n";
	if (fp2 == fp1) {
		cout << "Equal function pointers point to the same function.\n"
				"fp1(6)=" << fp1(6) << endl <<
				"fp2(6)=" << pa1(6) << endl;
	}
	cout << "Can assign 'nullptr' to function pointer and then it points to no function. You can compare function pointers to 'nullptr'.\n";
	fp1 = nullptr;
	if (fp1 == nullptr) {
		cout << "Never use such function pointer!\n";
		// (*fp1)(3); //never!
	}

	cout << "\nNo assignment to 'void *' possible!\n";
	//void * vptr = fp1; //error: invalid conversion from ‘int (*)(int)’ to ‘void*’ [-fpermissive]

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
	//Never return a reference to local variables in a real program.
	return &resf2;
}
int const * f3(int inp) {
	resf3 = inp + inp + 3;
	//Never return a reference to local variables in a real program.
	return &resf3;
}
int & f4(int inp) {
	resf4 = inp + inp + 4;
	//Never return a reference to local variables in a real program.
	return resf4;
}
int const & f5(int inp) {
	resf5 = inp + inp + 5;
	//Never return a reference to local variables in a real program.
	return resf5;
}

int (*retFpt())(int) {
	return &f1;
}
