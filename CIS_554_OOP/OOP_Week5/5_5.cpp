#include <iostream>

using std::cout;
using std::cin;

class RecursiveSum
{
public:
	int calculate(int n)
	{
		if (n == 0)
		{
			return 0;
		}
		else
		{
			return n + calculate(n - 1);
		}
	}
};

int main()
{
	cout << "Enter the max value N: ";
	int n;
	cin >> n;

	RecursiveSum recursiveSum;
	cout << "The sum of all numbers from one to N is: " << recursiveSum.calculate(n);
}