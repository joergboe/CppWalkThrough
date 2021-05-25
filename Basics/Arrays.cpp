/*
 * Demonstrating the basic principles of array usage in c++
 */

#include <iterator> // std::begin() std::end()
#include <iostream>
#include <typeinfo>
#include <array>

using namespace std;

// function definitions to demonstrate different kind of array parameters

void wrongUseOneArray(int inp[3]);

// array as parameter
void useOneArray(int inp[], size_t size);

// array reference as parameter
void useOneArray(int (&inp)[3]);

// std::array (c++11) has the semantics and effectivity of an integrated
using MyArray = array<char, 5>;
// std::array as parameter
void useOneArray(MyArray & inp);

int main() {
	cout << "*** Integrates arrays; subscriptions and sizes ***\n\n"
			"A declaration 'T name[size]' defines a array of type T\n"
			"The size of the array is deducted from from the initializer";
	int a1[] = {0, 1, 3};
	int a2[3];
	cout << "To define type aliases use 'typedef' or 'using'\n";
	typedef int ArrayType1[3];
	cout << "The size may be undefined\n";
	typedef int ArrayType2[];
	cout << "In using declarations use 'T[size]'\n";
	using ArrayType3 = int[3];
	using ArrayType4 = int[];
	typedef char const * ArrayType5[];
	using ArrayType6 = char const * [];
	cout << "typeid(ArrayType1).name(): " << typeid(ArrayType1).name() <<
			"\ntypeid(ArrayType2).name(): " << typeid(ArrayType2).name() <<
			"\ntypeid(ArrayType3).name(): " << typeid(ArrayType3).name() <<
			"\ntypeid(ArrayType4).name(): " << typeid(ArrayType4).name() <<
			"\ntypeid(ArrayType5).name(): " << typeid(ArrayType5).name() <<
			"\ntypeid(ArrayType6).name(): " << typeid(ArrayType6).name() << endl;

	cout << "\nThe definition of an array (global, static or local), the size must be known at compile time:\n";
	//ArrayType4 at4; //  error: storage size of ‘at4’ isn’t known

	cout << "\nInitialization with initializer can have 2 forms: old style or extended initializer list (since C++11)\n";
	short unsigned int shortIntArray1[] = {1, 128};
	short unsigned int shortIntArray2[] {1, 127};
	cout << "sizes shortIntArray1[]=" << sizeof shortIntArray1 << " shortIntArray2[]=" << sizeof shortIntArray2 << endl;
	cout << "\nEmpty initializer list with size deduction yields a array of size 0\n"
			"Zero size arrays are rejected from strict ISO C++; thus flag the extension.\n";
	__extension__ char charArr1[] = {};
	__extension__ char charArr2[] {};
	cout << "size charArr1: " << sizeof charArr1 << endl;
	cout << "size charArr2: " << sizeof charArr2 << endl;
	cout << "Empty initializer list yields a zero initialized array:\n";
	int intArr1[4]{};
	cout << "intArr1: ";
	for (auto x : intArr1)
		cout << x << " ";
	cout << endl;
	cout << "\nThe {} initializer prevents narrowing conversions:\n";
	//short int shortIntArray3[] = {1234567, 127}; // error: narrowing conversion of ‘1234567’ from ‘int’ to ‘short int’ inside { } [-Wnarrowing]

	cout << "\nUse subscriptions to get array elements : " << a1[0] << ", " << a1[1] << ", " << a1[2] << endl;
	cout << "sizeof a1 = " << sizeof a1 << " : delivers the size of the array in memory" << endl;

	size_t elem = sizeof a1 / sizeof(int);
	cout << "a1 has " << elem << " elements\n";

	cout << "\n*** Assignments and for loop ***" << endl;
	//a2 = a1; //error: invalid array assignment
	cout << "a2 = a1; !!! no array assignment possible: use for loop instead or std::array\n";
	for (size_t i=0; i<elem; ++i)
		a2[i] = a1[i];

	cout << "Integrated arrays are applicable in new c++11 range-based for loops" << endl;
	cout << "Elements from a2 are now: ";
	for (auto x : a2)
		cout << x << ", ";
	cout << endl;

	cout << "Integrated array is now applicable to function std::begin() and std::end() from header iterator\n"
			"And can be used to iterate through the array";
	auto it1 = begin(a2);
	cout << "Type of the array iterator: " << typeid(it1).name() << endl <<
		"Elements from a2 are now: ";
	for (; it1 != end(a2); ++it1)
		cout << *it1 << ", ";
	cout << endl;


	cout << "\n*** Arrays are easily converted into pointers to the first element ***\n";
	int * ap = a1;
	cout << "*ap=" << *ap << endl;
	cout << "Size information is lost when the array was converted to a pointer\n";
	cout << "sizeof *ap = " << sizeof *ap << " : delivers the size of the element type sizeof(int) = " << sizeof(int) << endl;
	cout << "Pointer arithmetic gives access to array elements: " << *ap << ", " << *(ap+1) << ", " << *(ap+2) << endl;

	cout << "\n*** Arrays in heap memory may be created and with initializer list ***\n"
			"But here the array size is not deducted! ?? Compiler Problem ?? -> P1009R2\n";
	auto a3 = new int[4]{5, 6, 7, 8};
	cout << "size of a3 = " << sizeof a3 << " : delivers the size of the pointer type = " << sizeof(void*) << endl;
	cout << "sizeof *a3 = " << sizeof *a3 << " : delivers the size of the element type sizeof(int) = " << sizeof(int) << endl;
	cout << "No idea how many elements in *a3. It is just a pointer to int: " << typeid(a3).name() << endl;

	cout << "\nThe empty initializer list yields a zero initialized array.\n"
			"A heap or stack allocated array with no initializer has undefined values (are probably 0):\n";
	{
		auto a4 = new int[4]{};
		auto const a5 = new int[4];
		auto ax = a3; // do not alter the original pointer; we need it for the deletion
		cout << "a3 = ";
		for (int i = 0; i < 4; ++i)
			cout << *ax++ << " ";
		cout << "\na4 = ";
		ax = a4;
		for (int i = 0; i < 4; ++i) {
			cout << *ax << " ";
			++ax;
		}
		cout << "\na5 = ";
		for (int i = 0; i < 4; ++i)
			cout << a5[i] << " ";

		cout << "\nTo delete heap arrays use delete[]" << endl;
		delete[] a3;
		delete[] a4;
		delete[] a5;
	}
	cout << "\n*** string literals *** are constant char arrays " << typeid("abc").name() << endl;
	cout << "a terminating null char is automatically appended : sizeof \"abc\" = " << sizeof "abc" << endl;
	//"abc"[2] = 'x'; // error: assignment of read-only location ‘"abc"[2]’
	char str[] = "abcd";
	char mychar = str[1];
	cout << "\"abcd\"[1]=" << "abcd"[1] << "=" << mychar << endl;
	const char * charptr = "xyz";
	cout << "and are silently converted to const char * charptr=" << charptr << endl;

	cout << "\n*** This is an amazing hack!\n"
	"a[j] == *(&a[0]+j) == *(a+j) == *(j+a) == j[a]" << endl;
	//a[j] == *(&a[0]+j) == *(a+j) == *(j+a) == j[a]
	cout << "\"abcd\"[1]=" << "abcd"[1] << endl;
	cout << "1[\"abcd\"]=" << 1["abcd"] << endl;

	cout << "*** array parameters ***\n"
			"The first obvious attempt is wrong: The information about the array size is lost.\n"
			"(because of the array to pointer decay)\n";
	int aw1[] = { 10, 20, 30, 40, 50 };
	wrongUseOneArray(aw1);
	useOneArray(a1, 3);
	useOneArray(a1);
	array<char, 5> chararr{"abcd"};
	useOneArray(chararr);

	cout << "\n*** Arrays with more dimensions are arrays of arrays ...\n";
	cout << "Note: declaration of an multidimensional array must have bounds for all dimensions except the first\n"
			"Evolution of multidimensional array:\n"
			"int var;       // var of type int\n"
			"int var[2];    // array 2 of int\n"
			"int var[3][2]; // array 3 of array 2 of int\n";
	int ia[][2] = {{1,2}, {3,4}, {5,6}};
	cout << "typeid: " << typeid(ia).name() << " size: " << sizeof ia << endl;

	cout << "\n*** More array declarations ***\n"
			"\nArray of pointer type\n";
	char const * charPointerArray[] = { "string1", "string2"};
	cout << "Sizeof charPointerArray: " << sizeof charPointerArray << endl;

	cout << "\nArray reference (must use parentheses to force correct declarator binding):\n";
	char const * (& charPointerArrayRef)[2] = charPointerArray; //
	cout << "Print *charPointerArrayRef: ";
	for (std::size_t i = 0; i < (sizeof charPointerArrayRef / sizeof(char const *)); ++i)
		cout << charPointerArrayRef[i] << " "; // it is not ! (*charPointerArray)[i]
	cout << endl;
	cout << "Alias definitions of array references:\n";
	typedef char const * (& CharPointerArrayRefType1)[2];
	using CharPointerArrayRefType2 = char const * (&)[2];
	cout << "Type of CharPointerArrayRefType1: " << typeid(CharPointerArrayRefType1).name() << endl <<
			"Type of CharPointerArrayRefType2: " << typeid(CharPointerArrayRefType2).name() << endl;

	{
		cout << "Cast an array pointer into a reference with 'reinterpret_cast<>()':\n";
		char const * * heapArray1 = new char const *[2] {"'a new string'", "'one more new string'"};
		CharPointerArrayRefType1 heapArray1Ref = reinterpret_cast<char const * (&)[2]>(*heapArray1);
		cout << "Print heapArray1: ";
		for (std::size_t i = 0; i < 2; ++i)
			cout << heapArray1[i] << " ";
		cout << endl;
		cout << "Print heapArray1Ref: ";
		for (auto x : heapArray1Ref)
			cout << x << " ";
		cout << endl;

		cout << "And convert back to the pointer:\n";
		char const ** ptr = heapArray1Ref;
		if (ptr == heapArray1)
			cout << "Properly converted!\n";
		cout << "free memory with delete[] operator requires a pointer.\n";
		delete[] ptr;
	}

	cout << "\nPointer to array type (must use parentheses to force correct declarator binding):\n";
	char const * (* charPointerArrayPointer)[2] = &charPointerArray;
	cout << "Sizeof charPointerArrayPointer: " << sizeof charPointerArrayPointer << endl;
	cout << "Print *charPointerArrayPointer: ";
	for (int i = 0; i < 2 ; ++i)
		cout << (*charPointerArrayPointer)[i] << " ";
	cout << endl;
	using charPointerArrayPointer2 = char const * (*) [2];
	cout << "charPointerArrayPointer2: " << typeid(charPointerArrayPointer2).name() << endl;

	cout << "\n\n*** Conclusion ***\n"
			"Integrated arrays are silently converted to pointers at the slightest occasion.\n"
			"Thus the size information is lost. std::array provides a type save alternative.\n"
			"Integrated arrays have always a fixed size which must be known at compile time.\n"
			"If variable size array is required use std::vector.\n";

	cout << "END" << endl;
	return 0;
}

