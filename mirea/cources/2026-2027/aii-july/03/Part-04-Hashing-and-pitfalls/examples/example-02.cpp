#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void print_dict(const string &name, const auto &mp) {
    cout << name << " = {";
    bool first = true;
    for (const auto &[key, value] : mp) {
        if (!first) cout << ", ";
        cout << key << ": " << value;
        first = false;
    }
    cout << "}" << '\n';
}

int main() {
    vector<string> words = {"pear", "apple", "kiwi", "pear", "plum", "apple"};

    // Считаем частоты слов.
    unordered_map<string, int> cnt;
    for (const string &word : words) {
        cnt[word]++;
    }

    // Количество различных ключей.
    cout << cnt.size() << '\n';

    print_dict("cnt", cnt);

    // Поиск по ключу.
    for (const string &word : vector<string>{"pear", "mango"}) {
        auto it = cnt.find(word);
        if (it == cnt.end()) {
            cout << "Find " << word << ": fail" << '\n';
        } else {
            cout << "Find " << word << ": ok, value = " << it->second << '\n';
        }
    }

    // Удаление ключей.
    for (const string &word : vector<string>{"pear", "mango", "apple"}) {
        cout << "Delete " << word << ": ";
        auto it = cnt.find(word);
        if (it == cnt.end()) {
            cout << "fail";
        } else {
            cout << "ok";
            cnt.erase(it);
        }
        print_dict(", cnt", cnt);
    }
}
