#include <iostream>
#include "maximum.h"

using std::cout;
using std::cin;

int main()
{
	int int1, int2, int3, int4;

	cout << "Input four integer values: ";
	cin >> int1 >> int2 >> int3 >> int4;

	cout << "The maximum integer value is: "
		<< maximum(int1, int2, int3, int4) << "\n";

	double double1, double2, double3, double4;

	cout << "Input four double values: ";
	cin >> double1 >> double2 >> double3 >> double4;

	cout << "The maximum double value is: "
		<< maximum(double1, double2, double3, double4) << "\n";

	char char1, char2, char3, char4;

	cout << "Input four character values: ";
	cin >> char1 >> char2 >> char3 >> char4;

	cout << "The maximum character value is: "
		<< maximum(char1, char2, char3, char4) << "\n";
}