#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <array>
#include <iomanip>

void addMean(std::list<double>& l) {
	double sum = 0;
	for (auto it : l)
		sum += it;
	l.push_back(sum / l.size());
}


class Matrix
{
	size_t m_size;
	std::vector<std::vector<int>> matrix;
public:
	Matrix(int _size) : m_size(_size) { create(); };

	int Det() { return findDet(matrix, m_size); };
	int findDet(auto a, int n) {
		if (n == 1)
			return a[0][0];
		else if (n == 2)
			return a[0][0] * a[1][1] - a[0][1] * a[1][0];
		else {
			int d = 0;
			for (int k = 0; k < n; k++) {
				std::vector<std::vector<int>> m(n - 1, std::vector<int>(n - 1));
				for (int i = 1; i < n; i++) {
					int t = 0;
					for (int j = 0; j < n; j++) {
						if (j == k)
							continue;
						m[i - 1][t] = a[i][j];
						t++;
					}
				}
				d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
			}
			return d;
		}
	};

	friend std::ostream& operator<<(std::ostream& out, Matrix m) {
		for (auto it : m.matrix)
		{
			for (auto it2 : it)
				out << std::setw(3) << it2;
			out << std::endl;
		}
		return out;
	}
private:
	void create() {
		matrix.resize(m_size);
		for (auto& it : matrix)
		{
			it.resize(m_size);
			for (auto& it2 : it)
			{
				it2 = (rand() % 100);
			}
		}
	}
};

template<typename T>
class MyIt
{
public:
	MyIt() {};
	MyIt(T& val) { ptr = &val; };

	void operator=(T val) { *ptr = val; }
	T operator*() { return *ptr; }
	void operator++() { ptr++; }
	void operator--() { ptr--; }
private:
	T* ptr;
};

int main()
{
	//task1
    std::list<double> l{ 1, 2, 3, 4, 5, 6 };
	for (auto it : l)
		std::cout << it << ' ';
	std::cout << std::endl;
    addMean(l);
	for (auto it : l)
		std::cout << it << ' ';
	std::cout << std::endl;
	std::cout << std::endl;


	//task2

	Matrix mat(5);
	std::cout << mat << std::endl;
	std::cout << "Det = " << mat.Det() << std::endl;
	std::cout << std::endl;
	

	//task3
	for (MyIt iter : l)
		std::cout << *iter << ' ';
	std::cout << std::endl;
}