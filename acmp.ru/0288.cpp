#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int main() {
    // Чтение текста в вектор:
    std::vector<char> text;
    for (char c; c = getchar(), c != EOF; text.push_back(c));
    text.push_back('\n'); text.push_back(EOF);
    
    // Проход по вектору:
    int answ = 0;
    for (int i = 0; text[i] != EOF; ++i) {
        if (text[i] == '\'') { // Пропустить строку '..'
            ++i;
            while (text[i] != '\'') ++i;
            assert(text[i] == '\'');
        }
        if (text[i] == '{') { // Пропустить комментарий {..}
            ++answ;
            while (text[i] != '}') ++i;
            assert(text[i] == '}');
        }
        if (i > 0 && text[i-1] == '/' && text[i] == '/') {
            // Пропустить комментарий //..\n
            ++answ;
            while (text[i] != '\n') ++i;
            assert(text[i] == '\n');
        }
        if (i > 0 && text[i-1] == '(' && text[i] == '*') {
            // Пропустить комментарий (*..*)
            i += 2;
            ++answ;
            while (!(text[i-1] == '*' && text[i] == ')')) ++i;
            assert(text[i-1] == '*' && text[i] == ')');
        }
    }
    printf("%d\n", answ);
    return 0;
}