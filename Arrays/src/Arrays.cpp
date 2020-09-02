/*
 * Demonstrating the basic principles of array usage in c++
 */

#include <iostream>
#include <typeinfo>
#include <array>

using namespace std;

// function definitions to demonstrate different kind of array parameters
// array as parameter
void useOneArray(int inp[], size_t size);
// array reference as parameter
void useOneArray(int (&inp)[3]);
// std::array (c++11) has the semantics and effectivity of an integrated
using MyArray = array<char, 5>;
// std::array as parameter
void useOneArray(MyArray & inp);

int main() {
	cout << "*** Integrates arrays; subscriptions and sizes ***" << endl;
	int a1[] = {0, 1, 3};
	cout << "use subscriptions to get array elements : " << a1[0] << ", " << a1[1] << ", " << a1[2] << endl;
	cout << "sizeof a1 = " << sizeof a1 << " : delivers the size of the array in memory" << endl;

	size_t elem = sizeof a1 / sizeof(int);
	cout << "a1 has " << elem << " elements\n";

	cout << "\n*** Assignments and for loop ***" << endl;
	int a2[3];
	cout << "a2 = a1; !!! no array assignment possible: use for loop instead\n";
	for (size_t i=0; i<elem; ++i)
		a2[i] = a1[i];

	cout << "Integrated arrays are applicable in new c++11 range-based for loops" << endl;
	cout << "Elements from a2 are now: ";
	for (auto x : a2)
		cout << x << ", ";
	cout << endl;

	cout << "\n*** Arrays are easily converted into pointers to the first element ***\n";
	int * ap = a1;
	cout << "*ap=" << *ap << endl;
	cout << "Size information is lost when the array was converted to a pointer\n";
	cout << "sizeof *ap = " << sizeof *ap << " : delivers the size of the element type sizeof(int) = " << sizeof(int) << endl;
	cout << "Pointer arithmetic gives access to array elements: " << *ap << ", " << *(ap+1) << ", " << *(ap+2) << endl;

	cout << "\n*** Array in heap memory may be created and with initializer list ***";
	int * a3 = new int[4]{ 5, 6, 7, 8};
	cout << "sizeof a3 = " << sizeof a3 << " : delivers the size of the pointer type = " << sizeof(void*) << endl;
	cout << "sizeof *a3 = " << sizeof *a3 << " : delivers the size of the element type sizeof(int) = " << sizeof(int) << endl;
	cout << "No idea how many elements in *a3. It is just a pointer." << endl;

	cout << "To delete heap arrays use delete[]" << endl;
	delete[] a3;

	cout << "\n*** string literals *** are char arrays " << typeid("abc").name() << endl;
	cout << "a terminating null char is automatically appended : sizeof \"abc\" = " << sizeof "abc" << endl;
	char str[] = "abcd";
	char mychar = str[1];
	cout << "\"abcd\"[1]=" << "abcd"[1] << "=" << mychar << endl;
	const char * charptr = "xyz";
	cout << "and are converted to const char * charptr=" << charptr << endl;

	cout << "\n*** This is an amazing hack!\n"
	"a[j] == *(&a[0]+j) == *(a+j) == *(j+a) == j[a]" << endl;
	//a[j] == *(&a[0]+j) == *(a+j) == *(j+a) == j[a]
	cout << "\"abcd\"[1]=" << "abcd"[1] << endl;
	cout << "1[\"abcd\"]=" << 1["abcd"] << endl;

	useOneArray(a1, 3);
	useOneArray(a1);
	array<char, 5> chararr{"abcd"};
	useOneArray(chararr);

	cout << "\n*** Arrays with more dimensions are arrays of arrays ...\n";
	cout << "Note: declaration of an multidimensional array must have bounds for all dimensions except the first\n";
	int ia[][2] = {{1,2}, {3,4}, {5,6}};
	cout << "typeid: " << typeid(ia).name() << " size: " << sizeof ia << endl;

	cout << "END" << endl;
	return 0;
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
