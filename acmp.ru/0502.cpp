#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int n; std::cin >> n;
    static int arr[51][51];
    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col) {
            std::cin >> arr[row][col];
        }
    }
    int max[51][52];
    for (int i = 1; i < 51; ++i) {
        for(int j = 0; j < 52; ++j) {
            max[i][j] = -1;
        }
    }
    for (int sum = 0; sum < n; ++sum) {
        for (int col = 1; col <= n; ++col) {
            if (max[sum][col] == -1) continue;
            // Никого не едим:
            max[sum][col+1] = std::max(max[sum][col+1], max[sum][col]);
            // Cъесть в строке row комара:
            for (int row = 1; row <= n; ++row) {
                //std::cout << "max[" << sum << "][" << col << "]=" << max[sum][col] << std::endl;
                if (sum+row <= n) {
                    max[sum+row][col+1] = std::max(
                        max[sum+row][col+1], 
                        max[sum][col] + arr[row][col]
                    );
                }
            }
        }
    }
    int answ = 0;
    for (int i = 1; i <= 51; ++i) {
        answ = std::max(answ, max[n][i]);
    }
    std::cout << answ << std::endl;
    return 0;
}