//============================================================================
// Name        : ExceptionProject.cpp
// Author      : joergboe
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <exception>
#include <stdexcept>

void myfunc(int inp) {
	std::cout << "myfunc(" << inp << ")" << std::endl;
	switch (inp) {
		case 0:
			std::cout << "throw std lib error type a sibling from std::exception" << std::endl;
			throw std::invalid_argument("Reason given");
		case 1:
			std::cout << "throw std::exception" << std::endl;
			throw std::exception();
		case 2:
			std::cout << "throw exception pointer with std lib error type a sibling from std::exception" << std::endl;
			throw new std::invalid_argument("Reason given 2");
		case 3: {
			std::cout << "throw a void pointer" << std::endl;
			void *ptr = new std::invalid_argument("Reason given 3");
			throw ptr;
		}
		case 4: {
			std::cout << "throw an int" << std::endl;
			int e = 4;
			throw e;
		}
		case 5: {
			std::cout << "throw any other (std::string)" << std::endl;
			throw std::string("do not see this");
		}
	};
}

int main() {
	std::cout << "ExceptionProject START" << std::endl;

	for (int i=0; i<6; i++) {
		try {
			myfunc(i);
		} catch (const std::exception& e) {
			std::cout << "Catch instance of std::exception& e.what(): " << e.what() << std::endl;
		} catch (const std::exception * e) {
			std::cout << "Catch instance of std::exception* e->what(): " << e->what() << std::endl;
			delete e;
		} catch (const void* e) {
			std::cout << "Catch instance of void*" << std::endl;
			//delete e; //problem!
		} catch (const int e) {
			std::cout << "Catch instance of int: " << e << std::endl;
		} catch (...) {
			std::cout << "catch(..)" << std::endl;
		}
		std::cout << std::endl;
	}

	try {
		myfunc(0); //throw a sibling from std::exception
	} catch (std::exception e) {
		std::cout << "Catch instance of std::exception e.what(): " << e.what() << std::endl;
		std::cout << "This is not recommended because e is not polymorph" << std::endl;
	}
	std::cout << std::endl;

	try {
		myfunc(4);
	} catch (const int& e) {
		std::cout << "Catch instance of int&: " << e << std::endl;
		std::cout << "This is possible" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "ExceptionProject END" << std::endl;
	return 0;
}
