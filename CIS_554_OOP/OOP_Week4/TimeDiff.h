#pragma once

class TimeDiff
{
public:
	int SecondsSinceNoon(int hour, int minute, int second);
private:
	bool validateTime(int hour, int minute, int second);
};