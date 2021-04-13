/////////////////////////////////////////////////////
// CIS554 Object Oriented Programming in C++
// Exercise 4_2 - Break and Continue
// PART A
/////////////////////////////////////////////////////
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	for (int currentDay = 1; currentDay <= 7; currentDay++)
	{
		switch (currentDay)
		{
		case 1:
			cout << "Day " << currentDay << " = Sunday" << endl;
			break;
		case 2:
			cout << "Day " << currentDay << " = Monday" << endl;
			break;
		case 3:
			cout << "Day " << currentDay << " = Tuesday" << endl;
			break;
		case 4:
			cout << "Day " << currentDay << " = Wednesday" << endl;
			break;
		case 5:
			cout << "Day " << currentDay << " = Thursday" << endl;
			break;
		case 6:
			cout << "Day " << currentDay << " = Friday" << endl;
			break;
		case 7:
			cout << "Day " << currentDay << " = Saturday" << endl;
			break;
		default: cout << "Not an allowable day number";
			break;
		}

		//ugh this is bad
		if (currentDay >= 4) break;
	}
}
