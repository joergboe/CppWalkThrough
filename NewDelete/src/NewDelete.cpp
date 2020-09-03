//============================================================================
// Name        : NewDelete.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	cout << "Hello NewDelete" << endl;
	int * ip = new int;
	*ip = 55;
	cout << "ip=" << ip << " *ip=" << *ip << endl;
	delete ip;
	cout << "ip=" << ip << " *ip=" << *ip << endl;
	ip = nullptr;
	cout << "ip=" << ip << endl;

	for (int x=0; x<4; ++x) {
		int * ipa = new int[x];
		cout << "Arr[" << x << "] ";
		int * ipc = ipa;
		for (int z=0; z<x; ++z)
			cout << *(ipc++);
		cout << endl;
		delete[] ipa;
	}
	cout << "End" << endl;
	return 0;
}
