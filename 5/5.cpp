#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <array>
#include <iomanip>
#include <unordered_set>
#include <set>

template<typename T, typename IT>
void uniqWords(IT start, IT finish)
{
	std::unordered_set<T> s(start, finish);
	std::copy(s.begin(), s.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

void read(auto& t)
{
	std::cout << "Enter text: ";
	std::string word;
	std::vector<std::string> v;
	while (std::cin >> word)
	{
		v.push_back(word);
		if (word[word.size() - 1] == '.')
		{
			t.insert(v);
			v.clear();
		}
	}
}

void print(auto t)
{
	for_each(t.begin(), t.end(), [](std::vector<std::string> el) 
		{ 
			copy(el.begin(), el.end(), std::ostream_iterator<std::string>(std::cout, " "));
			std::cout << std::endl << el.size() << " words" << std::endl << std::endl;
		});
}

struct LessLength
{
    bool operator()( std::vector<std::string> lhs, std::vector<std::string> rhs) const
    {
        return lhs.size() < rhs.size();
    }
};

int main()
{
	std::vector<int> v = { 1,2,3,4,5,5,5,6,7,7 };
	copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	uniqWords<int>(v.begin(), v.end());

	std::vector<std::string> s = { "a", "b", "b", "c", "d", "d" };
	std::copy(s.begin(), s.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << std::endl;
	uniqWords<std::string>(s.begin(), s.end());

	std::set<std::vector<std::string>, LessLength> text;
	//все предложения заканчиваются . 
	//остановка ввода - Enter, ctrl+z, Enter
	read(text);
	print(text);
}