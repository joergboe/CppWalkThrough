/*
 * Demonstration enum class and enum
 */

#include <iostream>
#include <typeinfo>

using namespace std;

//Enum class used later
enum class FlagEnum: char;
enum class FlagEnum: char { none=0, flag1=1, flag2=2, flag3=4 };
constexpr FlagEnum operator|(FlagEnum a, FlagEnum b);
//Must define constexpr function before usage:
//error: ‘constexpr FlagEnum operator|(FlagEnum, FlagEnum)’ used before its definition
constexpr FlagEnum operator|(FlagEnum a, FlagEnum b) {
	return static_cast<FlagEnum>(static_cast<char>(a) | static_cast<char>(b));
}

int main() {
	cout << "\n*** Enum Class ***\n";
	cout << "Define simple enum class:\n";
	enum class Color { red, orange, yellow, green, blue=10, purple } color{};
	cout << "type of color: " << typeid(color).name() << " sizeof: " << sizeof color << endl;
	cout << "No assignment to int possible; use explicit cast!\n";
	int c = static_cast<int>(color);
	cout << "Default value: " << c << endl;
	cout << "Assignment requires qualification. enum class does not inject the names of the enumerations into the enclosing namespace\n";
	//color = purple; //error: ‘purple’ was not declared in this scope
	color = Color::purple;
	cout << "Value of purple: " << static_cast<int>(color) << endl;
	cout << "No direct conversion from int to Color. Use functional cast!\n";
	//color = 4; //error: cannot convert ‘int’ to ‘main()::Color’ in assignment
	color = Color(4);
	cout << "Value of color: " << static_cast<int>(color) << endl;

	cout << "The underlying default type of enum class is int. The starting enumeration has default value 0.\n"
			"This can be changed in enum definition\n";
	enum class TrafficLight : char { red=6, yellow, green };
	TrafficLight trafficLight{};
	cout << "type of TrafficLight: " << typeid(trafficLight).name() << " size: " << sizeof trafficLight << endl;
	cout << "!!!Default value of trafficLight: " << int(trafficLight) << " !!! Default is alway 0" << endl;
	trafficLight = TrafficLight::green;
	cout << "Value of green: " << int(trafficLight) << endl;

	cout << "Operations: no increment, decrement... But compare of values of the same type is possible\n";
	TrafficLight trafficLight2{TrafficLight::red};
	//++trafficLight; //error: no match for ‘operator++
	//TrafficLight tlx = trafficLight & trafficLight2; //error: no match for ‘operator&’ (operand types are ‘main()::TrafficLight’ and ‘main()::TrafficLight’)
	//bool x = color == trafficLight; //error: no match for ‘operator==’ (operand types are ‘main()::Color’ and ‘main()::TrafficLight’)’
	cout << boolalpha << "trafficLight == trafficLight2 : " << (trafficLight == trafficLight2) << endl;
	cout << "trafficLight > trafficLight2 : " << (trafficLight > trafficLight2) << endl;
	TrafficLight tly(TrafficLight(20));
	cout << "There is no range check! So this is possible TrafficLight tly(TrafficLight(20)); Value of tly: " << static_cast<int>(tly) << endl;

	cout << "\n*** Simple enum ***\n";
	cout << "Underlying type is determined or may be defined\n"
			"Namespace pollution: all enumerations are inserted into namespace:\n";
	enum Enum1: unsigned char { item1=1, item2, item3 } enum1{};
	//enum Enum2 { item1, item2, item3 } enum2{}; //error: redeclaration of ‘item1’
	enum Enum2 { enum2_item1, enum2_item2, enum2_item3 } enum2{enum2_item2};
	Enum2 enum2Default{};
	cout << "type of enum1 enum2 : " << typeid(enum1).name() << " " << typeid(enum2).name() << " size: " << sizeof enum1 << endl;
	cout << "Default value enum1: " << enum1 << " enum2Default: " << enum2Default << " Default is always 0!"<< endl;
	cout << "implicit conversion to /underlying/integral types possible\n";
	unsigned char c1 = enum1;
	int e2 = enum2;
	cout << "c1: " << static_cast<int>(c1) << " e2: " << e2 << endl;
	cout << "Direct assignment with type mismatch is not possible; like : enum1 = enum2_item3;\n"
	//enum1 = enum2_item3; //error: cannot convert ‘main()::Enum2’ to ‘main()::Enum1’ in assignment
			"But implicit conversion can make trouble; like\n";
	enum1 = item1;
	if (enum1 == enum2_item2)
		cout << "Comparison enum1 == enum2_item2 evaluates to true: Wrong types are compared!\n";
	cout << "No direct arithmetic operations possible\n";
	//++enum1; //error: no match for ‘operator++’ (operand type is ‘main()::Enum1’)
	cout << "No direct conversion from int like: enum1 = Enum1{1}\n";
	//enum1 = Enum1{1}; //error: invalid conversion from ‘int’ to ‘main()::Enum1’ [-fpermissive]
	cout << "But possible is cast like\n";
	enum2 = Enum2(1);
	cout << "enum2: " << enum2 << endl;
	enum1 = static_cast<Enum1>(2);
	cout << "enum1: " << enum1 << endl;
	cout << "But if the value is outside of the range (1..3) the result may be undefined\n";
	enum1 = static_cast<Enum1>('A');
	cout << hex << "enum1: 0x" << enum1 << dec << endl;

	cout << "\n*** Anonymous Enum ***\n"
			"Anonymous enums deliver a set of constants\n";
	enum { const1=1, const2, const3, const4 };
	cout << "const1=" << const1 << ", const2=" << const2 <<", const3=" << const3 << ", const4=" << const4 << "\n";
	cout << "Type const1: " << typeid(const1).name() << endl;

	cout << "\n*** Combination of enumerations ***\n"
			"Simple enums can be combined like\n";
	enum1 = static_cast<Enum1>(item1 | item2);
	cout << "enum1: " << enum1 << endl;
	cout << "To combine enum class, you may define operator functions: like\n";
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
		cout << "Combined FlagEnum::flag1 | FlagEnum::flag2\n";
		break;
	case FlagEnum::none:
		cout << "FlagEnum::none\n";
		break;
	}
	cout << "Type: " << typeid(FlagEnum::flag1 | FlagEnum::flag2).name() << " size: " << sizeof(FlagEnum::flag1 | FlagEnum::flag2) << endl;
	cout << "END!" << endl;
	return 0;
}
