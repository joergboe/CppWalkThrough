/*
 * Demonstration enum class and enum
 */

#include <iostream>
#include <typeinfo>

using namespace std;

//Enum class used later
enum class FlagEnum: char { none=0, flag1=1, flag2=2, flag3=4 };
//Must define constexpr function before usage:
//error: ‘constexpr FlagEnum operator|(FlagEnum, FlagEnum)’ used before its definition
constexpr FlagEnum operator|(FlagEnum a, FlagEnum b) {
	return static_cast<FlagEnum>(static_cast<char>(a) | static_cast<char>(b));
}

int main() {
	cout << "\n****** Type enum class ******\n";
	cout << "Define simple enum class (scoped enum):\n";
	enum class Color { red, orange, yellow, green, blue=10, purple } color{};
	cout << "There may be gaps in the sequence of the enumerations\n";
	cout << "No assignment to int possible - use explicit cast!\n";
	int c = static_cast<int>(color);
	cout << "Default value: " << c << endl;
	cout << "Assignment requires qualification. enum class does not inject the names of the enumerations into the enclosing namespace\n";
	//color = purple; //error: ‘purple’ was not declared in this scope
	color = Color::purple;
	cout << "Value of purple: " << static_cast<int>(color) << endl;
	cout << "No direct conversion from int to Color. Use functional cast! \n";
	//color = 4; //error: cannot convert ‘int’ to ‘main()::Color’ in assignment
	color = Color(4);
	cout << "Value of color: " << static_cast<int>(color) << endl;
	cout << "Note: The result of such an operation may be not a enumeration value!" << endl;

	cout << "\ntype of color: " << typeid(color).name() << " sizeof: " << sizeof color << endl;
	cout << "type of Color: " << typeid(Color).name() << " sizeof: " << sizeof color << endl;
	cout << "type of Color::orange: " << typeid(Color::orange).name() << " sizeof: " << sizeof color << endl;

	cout << "\nThe underlying default type of enum class is int. The starting enumeration has default value 0.\n"
			"This can be changed in enum definition with initializer.\n";
	enum class TrafficLight : char { red=6, yellow, green };
	TrafficLight trafficLight{};
	cout << "type of TrafficLight: " << typeid(trafficLight).name() << " size: " << sizeof trafficLight << endl;
	cout << "!!!Default value of trafficLight: " << int(trafficLight) << " !!!\n"
			"Note: The default value is alway 0" << endl;
	trafficLight = TrafficLight::green;
	cout << "Value of red: " << static_cast<int>(TrafficLight::red) <<  " Value of green: " << int(trafficLight) << endl;

	cout << "\nOperations: no increment, decrement... But compare of values of the same type is possible\n";
	TrafficLight trafficLight2{TrafficLight::red};
	//++trafficLight; //error: no match for ‘operator++
	//TrafficLight tlx = trafficLight & trafficLight2; //error: no match for ‘operator&’ (operand types are ‘main()::TrafficLight’ and ‘main()::TrafficLight’)
	//bool x = color == trafficLight; //error: no match for ‘operator==’ (operand types are ‘main()::Color’ and ‘main()::TrafficLight’)’
	cout << boolalpha << "trafficLight == trafficLight2 : " << (trafficLight == trafficLight2) << endl;
	cout << "trafficLight > trafficLight2 : " << (trafficLight > trafficLight2) << endl;
	cout << "No 'operator<<' available!\n";
	TrafficLight tly(TrafficLight(20));
	cout << "\nThere is no range check! So this is possible TrafficLight tly(TrafficLight(20)); Value of tly: " << static_cast<int>(tly) << endl;


	cout << "\n****** Type enum (unscoped enumeration) ******\n";
	cout << "- The underlying type may be defined (since c++11) in the declaration."
			"- Underlying type is determined from the compiler implementation and depends on the implementation.\n"
			"- Namespace pollution: all enumerations are inserted into the enclosing namespace.\n"
			"- Each enumerator is associated with a value of the underlying type.\n"
			"- Each enumerator value may be defined with an initializer\n"
			"- If no initializer is given the enumeration values start with 0 and are incremented by 1 for each successor.\n"
			"- The sequence of the enumeration values may have gaps an there might be duplicate values.\n"
			"- Values of unscoped enumeration type are implicitly-convertible to integral types.\n"
			"- Values of integer, floating-point, and enumeration types can be converted by static_cast or explicit cast, to any enumeration type.\n"
			"The result of such an operation may not be an enumeration value.\n";
	enum Enum1: unsigned char { item1=1, item2, item3 } enum1{};
	//enum Enum2 { item1, item2, item3 } enum2{}; //error: redeclaration of ‘item1’
	enum Enum2 { enum2_item1, enum2_item2, enum2_item3 } enum2{enum2_item2};
	Enum2 enum2Default{};
	cout << "type of enum1 enum2 : " << typeid(enum1).name() << " " << typeid(enum2).name() << " size: " << sizeof enum1 << endl;
	cout << "Default value enum1: " << enum1 << " enum2Default: " << enum2Default << " Default is always 0!"<< endl;
	cout << "\nimplicit conversion to underlying integral type possible\n";
	unsigned char c1 = enum1;
	int e2 = enum2;
	cout << "numerical representation of c1 is: " << static_cast<int>(c1) << " e2: " << e2 << endl;
	cout << "Initialization from initializer list:\n";
	Enum2 enum2x{enum2_item1};
	cout << "enum2x: " << int(enum2x) << endl;
	//Enum2 enum2y{2};
	//Enum2 enum2z{-1};

	cout << "\nDirect assignment with type mismatch is not possible; like : enum1 = enum2_item3;\n"
	//enum1 = enum2_item3; //error: cannot convert ‘main()::Enum2’ to ‘main()::Enum1’ in assignment
			"But implicit conversion can make trouble; like\n";
	enum1 = item1;
	if (enum1 == enum2_item2)
		cout << "Comparison enum1 == enum2_item2 evaluates to true: Wrong types are compared!\n"
				"But implementations can issue warnings (gcc: -Wenum-compare)\n";
	cout << "No direct arithmetic operations possible\n";
	//++enum1; //error: no match for ‘operator++’ (operand type is ‘main()::Enum1’)
	cout << "No direct conversion from int like: enum1 = Enum1{1} or enum2 = Enum2{1}\n";
	//enum1 = Enum1{1}; //error: invalid conversion from ‘int’ to ‘main()::Enum1’ [-fpermissive]
	//enum2 = Enum2{1}; //error: invalid conversion from ‘int’ to ‘main()::Enum1’ [-fpermissive]
	cout << "\nBut possible is cast like: enum2 = Enum2(1)\n";
	enum2 = Enum2(1);
	cout << "enum2: " << enum2 << endl;
	cout << "\n or cast like: enum1 = static_cast<Enum1>(2);\n";
	enum1 = static_cast<Enum1>(2);
	cout << "enum1: " << enum1 << endl;
	cout << "\nBut if the value is outside of the range (1..3) the result may be undefined\n";
	enum1 = static_cast<Enum1>('A');
	cout << hex << "enum1: 0x" << enum1 << dec << endl;

	cout << "\n****** Anonymous Enumeration Types ******\n"
			"Anonymous enums deliver a set of constants like: enum { const1=1, const2, const3, const4 }\n";
	enum { const1=1, const2, const3, const4 };
	cout << "const1=" << const1 << ", const2=" << const2 <<", const3=" << const3 << ", const4=" << const4 << "\n";
	cout << "Type const1: " << typeid(const1).name() << endl;

	cout << "\nBut not possible with enum class\n";
	//enum class { const1=1, const2, const3, const4 } var; //error: unnamed scoped enum is not allowed


	cout << "\n****** Opaque enum ******\n"
			"Opaque enum declaration for an unscoped enumeration must specify the name and the underlying type (since c++11)\n";
	enum Opaque : int;
	enum Opaque : int { oa, ob, oc=10, od=ob+oc, oe=1} opaqueEnum;
	opaqueEnum = Opaque(0);
	cout << "opaqueEnum: " << opaqueEnum << endl;
	cout << "oa=" << oa << " ob=" << ob << " oc=" << oc << " od=" << od << " oe=" << oe << endl;

	cout << "\n****** Combination of enumerations ******\n"
			"Simple enums can be combined like: enum1 = static_cast<Enum1>(item1 | item2)\n";
	enum1 = static_cast<Enum1>(item1 | item2);
	cout << "enum1: " << enum1 << endl;
	cout << "This is in fact a conversation to int and then a cast to the enum type\n";
	cout << "type of item1 | item2 is: " << typeid(item1 | item2).name() << "\n";

	cout << "\nTo combine enum class, you may define operator functions see 'operator|' for type FlagEnum\n";
	FlagEnum fe = FlagEnum::flag1 | FlagEnum::flag2;
	cout << "fe: " << static_cast<int>(fe) << endl;
	cout << "Constexpr can be used in const expressions\n";
	switch (fe) {
	case FlagEnum::flag1:
		cout << "FlagEnum::flag1\n";
		break;
	case FlagEnum::flag2:
		cout << "FlagEnum::flag2\n";
		break;
	case FlagEnum::flag3:
		cout << "FlagEnum::flag3\n";
		break;
	case FlagEnum::flag1 | FlagEnum::flag2:
		cout << "Combined FlagEnum::flag1 | FlagEnum::flag2\n"
				"The usage of combined enums in a switch statement provokes a warning from -Wswitch (gcc)\n";
		break;
	case FlagEnum::none:
		cout << "FlagEnum::none\n";
		break;
	}
	cout << "Type: " << typeid(FlagEnum::flag1 | FlagEnum::flag2).name() << " size: " << sizeof(FlagEnum::flag1 | FlagEnum::flag2) << endl;

	enum Aliasenum { myconst1=1, myconst2, myconst3=2, myconst4=2 } aliasenum = {};
	cout << "Default value of Aliasenum: " << aliasenum << endl
			<< "the values: " << myconst1 << " " << myconst2 << " " << myconst3 << " " << myconst4 << endl;

	cout << "END!" << endl;
	return 0;
}
