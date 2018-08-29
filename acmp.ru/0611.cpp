/*
    Задача: Словарные квадраты
    
    Решение: перебор, отсечение, O(n!)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cstdlib>

int n;
char field1[10][10], field2[10][10], empty1[10], empty2[10], word[20][10];

void input() {
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf(" %c", &word[i][j]);
        }
    }
}

void init() {
    for (int i = 0; i < n; ++i) {
        empty1[i] = empty2[i] = true;
    }
}

void go(int cur) {
    if (cur == 2*n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%c", field1[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%c", field2[i][j]);
            }
            printf("\n");
        }
        std::exit(0);
    }
    // Определяем слово в первый квадрат
    for (int pos = 0; pos < n; ++pos) {
        if (empty1[pos]) {
            bool flag = true;
            for (int i = 0; i < n; ++i) {
                if (empty1[i]) continue;
                if (field1[i][pos] != word[cur][i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                empty1[pos] = false;
                for (int i = 0; i < n; ++i) {
                    field1[i][pos] = word[cur][i];
                    field1[pos][i] = word[cur][i];
                }
                go(cur+1);
                empty1[pos] = true;
            }
        }
    }
    // Определяем слово во второй квадрат:
    for (int pos = 0; pos < n; ++pos) {
        if (empty2[pos]) {
            bool flag = true;
            for (int i = 0; i < n; ++i) {
                if (empty2[i]) continue;
                if (field2[i][pos] != word[cur][i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                empty2[pos] = false;
                for (int i = 0; i < n; ++i) {
                    field2[i][pos] = word[cur][i];
                    field2[pos][i] = word[cur][i];
                }
                go(cur+1);
                empty2[pos] = true;
            }
        }
    }
}

int main() {
    input();
    init();
    go(0);
    throw 1;
}