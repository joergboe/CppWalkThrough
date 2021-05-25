/*
 * CommaOperator.cpp
 * Source      : Wikipedia https://en.wikipedia.org/wiki/Comma_operator
 *
 * The comma operator is a binary operator that evaluates its first operand and discards the result,
 * and then evaluates the second operand and returns this value (and type);
 * there is a sequence point between these evaluations.
 *
 * The use of the comma token as an operator is distinct from its use in
 * function calls and definitions, variable declarations, enum declarations,
 * and similar constructs, where it acts as a separator.
*/

#include <cstdlib>
#include <iostream>

using namespace std;

// function declarations
int f1();
int f2();
int f3();
void rev(char *, size_t);
void u2(int);

void waitUntilReturnPressed();

int main() {
	cout << "Hello CommaOperator!\n\n";
	cout << "   Source      : Wikipedia https://en.wikipedia.org/wiki/Comma_operator\n"
			"\n"
			"   The comma operator is a binary operator that evaluates its first operand and discards the result,\n"
			"   and then evaluates the second operand and returns this value (and type);\n"
			"   there is a sequence point between these evaluations.\n"
			"\n"
			"   The use of the comma token as an operator is distinct from its use in\n"
			"   function calls and definitions, variable declarations, enum declarations,\n"
			"   and similar constructs, where it acts as a separator.\n";
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3, i=0;\n"
				"Commas act as separators in this line, not as an operator.\n"
				"Expect: a=1, b=2, c=3, i=0\n";
		int a=1, b=2, c=3, i=0;
		cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3;\n"
				"int i = (a, b);\n"
				"Assigns value of b into i.\n"
				"Commas act as separators in the first line and as an operator in the second line.\n"
				"Expect: a=1, b=2, c=3, i=2\n";
		int a=1, b=2, c=3;
		int i = (a, b);
		cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3;\n"
				"{\n"
				"	int i = a, b;\n"
				"}\n"
				"Assigns value of a into i.\n"
				"Equivalent to: int (i = a), b;\n"
				"Commas act as separators in both lines.\n"
				"The braces on the second line avoid variable re-declaration in the same block,\n"
				"which would cause a compilation error.\n"
				"The second b declared is given no initial value.\n"
				"Expect in the inner block: a=1, b=undef, c=3, i=1\n";
		int a=1, b=2, c=3;
		{
			int i = a, b;
			cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
		}
	}
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3;\n"
				"int i = (a += 2, a + b);\n"
				"Increases value of a by 2, then assigns value of resulting operation a + b into i.\n"
				"Commas act as separators in the first line and as an operator in the second line.\n"
				"Expect: a=3, b=2, c=3, i=5\n";
		int a=1, b=2, c=3;
		int i = (a += 2, a + b);
		cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3;\n"
				"int i;\n"
				"i = a += 2, a + b;\n"
				"Increases value of a by 2, then stores value of a to i, and discards unused\n"
				"values of resulting operation a + b.\n"
				"Equivalent to: ((i = a) += 2), a + b;\n"
				"Commas act as separators in the first line and as an operator in the third line.\n"
				"Expect: a=3, b=2, c=3, i=3\n";
		int a=1, b=2, c=3;
		int i;
		i = a += 2, a + b;
		cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3;\n"
				"{\n"
				"	int i = a, b, c;\n"
				"}\n"
				"Assigns value of a into i.\n"
				"Commas act as separators in both lines.\n"
				"The braces on the second line avoid variable re-declaration in the same block,\n"
				"which would cause a compilation error.\n"
				"The second b and c declared are given no initial value.\n"
				"Expect in the inner block: a=1, b=undef, c=undef, i=1\n";
		int a=1, b=2, c=3;
		{
			int i = a, b, c;
			cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
		}
	}
	waitUntilReturnPressed();
	{
		cout << "int a=1, b=2, c=3;\n"
				"int i = (a, b, c);\n"
				"Commas act as separators in the first line and as an operator in the second line.\n"
				"Assigns value of c into i, discarding the unused a and b values.\n"
				"Expect: a=1, b=2, c=3, i=3\n";
		int a=1, b=2, c=3;
		int i = (a, b, c);
		cout << "a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	waitUntilReturnPressed();

	int r;
	r = f1();
	cout << "r=" << r << endl;
	waitUntilReturnPressed();
	r = f2();
	cout << "r=" << r << endl;
	waitUntilReturnPressed();
	r = f3();
	cout << "r=" << r << endl;
	waitUntilReturnPressed();

	cout << "* Use case 1: Multiple assignments in for loop *\n";
	char seq[] = {'A', 'B', 'C', 'D'};
	rev(seq, sizeof seq);

	cout << "\n* Use case 2: The comma can be used within a condition *\n"
			"(of an if, while, do while, or for) to allow auxiliary computations,\n"
			"particularly calling a function and using the result, with block scoping.\n";
	u2(3);


	cout << "\n* Use case 3: The comma can be used in preprocessor macros to perform multiple\n"
			"operations in the space of a single syntactic expression.*\n";
#define myassert(expr) if ( not expr ) cout << "Expr was false: '" << #expr << "'" << endl;

	int a = 5;
	myassert( ( "Condition not meet:", a < 5) );
	myassert( ( "Condition not meet:", a > 4) );

	cout << "END" << endl;
	return EXIT_SUCCESS;
}

int f1() {
	cout << "f1() { int a=1, b=2, c=3; return a=4, b=5, c=6; }\n"
			"Returns 6, not 4, since comma operator sequence points following the keyword\n"
			"return are considered a single expression evaluating to rvalue of final\n"
			"subexpression c=6.\n"
			"Commas act as operators in this line.\n";
	int a=1, b=2, c=3;
	return a=4, b=5, c=6;
}

int f2() {
	cout << "f2() { return 1, 2, 3; }\n"
			"Returns 3, not 1, for same reason as previous example.\n"
			"Commas act as operators in this line.\n";
	return 1, 2, 3;
}

int f3() {
	cout << "f3() { return(1), 2, 3; }\n"
			"Returns 3, not 1, still for same reason as above. This example works as it does\n"
			"because return is a keyword, not a function call. Even though compilers will\n"
			"allow for the construct return(value), the parentheses are only relative to \"value\"\n"
			"and have no special effect on the return keyword.\n"
			"Return simply gets an expression and here the expression is \"(1), 2, 3\".\n"
			"Commas act as operators in this line.\n";
	return(1), 2, 3;
}

/*
 * Use case 1: Multiple assignments in for loop
 */
void rev(char * s, size_t len) {
	char *first;
	for (first = s, s += len -1; s >= first; --s) {
		cout << *s;
	}
	cout << endl;
}

/*
 * Use case 2: The comma can be used within a condition
 * (of an if, while, do while, or for) to allow auxiliary computations,
 * particularly calling a function and using the result, with block scoping.
 */
void u2(int x) {
	if (x = x/2, x < 2) {
		cout << "x/2=" << x << endl;
	}
}

/* A helper function:
 * Wait until the return key was pressed
 * Stop the program if Cntr+D key was pressed
 */
void waitUntilReturnPressed() {
	cout << "Enter return key to continue or Ctrl+D to exit.\n";
	string s;
	getline(cin, s);
	if (cin.eof())
		// For the sake of simplicity, the exit function is used here.
		// Note :Objects with automatic storage duration are not destructed!
		exit(EXIT_FAILURE);
}
