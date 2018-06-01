#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cassert>

typedef long long ll;

struct Item {
    int col, height;
};

int main() {
    int nRows, nCols, nErased;
    scanf("%d %d %d", &nRows, &nCols, &nErased);
    std::vector<std::vector<int>> erased(nRows);
    for (int i = 0; i < nErased; ++i) {
        int row, col;
        scanf("%d %d", &row, &col); --row, --col;
        erased[row].push_back(col);
    }
    long long answ = 0;
    std::vector<int> height(nCols+1, 0);
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            height[col]++;
        }
        for (int col : erased[row]) {
            height[col] = 0;
        }
        std::stack<Item, std::vector<Item>> stack; 
        stack.push(Item{-1, 0});
        for (int col = 0; col <= nCols; ++col) {
            while (stack.top().height > height[col]) {
                auto top = stack.top(); stack.pop();
                // Сколькими способами можно выбрать верхнюю границу
                assert(top.height > stack.top().height);
                auto mul1 = std::min(
                    top.height-stack.top().height,
                    top.height-height[col]
                );
                // Сколькими способами можно выбрать два нижних угла
                auto mul2 = (col-top.col+1)*(col-top.col)/2;
                auto add = mul1 * 1LL * mul2;
                answ += add;
                if (stack.top().height < height[col]) {
                    stack.push(Item{top.col, height[col]});
                }                
            }
            if (stack.top().height < height[col]) {
                stack.push(Item{col, height[col]});
            }
        }
    }
    std::cout << answ;
    return 0;
}