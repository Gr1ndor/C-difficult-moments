#include <iostream>
#include <numeric>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <functional>
#include <Windows.h>
#include <algorithm>

using namespace std;

class FullName
{
	string name;
	string surname;
	string patr = "-";
public:
	FullName(string _name, string _surname, string _patr) : name(_name), surname(_surname), patr(_patr) {};
	FullName(string _name, string _surname) : name(_name), surname(_surname) {};
	FullName() {};
	void Open() {
		ifstream in("data.bin", ios::binary);
		in.read(name.data(), name.size());
		in.read(surname.data(), surname.size());
		in.read(patr.data(), patr.size());
	}; // бинарная десериализация в файл 
	void Save() {
		ofstream out("data.bin", ios::binary);
		out.write(name.c_str(), name.size());
		out.write(surname.c_str(), surname.size());
		out.write(patr.c_str(), patr.size());
	}; // бинарная сериализация в файл

	friend ostream& operator<<(ostream& _out, FullName fn) { _out << fn.name << ' ' << fn.surname << ' ' << fn.patr; return _out; };
	friend bool operator==(FullName f1, FullName f2)
	{
		return (f1.name == f2.name) && (f1.surname == f2.surname) && (f1.patr == f2.patr);
	}
};

class Student : public FullName
{
	FullName stName;
	vector<int> grades;
	double avg;
public:
	Student(string _name, string _surname, string _patr) : stName(_name, _surname, _patr) {};
	Student(string _name, string _surname) : stName(_name, _surname) {};
	void setGrades(int gr) { grades.push_back(gr); };
	void getGrades() { for (auto el : grades) cout << el << ' '; cout << endl; };
	void serAvg() { avg = grades.empty() ? 0.0 : accumulate(grades.begin(), grades.end(), 0.0) / grades.size(); };
	void printAvg() { cout << avg << endl; };
	double getAvg() { return avg; };
	const FullName getName() { return stName; };

	void Open() {
		ifstream in("data.bin", ios::binary);
		stName.Open();
		for(auto el : grades)
			in.read(reinterpret_cast<char*>(&el), sizeof(el));
		in.read(reinterpret_cast<char*>(&avg), sizeof(avg));
	};
	void Save() {
		ofstream out("data.bin", ios::binary);
		stName.Save();
		for (auto el : grades)
			out.write(reinterpret_cast<char*>(&el), sizeof(el));
		out.write(reinterpret_cast<char*>(&avg), sizeof(avg));
	};

	friend ostream& operator<<(ostream& _out, Student st) {
		_out << st.stName << endl; 
		for (auto el : st.grades) 
			_out << el << ' '; 
		_out << endl << st.avg << endl;
		return _out;
	}
};

class IRepository {
	virtual void Open() = 0; // бинарная десериализация в файл 
	virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
	virtual double GetAverageScore(const FullName& name) = 0;
	virtual string GetAllInfo(const FullName& name) = 0;
	virtual string GetAllInfo() = 0;
};

class StudentsGroup
{
	vector<Student> group;
public:
	void add(Student st) { group.push_back(st); };
	void print() { for (auto el : group) cout << el << endl; };
	void GetAllInfo(const FullName& name) { 
		auto el = find_if(group.begin(), group.end(), 
									[&](Student st) {return st.getName() == name; });
		if (el == group.end())
			cout << name << " not found" << endl;
		else
			cout << *el << endl;
	};
	double GetAverageScore(const FullName& name) { auto el = find_if(group.begin(), group.end(), 
			[&](Student st) {return st.getName() == name; }); 
	if (el == group.end())
		cout << name << " not found" << endl;
	else
		cout << el->getAvg() << endl;
	};

	
	void Save() {
		for (auto el : group)
			el.Save();
	};
	void Open() {
		for (auto el : group)
			el.Open();
	};
};

int main()
{
	Student a("Ivan", "Petrov");
	Student b("Vasya", "Shishkin", "Ivanovic");
	StudentsGroup g;
	g.add(a);
	g.add(b);
	g.print();
	g.Save();
	g.Open();
	g.print();
	FullName fn("Ivan", "Petrov");
	FullName fn2("Ivan", "Vasilev");
	g.GetAllInfo(fn);
	g.GetAllInfo(fn2);
}