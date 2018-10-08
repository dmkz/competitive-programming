/*
    Problem: 493A. Vasya and Football
    
    Solution: map, implementation, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

int main() {
    std::string th, ta;
    std::cin >> th >> ta;
    std::map<int,int> cnth;
    std::map<int,int> cnta;
    int nQ; scanf("%d", &nQ);
    while (nQ--) {
        int time; char team; int number; char type;
        scanf("%d %c %d %c", &time, &team, &number, &type);
        if (team == 'h') {
            std::map<int,int>& cnt = cnth;
            std::string& title = th;
            if (type == 'r') {
                if (cnt[number] == 2) {
                    continue;
                } else {
                    cnt[number] = 2;
                    std::cout << title << ' ' << number << ' ' << time << '\n';
                }
            } else if (type == 'y') {
                if (cnt[number] == 2) {
                    continue;
                } else if (cnt[number] == 1) {
                    std::cout << title << ' ' << number << ' ' << time << '\n';
                    cnt[number] = 2;
                } else {
                    cnt[number] = 1;
                }
            }
        } else {
            std::map<int,int>& cnt = cnta;
            std::string& title = ta;
            if (type == 'r') {
                if (cnt[number] == 2) {
                    continue;
                } else {
                    cnt[number] = 2;
                    std::cout << title << ' ' << number << ' ' << time << '\n';
                }
            } else if (type == 'y') {
                if (cnt[number] == 2) {
                    continue;
                } else if (cnt[number] == 1) {
                    std::cout << title << ' ' << number << ' ' << time << '\n';
                    cnt[number] = 2;
                } else {
                    cnt[number] = 1;
                }
            }
        }
    }
    return 0;
}