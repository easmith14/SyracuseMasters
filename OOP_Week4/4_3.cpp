/////////////////////////////////////////////////////
// CIS554 Object Oriented Programming in C++
// Exercise 4_3 - Logical operators
/////////////////////////////////////////////////////
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	bool bool1 = true;
	bool bool2 = true;
	bool bool3 = false;
	bool bool4 = false;

	if ((bool1 || bool3) || (bool2 && bool4))
	{
		cout << "Expression is TRUE" << endl;
	}
	else
	{
		cout << "Expression is FALSE" << endl;
	}
}
