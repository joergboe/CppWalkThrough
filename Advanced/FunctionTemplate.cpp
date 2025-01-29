//============================================================================
// Name        : FunctionTemplate.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

template<typename T>
void print(T inp) {
	cout << "T:" << inp << endl;
}
template<>
void print<int>(int inp) {
	cout << "int:" << inp << endl;
}

enum typf {none, one, two};

template<int I>
void print1() {
	cout << "I=" << I << endl;
}
template<>
void print1<0>() {
	cout << "special I=0" << endl;
}

template<typename T, typename C>
void print2(T inp, C inp2) {
	cout << "CT " << ":" << inp << " " << inp2 << endl;
}
template<>
void print2<char, int>(char inp, int inp2) {
	cout << "special char int " << inp << endl;
}

char Label1[] = "Label1"; //must not be constant, because wee need external binding
char Label2[] = "Label2";

template<char * cp>
void foo() {
	cout << "Foo allg cp=" << cp << endl;
}
template<>
void foo<Label2>() {
	cout << "Special foo " << Label2 << endl;
}

int main() {
	cout << "!!!Hello World!!!" << endl;
	int i = 55;
	print(i);
	print(5.5);
	print2<int, char>(i, 'a');
	print2(6.6, 1);
	print2('c', 11);
	print1<two>();
	print1<0>();
	foo<Label1>();
	foo<Label2>();
	cout << "END" << endl;
	return 0;
}
