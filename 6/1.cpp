#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <Windows.h>
#include "Timer.h"
#include <mutex>
using namespace std;

static mutex m;


class pcout
{
public:
	pcout() {  };
	template<typename T>
	pcout& operator<<(const T _t)
	{
		if (m.try_lock()) {
			m.lock();
		}

		cout << _t;
		
		return *this;
	}
	
	pcout& operator<<(std::ostream& (*fp)(ostream&))
	{
		std::cout << fp;
		return *this;
	}
};





void func1()
{
	this_thread::sleep_for(200ms);
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(200ms);
		consol_color::SetColor(15, 0);
		pcout() << i << " ";
	}
	pcout() << std::endl;
}

void func2()
{
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(200ms);
		consol_color::SetColor(10, 0);
		pcout() << i << " ";
	}
	pcout() << std::endl;
	consol_color::SetColor(15, 0);
}



int main()
{
	std::thread t1(func1);
	std::thread t2(func2);
	t1.join();
	t2.join();
	//я не смог заставить работать второй процесс, непонятно как открыть мьютекс
}