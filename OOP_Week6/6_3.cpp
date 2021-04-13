#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::setw;

int main()
{
	vector<int> n;
	srand(time(NULL));

	//we can't use the range based one for value assignment
	for (size_t i = 0; i < 10; ++i)
	{
		n.push_back((rand() % 98) + 2);
	}

	cout << "Element" << setw(13) << "Value\n";

	double total = 0;
	int j = 0;
	for (int element : n)
	{
		total += element;
		cout << setw(7) << j++ << setw(13) << element << "\n";
	}

	double average = total / n.size();

	cout << "******************************\nThe average value is: " << average
		<< "\n******************************";

}