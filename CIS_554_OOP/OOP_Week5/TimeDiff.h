#pragma once

class TimeDiff
{
public:
	void SecondsSinceNoon(int hour, int minute, int second, int &result);
private:
	void validateTime(int hour, int minute, int second, bool &isValid);
};