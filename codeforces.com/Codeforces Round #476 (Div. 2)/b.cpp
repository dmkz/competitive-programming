#include <bits/stdc++.h>

using namespace std;

int main() {
    int size, len;
    scanf("%d %d", &size, &len);
    
    std::vector<std::vector<bool>> not_empty(size, std::vector<bool>(size, false));
    for (int i = 0; i < size; ++i) {
        char buf[101]; scanf("%100s", buf);
        for (int j = 0; j < size; ++j) {
            char c = buf[j];
            not_empty[i][j] = (c == '.');
        }
    }
    
    std::vector<std::vector<int>> count(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // идем вправо
            int count_right = 0;
            for (int dj = 0; dj < len && j + dj < size; ++dj) {
                count_right += not_empty[i][j+dj];
            }
            if (count_right == len) {
                for (int dj = 0; dj < len && j + dj < size; ++dj) {
                    ++count[i][j+dj];
                }    
            }
            // идем вниз
            int count_down = 0;
            for (int di = 0; di < len && i + di < size; ++di) {
                count_down += not_empty[i+di][j];
            }
            if (count_down == len) {
                for (int di = 0; di < len && i + di < size; ++di) {
                    ++count[i+di][j];
                }
            } 
        }
    }
    
    int max_i = 0, max_j = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (count[i][j] > count[max_i][max_j]) {
                max_i = i;
                max_j = j;
            }
        }
    }
    ++max_i;
    ++max_j;
    printf("%d %d\n", max_i, max_j);
    
    return 0;
}