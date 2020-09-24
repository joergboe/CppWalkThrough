/*
 * Internal types and literals
 */

#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

int main() {
	cout << "Print sizes and typeinfos for internal types and literals\n";

	cout << "\nBool:\n";
	bool ba = false; bool bb = true;
	cout << "bool:" << ba << " " << bb << " size:" << sizeof(bool) << " typeid:" << typeid(bool).name() << "\n";

	cout << "\nChars:\n";
	char ca = 'a'; char cb = 'b';
	cout << "char:         " << ca << " " << cb << " size:" << sizeof(char) << " typeid:" << typeid(char).name() << "\n";
	signed char sca = 'a'; signed char scb = 'b';
	cout << "signed char:  " << sca << " " << scb << " size:" << sizeof(signed char) << " typeid:" << typeid(signed char).name() << "\n";
	unsigned char uca = 'a'; unsigned char ucb = 'b';
	cout << "unsigned char:" << uca << " " << ucb << " size:" << sizeof(unsigned char) << " typeid:" << typeid(unsigned char).name() << "\n";
	wchar_t wca = L'0'; wchar_t wcb = L'1';
	cout << "wchar_t:      " << wca << " " << wcb << " size:" << sizeof(wchar_t) << " typeid:" << typeid(wchar_t).name() << "\n";
#if __cplusplus >= 201103L
	char16_t ca16 = u'\x0030'; char16_t cb16 = u'1';
	cout << "char16_t:     " << ca16 << " " << cb16 << " size:" << sizeof(char16_t) << " typeid:" << typeid(char16_t).name() << "\n";
	char32_t ca32 = U'0'; char32_t cb32 = U'1';
	cout << "char32_t:     " << ca32 << " " << cb32 << " size:" << sizeof(char32_t) << " typeid:" << typeid(char32_t).name() << "\n";
#endif
	cout << "\nNote: char, signed char and unsigned char are tree different types.\nIf the char type is signed or unsigned depends on the implementation.\n";

	cout << "\nIntegers:\n";
	int ia = 0; int ib = 1;
	cout << "int:                   " << ia << " " << ib << " size:" << sizeof(int) << " typeid:" << typeid(int).name() << "\n";
	signed int sia = 0; signed int sib = 1;
	cout << "signed int:            " << sia << " " << sib << " size:" << sizeof(signed int) << " typeid:" << typeid(signed int).name() << "\n";
	unsigned int uia = 0u; unsigned int uib = 1U;
	cout << "unsigned int:          " << uia << " " << uib << " size:" << sizeof(unsigned int) << " typeid:" << typeid(unsigned int).name() << "\n";

	short int sa = 0; short int sb = 1;
	cout << "short int:             " << sa << " " << sb << " size:" << sizeof(short int) << " typeid:" << typeid(short int).name() << "\n";
	signed short int ssa = 0; signed short int ssb = 1;
	cout << "signed short int:      " << ssa << " " << ssb << " size:" << sizeof(signed short int) << " typeid:" << typeid(signed short int).name() << "\n";
	unsigned short int usa = 0u; unsigned short int usb = 1u;
	cout << "unsigned short int:    " << usa << " " << usb << " size:" << sizeof(unsigned short int) << " typeid:" << typeid(unsigned short int).name() << "\n";

	long int la = 0l; long int lb = 1l;
	cout << "long int:              " << la << " " << lb << " size:" << sizeof(long int) << " typeid:" << typeid(long int).name() << "\n";
	signed long int sla = 0l; signed long int slb = 1l;
	cout << "signed long int:       " << sla << " " << slb << " size:" << sizeof(signed long int) << " typeid:" << typeid(signed long int).name() << "\n";
	unsigned long int ula = 0lu; unsigned long int ulb = 1lu;
	cout << "unsigned long int:     " << ula << " " << ulb << " size:" << sizeof(unsigned long int) << " typeid:" << typeid(unsigned long int).name() << "\n";

	long long int lla = 0ll; long long int llb = 1ll;
	cout << "long long int:         " << lla << " " << llb << " size:" << sizeof(long long int) << " typeid:" << typeid(long long int).name() << "\n";
	signed long long int slla = 0ll; signed long long int sllb = 1ll;
	cout << "signed long long int:  " << slla << " " << sllb << " size:" << sizeof(signed long long int) << " typeid:" << typeid(signed long long int).name() << "\n";
	unsigned long long int ulla = 0llu; unsigned long long int ullb = 1llu;
	cout << "unsigned long long int:" << ulla << " " << ullb << " size:" << sizeof(unsigned long long int) << " typeid:" << typeid(unsigned long long int).name() << "\n";

	cout << "\nNote: The signed types are aliases.\n";
	cout << "\nFloating Point:\n";
	float fa = 0.0; float fb = 1.1;
	cout << "float:      " << fa << " " << fb << " size:" << sizeof(float) << " typeid:" << typeid(float).name() << "\n";
	double da = 0.0; double db = 1.1;
	cout << "double:     " << da << " " << db << " size:" << sizeof(double) << " typeid:" << typeid(double).name() << "\n";
	long double lda = 0.0; long double ldb = 1.1;
	cout << "long double:" << lda << " " << ldb << " size:" << sizeof(long double) << " typeid:" << typeid(long double).name() << "\n";

	cout << "\nPointer:\n";
	const char* pa = "a"; const char* pb = "b";
	cout << "const char*:" << pa << " " << pb << " size:" << sizeof(const char*) << " typeid:" << typeid(const char*).name() << "\n";
	const void* vpa = pa; const void* vpb = pb;
	cout << "const void*:" << vpa << " " << vpb << " size:" << sizeof(const void*) << " typeid:" << typeid(const void*).name() << "\n";
	cout << "char*: size:" << sizeof(char*) << " typeid:" << typeid(char*).name() << "\n";
	cout << "void*: size:" << sizeof(void*) << " typeid:" << typeid(void*).name() << "\n";

	cout << "\nArray:\n";
	int ai[] {1, 2, 3};
	cout << "int ai[] {1, 2, 3}:" << ai << " size:" << sizeof(ai) << " typeid:" << typeid(ai).name() << "\n";
	int ai2[] {};
	cout << "int ai2[] {}:" << ai2 << " size:" << sizeof(ai2) << " typeid:" << typeid(ai2).name() << "\n";
	cout << "Arrays are silently converted to pointers at the slightest occasion\n";

	cout <<"\nVoid type:\n";
	//void v;
	cout << "void:" << " size:" << sizeof(void) << " typeid:" << typeid(void).name() << "\n";

	enum en {a, b,c} ena = a;
	cout << "enum:" << ena << " size:" << sizeof(en) << " typeid:" << typeid(en).name() << "\n";

	cout << "\nReference types\n";
	int& ir = ia;
	cout << "int& ir:" << ir << " size:" << sizeof ir << " typeid:" << typeid(ir).name()
		<< "\nIn an expression, the reference is silently converted to the value as usual in C++.\n"
			"sizeof r gives mainly the size of the thing where it points to\n";
	cout << "&ir:" << &ir << " size:" << sizeof &ir << " typeid:" << typeid(&ir).name() << "\n";

	cout << "\nClasses:\n";
	class cl {};
	cout << "class cl {}: size:                                      " << sizeof(cl) << " typeid:" << typeid(cl).name() << "\n";
	class cld { char c; };
	cout << "class cld { char c; }: size:                            " << sizeof(cld) << " typeid:" << typeid(cld).name() << "\n";
	class cle { char c1, c2; };
	cout << "class cle { char c1, c2; }: size:                       " << sizeof(cle) << " typeid:" << typeid(cle).name() << "\n";
	class vcl { public: virtual ~vcl() {} };
	cout << "class vcl { public: virtual ~vcl() {} }: size:          " << sizeof(vcl) << " typeid:" << typeid(vcl).name() << "\n";
	class vcld { char c; public: virtual ~vcld() {} };
	cout << "class vcld { char c; public: virtual ~vcld() {} }: size:" << sizeof(vcld) << " typeid:" << typeid(vcld).name() << "\n";
	cout << "string                                           : size:" << sizeof(string) << " typeid:" << typeid(string).name() << "\n";

	cout << "\n******Literals*********\nBool:\n";
	cout << "true: size:" << sizeof(true) << " typeid:" << typeid(true).name() << "\n";

	cout << "\nChars\n";
	cout << "'a': size: " << sizeof('a') << " typeid:" << typeid('a').name() << "\n";
	cout << "L'a': size:" << sizeof(L'a') << " typeid:" << typeid(L'a').name() << "\n";
#if __cplusplus >= 201103L
	cout << "u'a': size:" << sizeof(u'a') << " typeid:" << typeid(u'a').name() << "\n";
	cout << "U'a': size:" << sizeof(U'a') << " typeid:" << typeid(U'a').name() << "\n";
#endif

	cout << "\nIntegers:\n";
	cout << "0:                   size:" << sizeof(0) << " typeid:" << typeid(0).name() << "\n";
	cout << "0xFFFF:              size:" << sizeof(0xFFFF) << " typeid:" << typeid(0xFFFF).name() << "\n";
	cout << "0x7FFFFFFF:          size:" << sizeof(0x7FFFFFFF) << " typeid:" << typeid(0x7FFFFFFF).name() << "\n";
	cout << "0xFFFFFFFF:          size:" << sizeof(0xFFFFFFFF) << " typeid:" << typeid(0xFFFFFFFF).name() << "\n";
	cout << "4,294,967,295: size:" << sizeof(4294967295) << " typeid:" << typeid(4294967295).name() << "\n";
	cout << "0x7FFFFFFFFFFFFFFF:  size:" << sizeof(0x7FFFFFFFFFFFFFFF) << " typeid:" << typeid(0x7FFFFFFFFFFFFFFF).name() << "\n";
	cout << "0xFFFFFFFFFFFFFFFF:  size:" << sizeof(0xFFFFFFFFFFFFFFFF) << " typeid:" << typeid(0xFFFFFFFFFFFFFFFF).name() << "\n";
	cout << "0xFFFFFFFFFFFFFFFFF: size:" << sizeof(0xFFFFFFFFFFFFFFFFF) << " typeid:" << typeid(0xFFFFFFFFFFFFFFFFF).name() << "\n";
	cout << "\n";
	cout << "0l:                  size:" << sizeof(0l) << " typeid:" << typeid(0l).name() << "\n";
	cout << "0ll:                 size:" << sizeof(0ll) << " typeid:" << typeid(0ll).name() << "\n";
	cout << "0x7FFFFFFFl:         size:" << sizeof(0x7FFFFFFFl) << " typeid:" << typeid(0x7FFFFFFFl).name() << "\n";
	cout << "0xFFFFFFFFl:         size:" << sizeof(0xFFFFFFFFl) << " typeid:" << typeid(0xFFFFFFFFl).name() << "\n";
	cout << "0x7FFFFFFFll:        size:" << sizeof(0x7FFFFFFFll) << " typeid:" << typeid(0x7FFFFFFFll).name() << "\n";
	cout << "0xFFFFFFFFll:        size:" << sizeof(0xFFFFFFFFll) << " typeid:" << typeid(0xFFFFFFFFll).name() << "\n";
	cout << "0x7FFFFFFFFFFFFFFFll:size:" << sizeof(0x7FFFFFFFFFFFFFFFll) << " typeid:" << typeid(0x7FFFFFFFFFFFFFFFll).name() << "\n";
	cout << "0xFFFFFFFFFFFFFFFFll:size:" << sizeof(0xFFFFFFFFFFFFFFFFll) << " typeid:" << typeid(0xFFFFFFFFFFFFFFFFll).name() << "\n";
	cout << "\n";
	cout << "0u:                  size:" << sizeof(0u) << " typeid:" << typeid(0u).name() << "\n";
	cout << "0ul:                 size:" << sizeof(0ul) << " typeid:" << typeid(0ul).name() << "\n";
	cout << "0ull:                size:" << sizeof(0ull) << " typeid:" << typeid(0ull).name() << "\n";
	cout << "0x7FFFFFFFul:        size:" << sizeof(0x7FFFFFFFul) << " typeid:" << typeid(0x7FFFFFFFul).name() << "\n";
	cout << "0xFFFFFFFFul:        size:" << sizeof(0xFFFFFFFFul) << " typeid:" << typeid(0xFFFFFFFFul).name() << "\n";
	cout << "0x7FFFFFFFFFFFFFFFull:size:" << sizeof(0x7FFFFFFFFFFFFFFFull) << " typeid:" << typeid(0x7FFFFFFFFFFFFFFFull).name() << "\n";
	cout << "0xFFFFFFFFFFFFFFFFull:size:" << sizeof(0xFFFFFFFFFFFFFFFFull) << " typeid:" << typeid(0xFFFFFFFFFFFFFFFFull).name() << "\n";

	cout << "\nFloats\n";
	cout << "0.0                 :size:" << sizeof(0.0) << " typeid:" << typeid(0.0).name() << "\n";
	cout << "1e-1                :size:" << sizeof(1e-1) << " typeid:" << typeid(1e-1).name() << "\n";
	cout << "0.0F                :size:" << sizeof(0.0F) << " typeid:" << typeid(0.0F).name() << "\n";
	cout << "1e-1F               :size:" << sizeof(1e-1F) << " typeid:" << typeid(1e-1F).name() << "\n";
	cout << "0.0L                :size:" << sizeof(0.0L) << " typeid:" << typeid(0.0L).name() << "\n";
	cout << "1e-1L               :size:" << sizeof(1e-1L) << " typeid:" << typeid(1e-1L).name() << "\n";

	cout << "\nStrings\n";
	cout << "char array \"s\"               :size:" << sizeof("s") << " typeid:" << typeid("s").name() << " " << "s" << "\n";
	cout << "char array \"1234\"            :size:" << sizeof("1234") << " typeid:" << typeid("1234").name() << " " << "1234" << "\n";
#if __cplusplus >= 201103L
	cout << "raw char array R\"(s)\"        :size:" << sizeof(R"(s)") << " typeid:" << typeid(R"(s)").name() << " " << R"(s)" << "\n";
	cout << "raw char array R\"**(1234)**\" :size:" << sizeof(R"**(1234)**") << " typeid:" << typeid(R"**(1234)**").name() << " " << R"**(1234)**" << "\n";
#endif
	cout << "wchar_t array  L\"s\"          :size:" << sizeof(L"s") << " typeid:" << typeid(L"s").name() << " " << L"s" << "\n";
#if __cplusplus >= 201103L
	cout << "wchar_t array  LR\"(s)\"       :size:" << sizeof(LR"(s)") << " typeid:" << typeid(LR"(s)").name() << " " << LR"(s)" << "\n";
#endif
#if __cplusplus >= 201103L
	cout << "UTF8      u8\"s\"              :size:" << sizeof(u8"s") << " typeid:" << typeid(u8"s").name() << " " << u8"s" << "\n";
	cout << "UTF8 raw  u8R\"(s)\"           :size:" << sizeof(u8R"(s)") << " typeid:" << typeid(u8R"(s)").name() << " " << u8R"(s)" << "\n";
	cout << "UTF16     u\"s\"               :size:" << sizeof(u"s") << " typeid:" << typeid(u"s").name() << " " << u"s" << "\n";
	cout << "UTF16 raw uR\"(s)\"            :size:" << sizeof(uR"(s)") << " typeid:" << typeid(uR"(s)").name() << " " << uR"(s)" << "\n";
	cout << "UTF32     U\"s\"               :size:" << sizeof(U"s") << " typeid:" << typeid(U"s").name() << " " << U"s" << "\n";
	cout << "UTF32 raw UR\"(s)\"            :size:" << sizeof(UR"(s)") << " typeid:" << typeid(UR"(s)").name() << " " << UR"(s)" << "\n";

	cout << "\nUTF Code points\n";
	cout << u8"Vokale in Dänisch: a, e, i, o, u, \\u00E6, \\u00F8, \\u00e5 und y.\n";
	cout << u8"Vokale in Dänisch: a, e, i, o, u, \u00E6, \u00F8, \u00e5 und y.\n";
	cout << u8"\\u0430\n";
	cout << u8"\u0430" << " size:" << sizeof(u8"\u0430") << "\n";
#endif

#if __cplusplus >= 201103L
	cout << "\nUser defined types:\n";
	//cout << "string literal \"s\"s         :size:" << sizeof("s"s) << " typeid:" << typeid("s"s).name() << " " << "s"s << "\n";
#endif

#if __cplusplus >= 201103L
	auto s = sizeof(bool);
	cout << "\nTypeid of sizeof:" << typeid(s).name() << "\n";
#endif

	cout << endl;

	cout << "string " << sizeof(string) << endl;
	return 0;
}
