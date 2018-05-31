#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <cassert>

struct Pair {
    int button, count;
};

enum State {LOWER, UPPER, FIRST};

int main() {
    // Чтение содержимого кнопок:
    std::vector<std::string> buttons(9);
    for (auto& it : buttons) {
        char buf[27]; char c;
        scanf("%26[^\n]%c", buf, &c); assert(c == '\n');
        it = buf;
    }
    
    // Получение номера кнопки и количества нажатий для символа c:
    std::function<Pair(char c)> get = [&](char c) {
        c = std::tolower(c);
        Pair answer{-1,-1};
        for (int id = 0; id < (int)buttons.size(); ++id) {
            if (int(buttons[id].find(c)) != -1) {
                answer = Pair{id, int(buttons[id].find(c)+1)};
                break;
            }
        }
        assert(answer.count > 0 && answer.button >= 0);
        return answer;
    };
    
    // Чтение исходной строки:
    char buf[1001];
    scanf("%1000[^\n]", buf);
    std::string s(buf);
    
    // Инициализация начального состояния и проход по строке:
    State state = FIRST;
    int prev = -1, answer = 0;
    for (auto c : s) {
        if (c == ' ') {
            answer++; prev = -1; continue;
        }
        auto res = get(c); 
        if (std::isupper(c)) {
            answer += state == LOWER;
            if (state == LOWER) {
                state = UPPER;
            } else if (state == FIRST) {
                state = LOWER;
            }
        } else if (std::islower(c)) {
            answer += state != LOWER;
            state = LOWER;
        } else {
            assert(c == '.' || c == '?' || c == '!');
            if (state == LOWER) {
                state = FIRST;
            }
        }
        answer += (res.button == prev) + res.count;
        prev = res.button;
    }
    printf("%d", answer);
    return 0;
}