void wrongUseOneArray(int inp[3]) {
	cout << "\n*** void wrongUseOneArray(int inp[3]) ***\n";
	cout << "typeid(inp): " << typeid(inp).name() <<
			"'inp' is decayed to a pointer and the actual array size is not available!\n"
			"sizeof inp: " << sizeof inp << "\n"
			"inp = ";
	for (int i = 0; i < 3; ++i) cout << inp[i] << " ";
	cout << "\nNote: the pointer can be used with subscription like an array.\n";
}

void useOneArray(int inp[], size_t size) {
	cout << "\n*** void useOneArray(int inp[], size_t size) ***\n";
	cout << "The usual way to hand over an array int inp[] but the information about the size of the array is lost\n";
	cout << "the type of inp here is pointer to int: " << typeid(inp).name() << " size: " << sizeof inp << endl;
	cout << "With a second argument we can now iterate over the array:\n";
	for (size_t i=0; i<size; ++i)
		cout << inp[i] << ", ";
	cout << "\n";
	cout << "However this is error prone work!" << endl;
}

// Use of array reference is possible
void useOneArray(int (&inp)[3]) {
	cout << "\n*** void useOneArray(int (&inp)[3]) ***\n";
	cout << "Use of array reference to keep size information : int (&inp)[3] size=" << sizeof inp << " type=" << typeid(inp).name() << endl;
	cout << "inp=[";
	for (auto x : inp)
		cout << x << ", ";
	cout << "]" << endl;
}

