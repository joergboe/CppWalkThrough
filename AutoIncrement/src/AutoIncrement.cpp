#include <iostream>
using namespace std;

int main() {
	cout << "***** pre increment : value = 1 *****" << endl;
	int value = 1;
	cout << "++value=" << ++value << endl;
	cout << "value=" << value << endl;
	cout << "standalone operation : ++value" << endl;
	++value;
	cout << "value=" << value << endl;
	int copy = ++value;
	cout << "copy = ++value; copy=" << copy << endl;
	cout << "value=" << value << endl;

	cout << "***** post increment : value = 1 *****" << endl;
	value = 1;
	cout << "value++=" << value++ << endl;
	cout << "value=" << value << endl;
	cout << "standalone operation : value++" << endl;
	value++;
	cout << "value=" << value << endl;
	copy = value++;
	cout << "copy = value++; copy=" << copy << endl;
	cout << "value=" << value << endl;

	cout << "END" << endl;
	return 0;
}
