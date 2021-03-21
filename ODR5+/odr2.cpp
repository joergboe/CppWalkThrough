#include <stdio.h>
#include "odr.h"

class Derived : public Base {
public:
	void foo() override {
		printf("%s() TWO: World\n", __func__);
	}
};

Base *create_derived2() {
	return new Derived();
}
