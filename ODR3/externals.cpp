#include <iostream>

// inline function is never exported
// thus omit extern
extern inline void bar() {
	std::cout << "bar(): Hello!\n";
}

extern void ext_funct() {
	std::cout << "Calling bar from ext_funct: ";
	bar();
}
