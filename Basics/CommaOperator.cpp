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

#include <iostream>
using namespace std;

int main() {
	cout << "Hello CommaOperator!" << endl;
	{
		/**
		 *  Commas act as separators in this line, not as an operator.
		 *  Results: a=1, b=2, c=3, i=0
		 */
		int a=1, b=2, c=3, i=0;
		cout << "No 1: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	{
		/**
		 *  Assigns value of b into i.
		 *  Commas act as separators in the first line and as an operator in the second line.
		 *  Results: a=1, b=2, c=3, i=2
		 */
		int a=1, b=2, c=3;
		int i = (a, b);
		cout << "No 2: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	{
		/**
		 *  Assigns value of a into i.
		 *  Equivalent to: int (i = a), b;
		 *  Commas act as separators in both lines.
		 *  The braces on the second line avoid variable redeclaration in the same block,
		 *  which would cause a compilation error.
		 *  The second b declared is given no initial value.
		 *  Results: a=1, b=2, c=3, i=1
		 */
		int a=1, b=2, c=3;
		{ int i = a, b;
			cout << "No 3: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
		}
	}
	{
		/**
		 *  Increases value of a by 2, then assigns value of resulting operation a + b into i.
		 *  Commas act as separators in the first line and as an operator in the second line.
		 *  Results: a=3, b=2, c=3, i=5
		 */
		int a=1, b=2, c=3;
		int i = (a += 2, a + b);
		cout << "No 4: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	{
		/**
		 *  Increases value of a by 2, then stores value of a to i, and discards unused
		 *  values of resulting operation a + b.
		 *  Equivalent to: ((i = a) += 2), a + b;
		 *  Commas act as separators in the first line and as an operator in the third line.
		 *  Results: a=3, b=2, c=3, i=3
		 */
		int a=1, b=2, c=3;
		int i;
		i = a += 2, a + b;
		cout << "No 5: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}
	{
		/**
		 *  Assigns value of a into i.
		 *  Commas act as separators in both lines.
		 *  The braces on the second line avoid variable redeclaration in the same block,
		 *  which would cause a compilation error.
		 *  The second b and c declared are given no initial value.
		 *  Results: a=1, b=2, c=3, i=1
		 */
		int a=1, b=2, c=3;
		{ int i = a, b, c;
			cout << "No 6: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
		}
	}
	{
		/**
		 *  Commas act as separators in the first line and as an operator in the second line.
		 *  Assigns value of c into i, discarding the unused a and b values.
		 *  Results: a=1, b=2, c=3, i=3
		 */
		int a=1, b=2, c=3;
		int i = (a, b, c);
		cout << "No 7: a=" << a << " b=" << b << " c=" << c << " i=" << i << endl;
	}

	int f1();
	int f2();
	int f3();
	int i;
	i = f1();
	cout << "No 8: i=" << i << endl;
	i = f2();
	cout << "No 9: i=" << i << endl;
	i = f3();
	cout << "No 10: i=" << i << endl;

	void rev(char *, size_t);
	char seq[] = {'A', 'B', 'C', 'D'};
	rev(seq, sizeof seq);

	void u2(int);
	u2(3);

	/*
	 * Use 3: The comma can be used in preprocessor macros to perform multiple
	 * operations in the space of a single syntactic expression.
	 */
#define myassert(expr) if ( not expr ) cout << "Expr was false: '" << #expr << "'" << endl;

	int a = 5;
	myassert( ( "Condition not meet:", a < 5) );
	myassert( ( "Condition not meet:", a > 4) );

	cout << "END" << endl;
	return EXIT_SUCCESS;
}

	/**
	 *  Returns 6, not 4, since comma operator sequence points following the keyword
	 *  return are considered a single expression evaluating to rvalue of final
	 *  subexpression c=6.
	 *  Commas act as operators in this line.
	 */
int f1() {
	int a=1, b=2, c=3;
	return a=4, b=5, c=6;
}

	/**
	 *  Returns 3, not 1, for same reason as previous example.
	 *  Commas act as operators in this line.
	 */
int f2() {
	return 1, 2, 3;
}

	/**
	 *  Returns 3, not 1, still for same reason as above. This example works as it does
	 *  because return is a keyword, not a function call. Even though compilers will
	 *  allow for the construct return(value), the parentheses are only relative to "value"
	 *  and have no special effect on the return keyword.
	 *  Return simply gets an expression and here the expression is "(1), 2, 3".
	 *  Commas act as operators in this line.
	 */
int f3() {
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
