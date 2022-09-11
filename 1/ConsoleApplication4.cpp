#include <iostream>
#include <string>
#include <tuple>
#include <optional>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>


class Person
{
private:
    std::string surname, name;
    std::optional<std::string>	patronymic;

public:
    Person(const std::string& _surname, const std::string& _name, const std::optional<std::string>& _patronymic) : surname(_surname), name(_name), patronymic(_patronymic)
    {};

    std::string getSurname() const { return surname; };

    friend std::ostream& operator<< (std::ostream& out, const Person& person) {
        out << std::setw(12) << person.surname << " " << std::setw(12) << person.name << " " << std::setw(16) << person.patronymic.value_or("");
        return out;
    }
    friend bool operator< (const Person& p1, const Person& p2) {
        return std::tie(p1.surname, p1.name, p1.patronymic) < std::tie(p2.surname, p2.name, p2.patronymic);
    }
    friend bool operator== (const Person& p1, const Person& p2) {
        return std::tie(p1.surname, p1.name, p1.patronymic) == std::tie(p2.surname, p2.name, p2.patronymic);
    }
};

class PhoneNumber
{
private:
    size_t countryCode, cityCode;
    std::string number;
    std::optional<size_t> extension;

public:
    PhoneNumber() = default;
    PhoneNumber(size_t _countryCode, size_t _cityCode, const std::string& _number, const std::optional<size_t>& _extension) : countryCode(_countryCode), cityCode(_cityCode), number(_number), extension(_extension)
    {};

    friend bool operator< (const PhoneNumber& num1, const PhoneNumber& num2) {
        return std::tie(num1.countryCode, num1.cityCode, num1.number, num1.extension) < std::tie(num2.countryCode, num2.cityCode, num2.number, num2.extension);
    }
    friend std::ostream& operator<< (std::ostream& out, const PhoneNumber& num) {
        out << "+" << num.countryCode << "(" << num.cityCode << ")" << num.number;
        if (num.extension)
            out << " " << num.extension.value();
        return out;
    }
};

class PhoneBook
{
private:
    std::vector<std::pair<Person, PhoneNumber>> record;

public:
    PhoneBook(std::ifstream& fstr) {
        std::string surname, name;
        std::optional<std::string>	patronymic;
        size_t countryCode, cityCode;
        std::string number;
        std::optional<std::string> ext;
        std::optional<size_t> extension;
        if (fstr.is_open())
        {
            while (fstr >> surname >> name >> patronymic.emplace() >> countryCode >> cityCode >> number >> ext.emplace())
            {

                if (patronymic.value() == "-")
                    patronymic = std::nullopt;
                Person person(surname, name, patronymic);
                if (ext.has_value())
                    if (ext.value() == "-")
                        extension = std::nullopt;
                    else
                        extension.emplace() = std::stoi(ext.value());
                PhoneNumber phoneNum(countryCode, cityCode, number, extension);

                record.push_back(std::make_pair(person, phoneNum));
            }
        }
        fstr.close();
    }

    void SortByName() {
        std::sort(record.begin(), record.end());
    }
    void SortByPhone() {
        std::sort(record.begin(), record.end(), [](const auto& x, const auto& y) { return x.second < y.second; });
    }

    

    std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& surname) {
        PhoneNumber number;
        std::string result = "";
        size_t count = 0;
        std::for_each(record.begin(), record.end(),
            [&](const auto& rec)
            {
                if (rec.first.getSurname() == surname)
                {
                    number = rec.second;
                    count++;
                }
            });
        if (count == 0) 
            result = "not found";
        if (count > 1) 
            result = "found more than 1";
        return std::make_tuple(result, number);
    }

    void ChangePhoneNumber(const Person& person, const PhoneNumber& newNum) {
        auto find_rec = std::find_if(record.begin(), record.end(),
            [&person](const auto& rec)
            {
                return rec.first == person;
            });
        if (find_rec != record.end()) find_rec->second = newNum;
    }

    friend std::ostream& operator<< (std::ostream& out, PhoneBook book) {
        for (const auto& [person, number] : book.record)
        {
            out << person << std::setw(5) << number << std::endl;
        }
        return out;
    }
};



int main()
{
    std::ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt 
    PhoneBook book(file);
    std::cout << book;
    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;
    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;
    std::cout << "-----GetPhoneNumber-----" << std::endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона человека, либо строку с ошибкой
    auto print_phone_number = [&book](const std::string& surname) {
    std::cout << surname << "\t";
    auto answer = book.GetPhoneNumber(surname);
    if (std::get<0>(answer).empty())
        std::cout << std::get<1>(answer);
    else
        std::cout << std::get<0>(answer);
    std::cout << std::endl;
    };
    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
        PhoneNumber{ 7, 123, "15344458", std::nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
        PhoneNumber{ 16, 465, "9155448", 13 });
    std::cout << book;
}