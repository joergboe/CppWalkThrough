/*
 * odr.h
 */

#ifndef ODR_H_
#define ODR_H_

// abstract base
class Base {
public:
	virtual void foo() = 0;
	virtual ~Base() = default; // define a virtual destructor when any virtual function is defined
};

extern Base *create_derived1();
extern Base *create_derived2();

#endif /* ODR_H_ */
