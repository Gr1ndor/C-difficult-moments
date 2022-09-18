#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

template<typename T>
void swap(T& t1, T& t2) {
    T t3 = std::move(t1);
    t1 = std::move(t2);
    t2 = std::move(t3);
}

template<typename T>
void SortPointers(std::vector<T>& a) {
    std::sort(a.begin(), a.end(), [](const auto x, const auto y) { return *x < *y; });
}

void searchVowel_1() {
    auto start = std::chrono::steady_clock::now();
    std::ifstream file("War.txt");
    std::string vowels = "AEIOUYaeiouy";
    size_t count = std::count_if(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), [=](char x) {return vowels.find(x) != std::string::npos; });
    file.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "Vowels = " << count << std::endl;
    std::cout << "Count_if + find = " << seconds.count() << "s" << std::endl;
    std::cout << std::endl;
}

void searchVowel_2() {
    auto start = std::chrono::steady_clock::now();
    std::ifstream file("War.txt");
    std::string vowels = "AEIOUYaeiouy";
    size_t count = std::count_if(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), [=](char x) -> bool {for (auto chr : vowels) { if (chr == x) return true; } return false; });
    file.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "Vowels = " << count << std::endl;
    std::cout << "Count_if + for = " << seconds.count() << "s" << std::endl;
    std::cout << std::endl;
}

void searchVowel_3() {
    auto start = std::chrono::steady_clock::now();
    std::ifstream file("War.txt");
    std::string vowels = "AEIOUYaeiouy";
    size_t count = 0;
    for (auto it = std::istreambuf_iterator<char>(file); it != std::istreambuf_iterator<char>(); ++it)
    {
        if (vowels.find(*it) != std::string::npos) ++count;
    }
    file.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "Vowels = " << count << std::endl;
    std::cout << "Find + for = " << seconds.count() << "s" << std::endl;
    std::cout << std::endl;
}

void searchVowel_4() {
    auto start = std::chrono::steady_clock::now();
    std::ifstream file("War.txt");
    std::string vowels = "AEIOUYaeiouy";
    size_t count = 0;
    for (auto it = std::istreambuf_iterator<char>(file); it != std::istreambuf_iterator<char>(); ++it)
    {
        for (char chr : vowels)
        {
            if (*it == chr && *it != std::string::npos) ++count;
        }
    }
    file.close();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::cout << "Vowels = " << count << std::endl;
    std::cout << "For + for = " << seconds.count() << "s" << std::endl;
    std::cout << std::endl;
}

int main()
{
    //task 1
    int a = 10, b = 5;
    int* ptra = &a;
    int* ptrb = &b;
    std::cout << ptra << std::endl;
    std::cout << *ptra << std::endl;
    std::cout << ptrb << std::endl;
    std::cout << *ptrb << std::endl;
    swap(ptra, ptrb);
    std::cout << ptra << std::endl;
    std::cout << *ptra << std::endl;
    std::cout << ptrb << std::endl;
    std::cout << *ptrb << std::endl;
    std::cout << std::endl;

    //task 2
    std::vector<int*> vec;
    for (size_t i = 0; i < 10; i++)
    {
        int* p = new int(rand() % 100);
        vec.push_back(p);
        std::cout << *vec[i] << ",  ";
    }
    std::cout << std::endl;
    SortPointers(vec);
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << *vec[i] << ",  ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //task 3
    searchVowel_1();
    searchVowel_2();
    searchVowel_3();
    searchVowel_4();
}