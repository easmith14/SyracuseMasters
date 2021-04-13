#include <iostream>
#include <iomanip>
#include <array>

using std::cout;
using std::cin;
using std::array;
using std::setw;

int main()
{
	array<array<int, 10>, 10> n;
	srand(time(NULL));

	for (size_t i = 0; i < 10; ++i)
	{
		for (size_t j = 0; j < 10; ++j)
			n[i][j] = (rand() % 98) + 2;
	}

	double total = 0;
	for (auto subarray : n)
	{
		for (int element : subarray)
		{
			total += element;
			cout << setw(7) << element;
		}
		cout << "\n";
	}

	double average = total / 100;

	cout << "******************************\nThe average value of the array elements = " << average
		<< "\n******************************";

}