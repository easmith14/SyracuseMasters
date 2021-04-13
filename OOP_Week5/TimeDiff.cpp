#include "TimeDiff.h"

void TimeDiff::validateTime(int hour, int minute, int second, bool &isValid)
{
	//calculate the negative to simplify boolean algebra
	isValid = !(hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0);
}

void TimeDiff::SecondsSinceNoon(int hour, int minute, int second, int &result)
{
	int secondsInMinute = 60;
	int minutesInHour = 60;
	int hoursInDay = 24;
	bool isValid = false;
	validateTime(hour, minute, second, isValid);

	if (isValid) 
	{
		int totalSeconds = secondsInMinute * minutesInHour * hoursInDay;
		int noonSeconds = totalSeconds / 2;
		int inpSeconds = (secondsInMinute * minutesInHour * hour) + (secondsInMinute * minute) + second;

		int diff = inpSeconds - noonSeconds;
		if (diff >= 0)
		{
			result = diff;
		}
		else
		{
			result = totalSeconds + diff;
		}
	}
	else 
	{
		result = -1;
	}
}