void useOneArray(MyArray & inp) {
	cout << "\n*** void useOneArray(MyArray & inp) ***\n";
	cout << "std::array (c++11) has the semantics an integrated array and offers features of a container\n";
	cout << "see: https://en.cppreference.com/w/cpp/container/array \n";
	cout << "inp type: " << typeid(inp).name() << " size: " << sizeof inp << " number elements: " << inp.size() << endl;
	cout << "with iterator we can walk through\ninp :";
	for (auto it = inp.begin(); it < inp.end() - 1; ++it)
		cout << *it << ", ";
	cout << endl;
	cout << "the last element is the 0 character: ";
	int x = inp.back();
	cout << x << endl;
	cout << boolalpha << "Some functions are pathologist: inp.empty(): " << inp.empty() << endl;
	array<int, 0> nullarray{};
	cout << "Some functions are pathologist: nullarray.empty(): " << nullarray.empty() << endl;
	cout << "inp.max_size() = " << inp.max_size() << endl;
	cout << "assignment is possible:\n";
	MyArray arr2 = inp;
	for (auto it = arr2.begin(); it < arr2.end() - 1; ++it)
		cout << *it << ", ";
	cout << endl;
	cout << "Compare inp == arr2: " << (inp == arr2) << endl;
	cout << "And more ..." << endl;
}
