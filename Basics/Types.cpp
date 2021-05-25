/*
 * Internal types and literals
 */

#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <limits>
#include <type_traits>
#include <climits>

using std::cout;
using std::endl;
using std::ostream;
using std::is_same;
using std::numeric_limits;
using std::setw;
using std::ios_base;

template<typename T>
void pr_vvstmm(const char name[], const T& var1, T& var2, const char comment[] = "") {
	cout.setf (ios_base::left , ios_base::adjustfield);
	cout << name << " var1=" << setw(20) << var1 << " var2=" << setw(20) << var2 << " size:" << setw(2) << sizeof(T) << " typeid:" << setw(5) << typeid(T).name();
	if (is_same<char, T>::value || is_same<signed char, T>::value || is_same<unsigned char, T>::value) {
		cout << " min:" << setw(20) << static_cast<int>(numeric_limits<T>::min()) << " max:" << setw(20) << static_cast<int>(numeric_limits<T>::max());
	} else {
		cout << " min:" << setw(20) << numeric_limits<T>::min() << " max:" << setw(20)<< numeric_limits<T>::max();
	}
	cout << " " << comment << "\n";
}

template<typename T>
void pr_vstmm(const char name[], const T& var, const char comment[] = "") {
	cout.setf (ios_base::left , ios_base::adjustfield);
	cout << name << " var=" << setw(20) << var << " size:" << setw(2) << sizeof(T) << " typeid:" << setw(5) << typeid(T).name();
	if (is_same<char, T>::value || is_same<signed char, T>::value || is_same<unsigned char, T>::value) {
		cout << " min:" << setw(20) << static_cast<int>(numeric_limits<T>::min()) << " max:" << setw(20)<< static_cast<int>(numeric_limits<T>::max());
	} else {
		cout << " min:" << setw(20) << numeric_limits<T>::min() << " max:" << setw(20)<< numeric_limits<T>::max();
	}
	cout << " " << comment << "\n";
}

template<typename T>
void pr_vst(const char name[], const T& var, const char comment[] = "") {
	cout.setf (ios_base::left , ios_base::adjustfield);
	cout << name << " var=" << setw(20) << var << " size:" << setw(2) << sizeof(T) << " typeid:" << setw(5) << typeid(T).name();
	cout << " " << comment << "\n";
}

template<typename T>
void pr_st(const char name[], const char comment[] = "") {
	cout.setf (ios_base::left , ios_base::adjustfield);
	cout << name << " size:" << setw(2) << sizeof(T) << " typeid:" << setw(5) << typeid(T).name();
	cout << " " << comment << "\n";
}

