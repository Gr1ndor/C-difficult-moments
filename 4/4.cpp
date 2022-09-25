#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <array>
#include <iomanip>

template<typename Con, typename T>
void insert_sorted(Con& c, T x)
{
	c.insert(upper_bound(c.begin(), c.end(), x), x);
}


int main()
{
	std::vector<int> v = { 1, 2, 3, 5, 6, 7 };
	insert_sorted(v, 4);
	for_each(v.begin(), v.end(), [](int i) {std::cout << i << ' '; });
	std::cout << std::endl;

	std::vector<float> a(100);
	std::vector<int> b(100);
	generate(a.begin(), a.end(), []() {return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100)); });
	for_each(a.begin(), a.end(), [](float i) {std::cout << i << ' '; });
	std::cout << std::endl;
	std::cout << std::endl;
	std::copy(a.begin(), a.end(), b.begin());
	for_each(b.begin(), b.end(), [](int i) {std::cout << i << ' '; });
	std::cout << std::endl;
	float err(0);
	std::for_each(a.begin(), a.end(), [&err](float n) {err += n;});
	std::for_each(b.begin(), b.end(), [&err](float n) {err -= n; });
	std::cout << std::endl;
	std::cout << "Error = " << err << std::endl;
}