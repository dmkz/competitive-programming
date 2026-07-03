// Демонстрация stable_sort в C++

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int score;
    string name;
};

int main() {
    // В исходном порядке студенты с одинаковым score идут друг за другом
    vector<Student> students = {
        {2, "Ann"},
        {1, "Boris"},
        {2, "Clara"},
        {1, "Diana"},
        {2, "Eva"},
    };

    // Устойчивая сортировка по score сохраняет порядок равных элементов
    stable_sort(students.begin(), students.end(), [](const Student& left, const Student& right) {
        return left.score < right.score;
    });

    // Вывод результата
    for (const Student& student : students) {
        cout << student.score << ':' << student.name << '\n';
    }
}