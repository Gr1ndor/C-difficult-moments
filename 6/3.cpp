#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <Windows.h>
#include "Timer.h"
#include <mutex>
#include <future>

using namespace std;

void print(vector<int>& v)
{
	system("cls");
	for_each(v.begin(), v.end(), []( int n) {
		std::cout << n << ' '; });
}

void in(vector<int>& v)
{
	while (true)
	{
	this_thread::sleep_for(1s);
	v.push_back(rand() % 100);
	print(v);
	}
}

void out(vector<int>& v)
{
	while (true)
	{
	this_thread::sleep_for(500ms);
	if (!v.empty())
	{
		v.erase(remove(v.begin(), v.end(), *max_element(v.begin(), v.end())), v.end());
	}
	print(v);
	}
}



int main()
{
	vector<int> value;
	thread home(in, ref(value));
	thread thief(out, ref(value));
	home.join();
	thief.join();
}