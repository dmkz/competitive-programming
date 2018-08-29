/*
    Задача: 627. Игра в слова
    
    Решение: сортировка, множества, пересечение, строки, O(n * log(n) * LEN)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

#define all(x) (x).begin(), (x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())

std::vector<std::string> input(const std::vector<int>& cnt) {
    int q; scanf("%d", &q); char buf[101];
    std::vector<std::string> answ;
    for (int i = 0; i < q; ++i) {
        scanf("%100s", buf);
        std::string s(buf);
        std::vector<int> tmp(26);
        for (auto it : s) {
            tmp[int(it-'a')]++;
        }
        bool flag = true;
        for (int j = 0; j < 26; ++j) {
            if (tmp[j] > cnt[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        answ.push_back(s);
    }
    return answ;
}

int first(int a, int b, int ab) {
// Первый поддается
    // Сначала называет все слова, которые у него уникальны
    int min = std::min(a, ab);
    a -= min;
    ab -= min;
    // Затем либо уникальные закончились:
    if (ab == 0) {
        if (a < b) {
            return 2;
        } else if (a > b) {
            return 1;
        } else return 0;
    }
    // Либо у первого слова закончились:
    a += ab % 2;
    if (a < b) {
        return 2;
    } else if (a > b) {
        return 1;
    } else return 0;
}

int second(int a, int b, int ab) {
// Второй поддается
    int min = std::min(b, ab);
    b -= min;
    ab -= min;
    if (ab == 0) {
        if (a < b) {
            return 2;
        } else if (a > b) {
            return 1;
        } else return 0;
    }
    // b == 0, ab != 0;
    a += (ab+1)/ 2;
    b += ab/2;
    if (a < b) {
        return 2;
    } else if (a > b) {
        return 1;
    } else return 0;
}

int equal(int a, int b, int ab) {
    a += ab % 2;
    if (a < b) {
        return 2;
    } else if (a > b) {
        return 1;
    }
    return 0;
}

int main() {
    char buf[100+1];
    scanf("%100s", buf);
    std::vector<int> cnt(26);
    for (auto it : std::string(buf)) {
        cnt[int(it-'a')]++;
    }
    auto fi = input(cnt);
    auto se = input(cnt);
    std::sort(all(fi)); unique(fi);
    std::sort(all(se)); unique(se);
    std::vector<std::string> same;
    std::set_intersection(all(fi), all(se), std::back_inserter(same));
    int ab = (int)same.size();
    int a = (int)fi.size()-ab;
    int b = (int)se.size()-ab;
    printf("%d\n%d\n%d\n", equal(a,b,ab), first(a,b,ab), second(a,b,ab));
    return 0;
}