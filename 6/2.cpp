#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <Windows.h>
#include "Timer.h"
#include <mutex>
#include <future>

using namespace std;

int searchPrime(int length, promise<int> prime)
{
	if (length == 1)
	{
		return 2;
	}
	length--;
	int num = 3;
	for (num; length > 0;length--, num+=2 )
	{
		for (int j = 2; j <= sqrt(num); j++)
		{
			if (num % j == 0)
			{
				length++;
				break;
			}
		}
	}
	prime.set_value(num - 2);
	return num - 2;
}



int main()
{
	promise<int> prime;
	future<int> fut = prime.get_future();
	thread t1(searchPrime, 1000000, move(prime));

	cout << "result = " << fut.get() << endl;
	t1.join();
}