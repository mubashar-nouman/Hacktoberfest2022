#include <iostream>
using namespace std;

int main()
{
	const int x = 3;
	const int y = 3;
	int nums[x][y] = { 7,5,6,1,2,3,4,6,2 };
	for (int i = 0; i < x; i++)
	{
		int sum = 0;
		for (int j = 0; j < y; j++)
		{
			sum += nums[i][j];

		}
		cout << "the sum of the row number  " << i + 1 << "  is   " << sum;
		cout << endl;
	}


}