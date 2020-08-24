#include <iostream>

using namespace std;

int main()
{
	int health = 100;
	for (;;)
	{
		cout << "Health is: " << health << "\nAddress is: " << &health << "\n";
		system("pause");
		health--;
	}

	return 0;
}