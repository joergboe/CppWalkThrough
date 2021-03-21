#include <cstdio>
#include "odr.h"

class Derived : public Base {
public:
	void foo() override {
		std::printf("%s() ONE: Hello\n", __func__);
	}
};

Base *create_derived1() {
	return new Derived();
}

