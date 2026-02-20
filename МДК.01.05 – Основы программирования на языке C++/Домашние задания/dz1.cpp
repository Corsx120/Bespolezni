#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

// Описание книги
struct Book {
    std::string title;
    std::string author;
    int year = 0;
};

// Задание 1: вывод информации о книге
void printBook(const Book& b) {
    std::cout << "Book: \"" << b.title << "\""
        << ", Author: " << b.author
        << ", Year: " << b.year << '\n';
}

// Описание студента
struct Student {
    std::string name;
    double average = 0.0;
    int id = 0;
};


void printStudent(const Student& s) {
    std::cout << "Student: " << s.name
        << " (ID: " << s.id << "), Average: "
        << std::fixed << std::setprecision(2) << s.average << '\n';
}

// Задание 2: увеличить средний балл студента на value
void increaseGrade(Student& s, double value) {
    s.average += value;
    // Если нужно ограничение сверху (например 5.0), раскомментируйте:
    // if (s.average > 5.0) s.average = 5.0;
}

int main() {
    // Демонстрация printBook
    Book b{ "War and Peace", "Leo Tolstoy", 1869 };
    printBook(b);

    // Задание 3: создаём вектор из 3-5 студентов
    std::vector<Student> students = {
        {"Ivan Ivanov", 4.20, 101},
        {"Petr Petrov", 3.85, 102},
        {"Anna Sidorova", 4.95, 103},
        {"Olga Smirnova", 4.95, 104} 
    };

    // Увеличим оценку одному студенту для примера
    increaseGrade(students[1], 0.5); // Petr Petrov -> 4.35

    std::cout << "\nAll students:\n";
    for (const auto& s : students) printStudent(s);

    // Найти студента с максимальным средним баллом
    auto it = std::max_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.average < b.average;
        });

    if (it != students.end()) {
        std::cout << "\nStudent with max average:\n";
        printStudent(*it);
    }
    else {
        std::cout << "No students in the list.\n";
    }

    return 0;
}