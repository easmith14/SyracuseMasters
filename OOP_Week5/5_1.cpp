#include <iostream>
#include "TimeDiff.h"
using std::cout;
using std::cin;

int main() {

	cout << "Let's find out how long it has been since the last noon!\n";

	int inpHour = 0;
	int inpMinute = 0;
	int inpSecond = 0;

	cout << "Enter the current hour: ";
	cin >> inpHour;

	cout << "Enter the current minute: ";
	cin >> inpMinute;

	cout << "Enter the current second: ";
	cin >> inpSecond;

	TimeDiff diff;
	int timeResult;
	diff.SecondsSinceNoon(inpHour, inpMinute, inpSecond, timeResult);

	if (timeResult == -1) 
	{
		cout << "Invalid time entered!";
	}
	else 
	{
		cout << "Seconds since previous noon = " << timeResult;
	}
	
}