int main() {
	cout << "Print sizes and typeinfos for internal types and literals\n";
	{
		cout << "\n****** Boolean Type ******\n"
				"The type bool holds 2 values: false and true.\n"
				"	- false is represented by a numerical value of 0\n"
				"	- true is represented by a numerical value of 1\n";
		bool var1 = false; bool var2 = true;
		pr_vvstmm("bool :", var1, var2);

		cout << "\nThe literals for type bool are false and true.\n";
		pr_vst("true:", true);
		pr_vst("true:", false);

		cout << "\nNote: The value of sizeof(bool) is implementation defined and might differ from 1\n"
				"\n"
				"The stream manipulators std::boolalpha and std::noboolalpha enable and disable\n"
				"the alphanumeric input or output format for bool types.\n"
				<< std::boolalpha << "var1=" << var1 << " var2=" << var2 << "\n";

		cout << "\nBoolean values can be converted from and to integers.\n"
				"	- the integer value 0 is converted to false.\n"
				"	- other integer values are converted to true.\n";
		var1 = 0; var2 = 55;
		cout << "var1 = 0 : " << var1 << " var2 = 55 : " << var2 << "\n";
		int i = var2;
		cout << "int i = var2 : " << i << std::noboolalpha << "\n";
	}

	cout << "\n****** Character Types ******\n"
			"Character types can be used in many ways.\n"
			"They primary purpose is to hold characters for the representation of text.\n"
			"But they are also used to represent raw memory or integral types.\n"
			"In C++ there are basically 3 kinds f car types: car, signed char and unsigned char.\n";
	{
		char var1 = 'a'; char var2 = 'b';
		pr_vvstmm("char:         ", var1, var2);
	}
	{
		signed char var1 = 'a'; signed char var2 = 'b';
		pr_vvstmm("signed char:  ", var1, var2);
	}
	{
		unsigned char var1 = 'a'; unsigned char var2 = 'b';
		pr_vvstmm("unsigned char:", var1, var2);
	}
	cout << "\nNote: char, signed char and unsigned char are tree different types.\n"
			"If the char type is signed or unsigned depends on the implementation.\n"
			"The unsigned char type is used for object representations and raw memory.\n"
			"The size of char, signed char and unsigned char is per definition 1.\n"
			"But the number of bits in a char may be different from 8. The CHAR_BIT\n"
			"in header climits provides information about this size. The value depends\n"
			"on the particular system and library implementation, but shall reflect the\n"
			"limits of these types in the target platform.\n";
	cout << "CHAR_BIT=" << CHAR_BIT << "\n";

	cout << "\nThe basic input/output system ('operator<<', 'operator>>') interprets values\n"
			"of the char type as characters and not as numbers.\n";
	cout << "\nChar literals are the characters of the implementation (ASCII) enclosed in single quotes:\n";
	pr_vst("'a' :", 'a');
	cout << "Some non printable characters and the quote itself can be expressed with escape sequences:\n"
			"\\n - Newline\n"
			"\\t - Tab\n"
			"\\v - Vertical Tab\n"
			"\\b - Backpace\n"
			"\\r - Carriage Return\n"
			"\\f - Form Feed\n"
			"\\a - Bell\n"
			"\\\\ - Backslash\n"
			"\\? - ?\n"
			"\\\' - Single Quote\n"
			"\\\" - Double Quote\n";
	cout << "\nThe integer value of an character can be written as octal number or as hex number:\n"
			"\\ooo - octal\n"
			"\\xhhh - hex\n"
			"There is no limit in the number of octal or hex digits. The number sequence ends\n"
			"with the first character which is not a octal or hexadecimal digit.\n";

	cout << "\nNote: With the number notation the program becomes platform dependent!\n";

	cout << "For every value of type unsigned char in range [0, 255], converting the value to char\n"
			"and then back to unsigned char produces the original value. (since C++11).\n";

	cout << "\nThe type wchar_t can hold wider character sets:\n";
	{
		wchar_t var1 = L'0'; wchar_t var2 = L'a';
		pr_vvstmm("wchar_t var1 = L'0'; wchar_t var2 = L'a';  :", var1, var2);
	}
	cout << "\nNote: Values of the wchar_t type are interpreted as numbers from the\n"
			"basic input output system.\n";

	cout << "Literals of type wchar_t are written in the form:\n";
	pr_vst("L'a':", L'a');
	cout << "Or as octal or hexadecimal number format:\n";
	pr_vst("L'\\x30'", L'\x30');
	pr_vst("L'\\60'", L'\60');

#if __cplusplus >= 201103L
	cout << "Types char16_t and char32_t:\n";
	{
		char16_t var1 = u'\0'; char16_t var2 = u'@';
		pr_vvstmm("char16_t:     ", var1, var2, "(C++11)");
	}
	{
		char32_t var1 = U'0'; char32_t var2 = U'@';
		pr_vvstmm("char32_t:     ", var1, var2, "(C++11)");
	}
	cout << "\nNote: Values of the char16_t and char32_t type are interpreted as numbers from the\n"
			"basic input output system.\n";

	cout << "\nLiterals of type char16_t and char32_t are written in the form:\n";
	pr_vst("char16_t=u'a':",u'a', "output as integer (C++11)");
	pr_vst("char32_t=U'a':",U'a', "output as integer (C++11)");

	cout << "Literals of wider character sets can be expressed as octal number or hex number like:\n";
	pr_vst("u'\\x0040'    :",u'\x0040');
	pr_vst("u'\\x00000040':",u'\x0000040');
	pr_vst("U'\\x0040'    :",U'\x0040');
	pr_vst("U'\\x00000040':",U'\x0000040');
#endif

	cout << "\nNote: wchar_t, char16_t and char32_t are interpreted as integers in output stream.\n";

	cout << "\n****** Integer Types ******:\n";
	{
		short int var1 = 0; short int var2 = 1;
		pr_vvstmm("short int:             ", var1, var2);
		signed short int ssa = 0; signed short int ssb = 1;
		pr_vvstmm("signed short int:      ", ssa, ssb);
		unsigned short int usa = 0u; unsigned short int usb = 1u;
		pr_vvstmm("unsigned short int:    ", usa, usb);
	}
	{
		int var1 = 0; int var2 = 1;
		pr_vvstmm("int:                   ", var1, var2);
		signed int sia = 0; signed int sib = 1;
		pr_vvstmm("signed int:            ", sia, sib);
		unsigned int uia = 0u; unsigned int uib = -1U;
		pr_vvstmm("unsigned int:          ", uia, uib);
	}
	{
		long int var1 = 0l; long int var2 = 1l;
		pr_vvstmm("long int:              ", var1, var2);
		signed long int sla = 0l; signed long int slb = 1l;
		pr_vvstmm("signed long int:       ", sla, slb);
		unsigned long int ula = 0lu; unsigned long int ulb = 1lu;
		pr_vvstmm("unsigned long int:     ", ula, ulb);
	}
#if __cplusplus >= 201103L
	{
		long long int lla = 0ll; long long int llb = 1ll;
		pr_vvstmm("long long int:         ", lla, llb, "(C++11)");
		signed long long int slla = 0ll; signed long long int sllb = 1ll;
		pr_vvstmm("signed long long int:  ", slla, sllb, "(C++11)");
		unsigned long long int ulla = 0llu; unsigned long long int ullb = 1llu;
		pr_vvstmm("unsigned long long int:", ulla, ullb, "(C++11)");
	}
#endif

	cout << "\nNote: The signed types are aliases.\n"
			"sizeof(char) <= sizeof(short int) <= sizeof(int) <= sizeof(long int) <= sizeof(long long int)\n"
			"with\n"
			"sizeof(char) == 1\n"
			"sizeof(short int) >= 2\n"
			"sizeof(long int) >= 4\n"
			"sizeof(long long int) >= 8\n";

	cout << "\n*** Integer Literals\n"
			"Integer literals can be specified in decimal format\n";
	pr_vst("10                   :", 10);
	cout << "!Numbers with a leading 0 are interpreted as base 8 numbers!\n";
	pr_vst("010                  :", 010);
	cout << "!Numbers with a leading 0x or 0X are interpreted as base 16 numbers!\n";
	pr_vst("0x10                 :", 0x10);
	cout << "\nThe type of an int literal is adapted to the value"
			"The type of the integer literal is the first type in which the value can fit,\n"
			"and depends on the suffix and the numeric base.\n";
	pr_vst("0                    :", 0, "int");
	pr_vst("0xFFFF               :", 0xFFFF, "int");
	pr_vst("0X7fffffff           :", 0X7fffffff, "int");
	pr_vst("0xFFFFFFFF           :", 0xFFFFFFFF, "unsigned int ! Hex-literals and octal-literals are packed in an unsigned type if possible");
	pr_vst("4,294,967,295        :", 4294967295, "long int ! Decimal-literals are packed in an signed type");
	pr_vst("0x7FFFFFFFFFFFFFFF   :", 0x7FFFFFFFFFFFFFFF, "long int");
	pr_vst("0xFFFFFFFFFFFFFFFF   :", 0xFFFFFFFFFFFFFFFF, "unsigned long int");
	cout << "18446744073709551615 : size:" << sizeof 18446744073709551615 << " type:" << typeid(18446744073709551615).name() << " Switch to the next integer type 128 bit\n";
	pr_vst("0xFFFFFFFFFFFFFFFFF  :", 0xFFFFFFFFFFFFFFFFF, "If the value becomes to big, it is truncated. The compiler should produce a warning here!");

	cout << "\nLiterals with prefix l or L are never shorter than a long int. But may be unsigned!\n";
	pr_vst("0l:                  :", 0l);
	pr_vst("0x7FFFFFFFl:         :", 0x7FFFFFFFl);
	pr_vst("0xFFFFFFFFl:         :", 0xFFFFFFFFl);
	pr_vst("4,294,967,295l:      :", 4294967295l, "long int ! Decimal-literals are packed in an signed type");
	pr_vst("0x7FFFFFFFFFFFFFFFl: :", 0x7FFFFFFFFFFFFFFFl, "long int");
	pr_vst("0xFFFFFFFFFFFFFFFFl: :", 0xFFFFFFFFFFFFFFFFl, "unsigned long int");
	cout << "18446744073709551615l: size:" << sizeof 18446744073709551615l << " type:" << typeid(18446744073709551615l).name() << " Switch to the next integer type 128 bit\n";
	long int temps = 18446744073709551615l;
	pr_vst("long int temps = 18446744073709551615l          :", temps, "!!! The value is to large for a long int and thus truncated");
	unsigned long int tempu = 18446744073709551615l;
	pr_vst("unsigned long int tempu = 18446744073709551615l :", tempu, "But fits into a unsigned long int");

	cout << "\nLiterals with prefix ll or LL are never shorter than a long long int. But may be unsigned!\n";
	pr_vst("0ll                  :", 0ll);
	pr_vst("0x7FFFFFFFll         :", 0x7FFFFFFFll);
	pr_vst("0xFFFFFFFFll         :", 0xFFFFFFFFll);
	pr_vst("4,294,967,295ll      :", 4294967295ll, "long long int ! Decimal-literals are packed in an signed type");
	pr_vst("0x7FFFFFFFFFFFFFFFll :", 0x7FFFFFFFFFFFFFFFll);
	pr_vst("0xFFFFFFFFFFFFFFFFll :", 0xFFFFFFFFFFFFFFFFll, "unsigned long long int");
	cout << "18446744073709551615ll: size:" << sizeof 18446744073709551615ll << " type:" << typeid(18446744073709551615ll).name() << " Switch to the next integer type 128 bit\n";

	cout << "\nLiterals with prefix u or U are always unsigned\n";
	pr_vst("0u                   :", 0u);
	pr_vst("0x7FFFFFFFu          :", 0x7FFFFFFFu);
	pr_vst("0xFFFFFFFFu          :", 0xFFFFFFFFu);
	pr_vst("4,294,967,295u       :", 4294967295u, "unsigned int");
	pr_vst("0x7FFFFFFFFFFFFFFFu  :", 0x7FFFFFFFFFFFFFFFu);
	pr_vst("0xFFFFFFFFFFFFFFFFu  :", 0xFFFFFFFFFFFFFFFFu, "unsigned long long int");
	pr_vst("18446744073709551615u:", 18446744073709551615u, "Fits in the unsigned long int type!");

	cout << "\nLiterals with prefix ul or UL are never shorter than a long int and are unsigned\n";
	pr_vst("0u:                  :", 0ul);
	pr_vst("0x7FFFFFFFul         :", 0x7FFFFFFFul);
	pr_vst("0xFFFFFFFFul         :", 0xFFFFFFFFul);
	pr_vst("4,294,967,295ul      :", 4294967295ul, "unsigned long int");
	pr_vst("0x7FFFFFFFFFFFFFFFul :", 0x7FFFFFFFFFFFFFFFul);
	pr_vst("0xFFFFFFFFFFFFFFFFul :", 0xFFFFFFFFFFFFFFFFul, "unsigned long long int");
	pr_vst("18446744073709551615ul:", 18446744073709551615ul, "Fits in the unsigned long int type");

	cout << "\nLiterals with prefix ull or ULL are never shorter than a long long int and are unsigned\n";
	pr_vst("0ull                 :", 0ull);
	pr_vst("0x7FFFFFFFull        :", 0x7FFFFFFFull);
	pr_vst("0xFFFFFFFFull        :", 0xFFFFFFFFull);
	pr_vst("4,294,967,295ull     :", 4294967295ull, "unsigned long long int");
	pr_vst("0x7FFFFFFFFFFFFFFFull:", 0x7FFFFFFFFFFFFFFFull);
	pr_vst("0xFFFFFFFFFFFFFFFFull:", 0xFFFFFFFFFFFFFFFFull);
	pr_vst("18446744073709551615ull:",18446744073709551615ull,"Fits in the unsigned long long int type");

	cout << "\nThe prefix may consist of capital letters and minor letters and the order is not relevant.\n";
	pr_vst("0LLu                  :", 0LLu);
	pr_vst("0llU                  :", 0llu);
	pr_vst("0ULL                  :", 0ULL);

#if __cplusplus >= 201103L
	cout << "\n*** Fixed width integer types (C++11):\n"
	"Header <cstdint> offers fixed size integer types here some examples:\n";
	int8_t i8 = 0x30; uint8_t ui8 = 0x31; int16_t i16 = 12; uint16_t uint16 = 13;
	int32_t i32 = 14; uint32_t ui32 = 15; int64_t i64 = 16; uint64_t ui64 = 17;
	pr_vstmm("int8_t i8 = 0x30      :", i8, "This is an alias of signed char. The 'operator<<' interprets the values as character");
	pr_vstmm("uint8_t ui8 = 0x31    :", ui8, "This is an alias of unsigned char. The 'operator<<' interprets the values as character");
	pr_vstmm("int16_t i16 = 12      :", i16);
	pr_vstmm("uint16_t uint16 = 13  :", uint16);
	pr_vstmm("int32_t i32 = 14      :", i32);
	pr_vstmm("uint32_t ui32 = 15    :", ui32);
	pr_vstmm("int64_t i64 = 16      :", i64);
	pr_vstmm("uint64_t ui64 = 17    :", ui64);
	cout << "\nNote: there are more types available in <cstdint>\n";
#endif

	cout << "\n****** Floating Point Types ******\n";
	{
		float var1 = 0.0f; float var2 = 1.1f;
		pr_vvstmm("float:      ", var1, var2);
	}
	{
		double var1 = 0.0; double var2 = 1.1;
		pr_vvstmm("double:     ", var1, var2);
	}
	{
		long double var1 = 0.0; long double var2 = 1.1;
		pr_vvstmm("long double:", var1, var2);
	}
	cout << "\n*** Floating Point Literals\n"
			"Float literals without suffix are doubles.\n";
	pr_vst("0.0                 :", 0.0);
	pr_vst("1e-1                :", 1e-1);
	pr_vst(".1                  :", .1);

	cout << "\nSuffix f or F makes a float literal.\n";
	pr_vst("0.0F                :", 0.0F);
	pr_vst("1e-1f               :", 1e-1F);
	pr_vst(".1f                 :", .1f);

	cout << "\nSuffix l or L makes a long double literal.\n";
	pr_vst("0.0L                :", 0.0L);
	pr_vst("1e-1l               :", 1e-1L);
	pr_vst(".1L                 :", .1L);

	cout << "\n****** Pointer Types ******\n"
			"A pointer represents the address of an variable of type x\n";
	int i = 55;
	int* ip = &i;
	pr_vst("int* ip:", ip);
	cout << "void pointer can hold the value of any kind of other pointer\n";
	void* vp = ip;
	pr_vst("void* vp:", vp);
	cout << "Note: The 'operator<<' function interprets the most pointer types as the address where it points to.\n";
	cout << "\nMore about pointer: see also in Constness1, FunctionPointers, Lambdas and PointerToMember\n";

	cout << "\n****** Array Types ******\n";

	int ai[] {1, 2, 3};
	pr_vst("int ai[] {1, 2, 3}:", ai, "During output, the array is converted into a pointer and thus, the address is printed.");
	__extension__ int ai2[] {};
	pr_vst("int ai2[] {}      :", ai2);
	cout << "\nNote: Arrays are silently converted to pointers at the slightest occasion.\n"
			"During output with the output stream 'cout', the array is converted into a pointer. And thus for the most array types the address is printed.";
	cout << "\nMore about Arrays: see also in Arrays\n";

	cout << "\n****** C-strings ******\n"
			"c-strings are char arrays with the terminating 0 character\n";
	char cstr1[] {'c', '-', 's', 't', 'r', 'i', 'n', 'g', 's', '\0'};
	cout << "\nThe 'operator<<' function interprets char arrays\n"
			"as c-string and expects the terminating 0 character!\n"
			"cstr1=" << cstr1 << "\n";

	cout << "\nA string literal represents the const char array of the characters and the null character is silently appended.\n";
	pr_vst("\"abcd\"", "abcd");

	cout << "\nThe function 'operator<<' handles also the types car* and const char* as c-string\n";
	const char* cpc = "const c-string";
	pr_vst("const char* :", cpc);
	char* pc2 = cstr1;
	pr_vst("char*       :", pc2);

	cout << "\nThe same applies to arrays of signed chars and unsigned chars\n";
	signed char cstr2[] {'a', 'b', 'c', '\0'};
	pr_vst("signed char cstr2[]:", cstr2);
	unsigned char cstr3[] {'a', 'b', 'c', '\0'};
	pr_vst("unsigned char cstr3[]:", cstr3);

	cout << "\nA const char arrays can be initialized with string literal.\n";
	const char cchararr[] = "c-string: const char[]";
	pr_vst("const char[]:", cchararr);

	cout << "\nNote: Other pointer types are printed as address\n";
	const void* vpa = cpc;
	pr_vst("const void*:", vpa);

	cout << "\n*** Literals\n";

	pr_vst("\"s\"            :", "s", "char array");
	pr_vst("\"1234\"         :", "1234", "char array ");
#if __cplusplus >= 201103L
#endif
	pr_vst("L\"s\"           :", L"s", "wchar_t array");
#if __cplusplus >= 201103L
#endif
#if __cplusplus >= 201103L
	pr_vst("u8\"s\"          :", u8"s", "char array UTF8 string (C++11)");
	pr_vst("u\"s\"           :", u"s", "char16_t array UTF16 string (C++11)");
	pr_vst("U\"s\"           :", U"s", "char32_t array UTF32 string (C++11)");

	cout << "\nUTF Code points\n";
	cout << u8"You can use UTF Code points: \\u00E6, \\u00F8, \\u00e5.\n";
	cout << "Diplays:\n";
	cout << u8"You can use UTF Code points: \u00E6, \u00F8, \u00e5.\n";
	cout << "UTF8 are variable size strings!\n";
	pr_vst("u8\"\\u00F8\":", u8"\u00F8");
	pr_vst("\\u00F8:", "\u00F8");
	pr_vst("u8\"'\\u0430'\"", u8"'\u0430'");

	cout << "\nRaw strings can contain the '\"' and the '\\' character unescaped.\n"
			"Raw strings start with 'R\"(' and end with ')\"'.\n"
			"The start and end delimiter can be extended like:\n"
			"'R\"***(' ... ')***\"'\n";
	pr_vst("R\"(\"s\")\"       :", R"("s")", "char array raw string (C++11)");
	pr_vst("R\"**(12\\4)**\"  :", R"**(12\4)**", "char raw string array (C++11)");
	pr_vst("LR\"(s)\"        :", LR"(s)", "wchar_t array raw string (C++11)");
	pr_vst("u8R\"(s)\"       :", u8R"(s)", "char array UTF8 raw string (C++11)");
	pr_vst("uR\"(s)\"        :", uR"(s)", "char16_t array UTF16 raw string (C++11)");
	pr_vst("UR\"(s)\"        :", UR"(s)", "char32_t array UTF32 raw string (C++11)");
#endif

	cout << "\n****** Enumeration Types ******\n";
	{
		enum my_enum {a,b,c} var = a;
		pr_vst("enum my_enum {a,b,c} var = a:", var);
		cout << "Note: enums are implicitly converted to int for output\n";
	}

#if __cplusplus >= 201103L
	enum class my_enum_class {green, yellow, read} enclv = my_enum_class::green;
	cout << "enum class my_enum_class {green, yellow, read} enclv = my_enum_class::green:" << static_cast<int>(enclv) << " size:" << sizeof(my_enum_class) << " typeid:" << typeid(my_enum_class).name() << " (C++11)\n";
	cout << "Note: no 'operator<<' available for enum class. Convert to integer for output.\n";
#endif

	cout <<"\n****** Special Types ******\n";
	cout << "The 'std::size_t' is used to express sizes of objects and types.\n"
			"It is the return type of operator 'sizeof'.";
	pr_st<std::size_t>("std::size_t    :", "Alias of unsigned long");
	{
		auto var = sizeof(int);
		pr_vstmm("auto var = sizeof(int) :", var);
	}
	cout << "\n";
	pr_st<void>("void           :", "The void type does not represent any type.");
	//void v; //error: variable or field ‘v’ declared void
	cout << "Note: variables of type void can not be declared!\n";
	cout << "\n";
	int sa = 55; int sb = 56;
	std::ptrdiff_t ptrdiff = &sa - &sb;
	pr_vstmm("std::ptrdiff_t :", ptrdiff, "The pointer difference type. Alias of long int.");
	cout << "\n";
#if __cplusplus >= 201103L
	pr_st<std::nullptr_t>("std::nullptr_t :", "is the type of the null pointer literal");
	cout << "typeid(nullptr).name(): " << typeid(nullptr).name() << "\n";
	cout << "Note: variables of type std::nullptr_t can be declared. But no function ‘operator<<’ is available\n";
	cout << "can assign std::nullptr_t to every pointer type\n";
	std::nullptr_t nptr = nullptr;
	int* nptr1 = nptr;
	cout << "nptr1:" << nptr1 << "\n";
	cout << "Note: You can not assign std::nullptr_t to reference types.\n";
	//int& nptr2 = nptr; //error: invalid initialization of reference of type ‘int&’ from expression of type ‘std::nullptr_t’
#endif
	cout << "\n";
	pr_vst("NULL           :", NULL, "NULL is a macro and is the long int literal with value 0");

	cout << "\n****** Reference Types ******\n";
	cout << "In an expression, the reference is silently converted to the value as usual in C++.\n"
			"sizeof r gives mainly the size of the thing where it points to\n";
	int iir = 56;
	int& ir = iir;
	cout << "int& ir:" << ir << " sizeof ir:" << sizeof ir << " typeid:" << typeid(ir).name()
			<< "\nThus no direct output of the reference properties is possible, so use address\n";
	cout << "&ir:" << &ir << " size:" << sizeof &ir << " typeid:" << typeid(&ir).name() << " (This is the pointer type)\n";

	cout << "\n****** User Defined Type struct ******\n";
	struct str {int a; char b;};
	cout << "struct str {int a, car b} sizeof(str):" << sizeof(str) << " typeid:" << typeid(str).name() << "\n";

	cout << "\n****** User Defined Type class ******\n";
	class cl {};
	cout << "class cl {}: size:                                      " << sizeof(cl) << " typeid:" << typeid(cl).name() << "\n";
	class cld { char c; };
	cout << "class cld { char c; }: size:                            " << sizeof(cld) << " typeid:" << typeid(cld).name() << "\n";
	class cle { char c1, c2; };
	cout << "class cle { char c1, c2; }: size:                       " << sizeof(cle) << " typeid:" << typeid(cle).name() << "\n";
	cout << "\n";
	class vcl { public: virtual ~vcl() {} };
	cout << "class vcl { public: virtual ~vcl() {} }: size:          " << sizeof(vcl) << " typeid:" << typeid(vcl).name() << "\n";
	class vcld { char c; public: virtual ~vcld() {} };
	cout << "class vcld { char c; public: virtual ~vcld() {} }: size:" << sizeof(vcld) << " typeid:" << typeid(vcld).name() << "\n";
	cout << "\n";
	cout << "std::string                                      : size:" << sizeof(std::string) << " typeid:" << typeid(std::string).name() << "\n";

	cout << "\n****** User Defined Type union ******\n";
	union uni {int a; char b;};
	cout << "union uni {int a; char b;} sizeof(uni):" << sizeof(uni) << " typeid:" << typeid(uni).name() << "\n";

	cout << endl;
	return 0;
}
