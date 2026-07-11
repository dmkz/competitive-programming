#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

void print_set(const string &name, const auto &s) {
    cout << name << " = {";
    bool first = true;
    for (const string &value : s) {
        if (!first) cout << ',';
        cout << value;
        first = false;
    }
    cout << "}" << '\n';
}

int main() {
    vector<string> words = {"pear", "apple", "kiwi", "pear", "plum", "apple"};

    // В unordered_set храним только уникальные слова.
    unordered_set<string> s;
    for (const string &word : words) {
        s.insert(word);
    }

    // Количество различных слов.
    cout << s.size() << '\n';

    print_set("s", s);

    // Проверка принадлежности.
    for (const string &word : vector<string>{"pear", "mango"}) {
        cout << "Have " << word << ": " << (s.count(word) ? "yes" : "no") << '\n';
    }

    // Удаление элементов.
    for (const string &word : vector<string>{"kiwi", "mango", "apple"}) {
        cout << "Delete " << word << ": ";
        auto it = s.find(word);
        if (it == s.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            s.erase(it);
        }
        print_set(", s", s);
    }
}
