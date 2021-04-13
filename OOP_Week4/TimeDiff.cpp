#include "TimeDiff.h"

bool TimeDiff::validateTime(int hour, int minute, int second)
{
	//calculate the negative to simplify boolean algebra
	return !(hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0);
}

int TimeDiff::SecondsSinceNoon(int hour, int minute, int second)
{
	int secondsInMinute = 60;
	int minutesInHour = 60;
	int hoursInDay = 24;

	if (validateTime(hour, minute, second)) 
	{
		int totalSeconds = secondsInMinute * minutesInHour * hoursInDay;
		int noonSeconds = totalSeconds / 2;
		int inpSeconds = (secondsInMinute * minutesInHour * hour) + (secondsInMinute * minute) + second;

		int diff = inpSeconds - noonSeconds;
		if (diff >= 0)
		{
			return diff;
		}
		else
		{
			return totalSeconds + diff;
		}
	}
	else 
	{
		return -1;
	}
}
