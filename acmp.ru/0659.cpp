#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

int C(int n, int k) {
    if (k > n - k) {
        return C(n, n-k);
    }
    int answer = 1;
    for (int i = 1; i <= k; ++i) {
        answer *= (n - i + 1);
        answer /= i;
    }
    return answer;
}

int main() {
    int n, k, m; scanf("%d %d %d", &n, &k, &m);
    
    char is_pair[24][24] = {};
    for (int i = 0; i < m; ++i) {
        int a, b; scanf("%d %d", &a, &b); --a, --b;
        is_pair[a][b] = is_pair[b][a] = 1;
    }
    
    int perm[24] = {}; 
    for (int i = 0; i < k; ++i) perm[n-1-i] = 1;
    
    // Формирование всех перестановок:
    std::vector<int> permutations;
    permutations.reserve(C(n, k));
    do {
        int number = 0;
        for (int i = 0; i < n; ++i) {
            number |= (perm[i] << i);
        }
        permutations.push_back(number);
    } while (std::next_permutation(perm, perm+n));
    
    // Перебор всех перестановок:
    std::vector<int> answer(n*n, -1);
    for (auto perm : permutations) {
        int sum = 0;        
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 1) & 1))) & is_pair[0][1];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 2) & 1))) & is_pair[0][2];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 3) & 1))) & is_pair[0][3];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 4) & 1))) & is_pair[0][4];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 5) & 1))) & is_pair[0][5];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 6) & 1))) & is_pair[0][6];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 7) & 1))) & is_pair[0][7];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 8) & 1))) & is_pair[0][8];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 9) & 1))) & is_pair[0][9];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 10) & 1))) & is_pair[0][10];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 11) & 1))) & is_pair[0][11];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 12) & 1))) & is_pair[0][12];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 13) & 1))) & is_pair[0][13];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 14) & 1))) & is_pair[0][14];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 15) & 1))) & is_pair[0][15];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 16) & 1))) & is_pair[0][16];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 17) & 1))) & is_pair[0][17];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 18) & 1))) & is_pair[0][18];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 19) & 1))) & is_pair[0][19];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 20) & 1))) & is_pair[0][20];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 21) & 1))) & is_pair[0][21];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 22) & 1))) & is_pair[0][22];
        sum += (~(((perm >> 0) & 1) ^ ((perm >> 23) & 1))) & is_pair[0][23];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 2) & 1))) & is_pair[1][2];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 3) & 1))) & is_pair[1][3];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 4) & 1))) & is_pair[1][4];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 5) & 1))) & is_pair[1][5];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 6) & 1))) & is_pair[1][6];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 7) & 1))) & is_pair[1][7];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 8) & 1))) & is_pair[1][8];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 9) & 1))) & is_pair[1][9];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 10) & 1))) & is_pair[1][10];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 11) & 1))) & is_pair[1][11];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 12) & 1))) & is_pair[1][12];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 13) & 1))) & is_pair[1][13];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 14) & 1))) & is_pair[1][14];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 15) & 1))) & is_pair[1][15];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 16) & 1))) & is_pair[1][16];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 17) & 1))) & is_pair[1][17];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 18) & 1))) & is_pair[1][18];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 19) & 1))) & is_pair[1][19];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 20) & 1))) & is_pair[1][20];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 21) & 1))) & is_pair[1][21];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 22) & 1))) & is_pair[1][22];
        sum += (~(((perm >> 1) & 1) ^ ((perm >> 23) & 1))) & is_pair[1][23];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 3) & 1))) & is_pair[2][3];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 4) & 1))) & is_pair[2][4];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 5) & 1))) & is_pair[2][5];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 6) & 1))) & is_pair[2][6];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 7) & 1))) & is_pair[2][7];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 8) & 1))) & is_pair[2][8];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 9) & 1))) & is_pair[2][9];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 10) & 1))) & is_pair[2][10];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 11) & 1))) & is_pair[2][11];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 12) & 1))) & is_pair[2][12];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 13) & 1))) & is_pair[2][13];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 14) & 1))) & is_pair[2][14];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 15) & 1))) & is_pair[2][15];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 16) & 1))) & is_pair[2][16];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 17) & 1))) & is_pair[2][17];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 18) & 1))) & is_pair[2][18];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 19) & 1))) & is_pair[2][19];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 20) & 1))) & is_pair[2][20];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 21) & 1))) & is_pair[2][21];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 22) & 1))) & is_pair[2][22];
        sum += (~(((perm >> 2) & 1) ^ ((perm >> 23) & 1))) & is_pair[2][23];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 4) & 1))) & is_pair[3][4];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 5) & 1))) & is_pair[3][5];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 6) & 1))) & is_pair[3][6];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 7) & 1))) & is_pair[3][7];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 8) & 1))) & is_pair[3][8];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 9) & 1))) & is_pair[3][9];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 10) & 1))) & is_pair[3][10];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 11) & 1))) & is_pair[3][11];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 12) & 1))) & is_pair[3][12];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 13) & 1))) & is_pair[3][13];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 14) & 1))) & is_pair[3][14];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 15) & 1))) & is_pair[3][15];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 16) & 1))) & is_pair[3][16];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 17) & 1))) & is_pair[3][17];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 18) & 1))) & is_pair[3][18];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 19) & 1))) & is_pair[3][19];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 20) & 1))) & is_pair[3][20];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 21) & 1))) & is_pair[3][21];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 22) & 1))) & is_pair[3][22];
        sum += (~(((perm >> 3) & 1) ^ ((perm >> 23) & 1))) & is_pair[3][23];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 5) & 1))) & is_pair[4][5];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 6) & 1))) & is_pair[4][6];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 7) & 1))) & is_pair[4][7];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 8) & 1))) & is_pair[4][8];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 9) & 1))) & is_pair[4][9];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 10) & 1))) & is_pair[4][10];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 11) & 1))) & is_pair[4][11];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 12) & 1))) & is_pair[4][12];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 13) & 1))) & is_pair[4][13];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 14) & 1))) & is_pair[4][14];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 15) & 1))) & is_pair[4][15];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 16) & 1))) & is_pair[4][16];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 17) & 1))) & is_pair[4][17];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 18) & 1))) & is_pair[4][18];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 19) & 1))) & is_pair[4][19];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 20) & 1))) & is_pair[4][20];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 21) & 1))) & is_pair[4][21];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 22) & 1))) & is_pair[4][22];
        sum += (~(((perm >> 4) & 1) ^ ((perm >> 23) & 1))) & is_pair[4][23];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 6) & 1))) & is_pair[5][6];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 7) & 1))) & is_pair[5][7];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 8) & 1))) & is_pair[5][8];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 9) & 1))) & is_pair[5][9];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 10) & 1))) & is_pair[5][10];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 11) & 1))) & is_pair[5][11];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 12) & 1))) & is_pair[5][12];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 13) & 1))) & is_pair[5][13];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 14) & 1))) & is_pair[5][14];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 15) & 1))) & is_pair[5][15];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 16) & 1))) & is_pair[5][16];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 17) & 1))) & is_pair[5][17];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 18) & 1))) & is_pair[5][18];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 19) & 1))) & is_pair[5][19];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 20) & 1))) & is_pair[5][20];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 21) & 1))) & is_pair[5][21];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 22) & 1))) & is_pair[5][22];
        sum += (~(((perm >> 5) & 1) ^ ((perm >> 23) & 1))) & is_pair[5][23];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 7) & 1))) & is_pair[6][7];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 8) & 1))) & is_pair[6][8];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 9) & 1))) & is_pair[6][9];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 10) & 1))) & is_pair[6][10];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 11) & 1))) & is_pair[6][11];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 12) & 1))) & is_pair[6][12];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 13) & 1))) & is_pair[6][13];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 14) & 1))) & is_pair[6][14];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 15) & 1))) & is_pair[6][15];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 16) & 1))) & is_pair[6][16];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 17) & 1))) & is_pair[6][17];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 18) & 1))) & is_pair[6][18];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 19) & 1))) & is_pair[6][19];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 20) & 1))) & is_pair[6][20];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 21) & 1))) & is_pair[6][21];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 22) & 1))) & is_pair[6][22];
        sum += (~(((perm >> 6) & 1) ^ ((perm >> 23) & 1))) & is_pair[6][23];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 8) & 1))) & is_pair[7][8];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 9) & 1))) & is_pair[7][9];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 10) & 1))) & is_pair[7][10];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 11) & 1))) & is_pair[7][11];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 12) & 1))) & is_pair[7][12];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 13) & 1))) & is_pair[7][13];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 14) & 1))) & is_pair[7][14];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 15) & 1))) & is_pair[7][15];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 16) & 1))) & is_pair[7][16];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 17) & 1))) & is_pair[7][17];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 18) & 1))) & is_pair[7][18];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 19) & 1))) & is_pair[7][19];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 20) & 1))) & is_pair[7][20];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 21) & 1))) & is_pair[7][21];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 22) & 1))) & is_pair[7][22];
        sum += (~(((perm >> 7) & 1) ^ ((perm >> 23) & 1))) & is_pair[7][23];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 9) & 1))) & is_pair[8][9];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 10) & 1))) & is_pair[8][10];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 11) & 1))) & is_pair[8][11];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 12) & 1))) & is_pair[8][12];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 13) & 1))) & is_pair[8][13];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 14) & 1))) & is_pair[8][14];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 15) & 1))) & is_pair[8][15];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 16) & 1))) & is_pair[8][16];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 17) & 1))) & is_pair[8][17];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 18) & 1))) & is_pair[8][18];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 19) & 1))) & is_pair[8][19];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 20) & 1))) & is_pair[8][20];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 21) & 1))) & is_pair[8][21];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 22) & 1))) & is_pair[8][22];
        sum += (~(((perm >> 8) & 1) ^ ((perm >> 23) & 1))) & is_pair[8][23];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 10) & 1))) & is_pair[9][10];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 11) & 1))) & is_pair[9][11];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 12) & 1))) & is_pair[9][12];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 13) & 1))) & is_pair[9][13];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 14) & 1))) & is_pair[9][14];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 15) & 1))) & is_pair[9][15];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 16) & 1))) & is_pair[9][16];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 17) & 1))) & is_pair[9][17];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 18) & 1))) & is_pair[9][18];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 19) & 1))) & is_pair[9][19];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 20) & 1))) & is_pair[9][20];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 21) & 1))) & is_pair[9][21];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 22) & 1))) & is_pair[9][22];
        sum += (~(((perm >> 9) & 1) ^ ((perm >> 23) & 1))) & is_pair[9][23];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 11) & 1))) & is_pair[10][11];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 12) & 1))) & is_pair[10][12];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 13) & 1))) & is_pair[10][13];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 14) & 1))) & is_pair[10][14];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 15) & 1))) & is_pair[10][15];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 16) & 1))) & is_pair[10][16];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 17) & 1))) & is_pair[10][17];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 18) & 1))) & is_pair[10][18];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 19) & 1))) & is_pair[10][19];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 20) & 1))) & is_pair[10][20];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 21) & 1))) & is_pair[10][21];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 22) & 1))) & is_pair[10][22];
        sum += (~(((perm >> 10) & 1) ^ ((perm >> 23) & 1))) & is_pair[10][23];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 12) & 1))) & is_pair[11][12];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 13) & 1))) & is_pair[11][13];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 14) & 1))) & is_pair[11][14];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 15) & 1))) & is_pair[11][15];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 16) & 1))) & is_pair[11][16];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 17) & 1))) & is_pair[11][17];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 18) & 1))) & is_pair[11][18];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 19) & 1))) & is_pair[11][19];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 20) & 1))) & is_pair[11][20];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 21) & 1))) & is_pair[11][21];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 22) & 1))) & is_pair[11][22];
        sum += (~(((perm >> 11) & 1) ^ ((perm >> 23) & 1))) & is_pair[11][23];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 13) & 1))) & is_pair[12][13];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 14) & 1))) & is_pair[12][14];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 15) & 1))) & is_pair[12][15];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 16) & 1))) & is_pair[12][16];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 17) & 1))) & is_pair[12][17];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 18) & 1))) & is_pair[12][18];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 19) & 1))) & is_pair[12][19];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 20) & 1))) & is_pair[12][20];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 21) & 1))) & is_pair[12][21];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 22) & 1))) & is_pair[12][22];
        sum += (~(((perm >> 12) & 1) ^ ((perm >> 23) & 1))) & is_pair[12][23];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 14) & 1))) & is_pair[13][14];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 15) & 1))) & is_pair[13][15];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 16) & 1))) & is_pair[13][16];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 17) & 1))) & is_pair[13][17];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 18) & 1))) & is_pair[13][18];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 19) & 1))) & is_pair[13][19];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 20) & 1))) & is_pair[13][20];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 21) & 1))) & is_pair[13][21];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 22) & 1))) & is_pair[13][22];
        sum += (~(((perm >> 13) & 1) ^ ((perm >> 23) & 1))) & is_pair[13][23];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 15) & 1))) & is_pair[14][15];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 16) & 1))) & is_pair[14][16];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 17) & 1))) & is_pair[14][17];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 18) & 1))) & is_pair[14][18];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 19) & 1))) & is_pair[14][19];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 20) & 1))) & is_pair[14][20];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 21) & 1))) & is_pair[14][21];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 22) & 1))) & is_pair[14][22];
        sum += (~(((perm >> 14) & 1) ^ ((perm >> 23) & 1))) & is_pair[14][23];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 16) & 1))) & is_pair[15][16];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 17) & 1))) & is_pair[15][17];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 18) & 1))) & is_pair[15][18];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 19) & 1))) & is_pair[15][19];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 20) & 1))) & is_pair[15][20];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 21) & 1))) & is_pair[15][21];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 22) & 1))) & is_pair[15][22];
        sum += (~(((perm >> 15) & 1) ^ ((perm >> 23) & 1))) & is_pair[15][23];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 17) & 1))) & is_pair[16][17];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 18) & 1))) & is_pair[16][18];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 19) & 1))) & is_pair[16][19];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 20) & 1))) & is_pair[16][20];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 21) & 1))) & is_pair[16][21];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 22) & 1))) & is_pair[16][22];
        sum += (~(((perm >> 16) & 1) ^ ((perm >> 23) & 1))) & is_pair[16][23];
        sum += (~(((perm >> 17) & 1) ^ ((perm >> 18) & 1))) & is_pair[17][18];
        sum += (~(((perm >> 17) & 1) ^ ((perm >> 19) & 1))) & is_pair[17][19];
        sum += (~(((perm >> 17) & 1) ^ ((perm >> 20) & 1))) & is_pair[17][20];
        sum += (~(((perm >> 17) & 1) ^ ((perm >> 21) & 1))) & is_pair[17][21];
        sum += (~(((perm >> 17) & 1) ^ ((perm >> 22) & 1))) & is_pair[17][22];
        sum += (~(((perm >> 17) & 1) ^ ((perm >> 23) & 1))) & is_pair[17][23];
        sum += (~(((perm >> 18) & 1) ^ ((perm >> 19) & 1))) & is_pair[18][19];
        sum += (~(((perm >> 18) & 1) ^ ((perm >> 20) & 1))) & is_pair[18][20];
        sum += (~(((perm >> 18) & 1) ^ ((perm >> 21) & 1))) & is_pair[18][21];
        sum += (~(((perm >> 18) & 1) ^ ((perm >> 22) & 1))) & is_pair[18][22];
        sum += (~(((perm >> 18) & 1) ^ ((perm >> 23) & 1))) & is_pair[18][23];
        sum += (~(((perm >> 19) & 1) ^ ((perm >> 20) & 1))) & is_pair[19][20];
        sum += (~(((perm >> 19) & 1) ^ ((perm >> 21) & 1))) & is_pair[19][21];
        sum += (~(((perm >> 19) & 1) ^ ((perm >> 22) & 1))) & is_pair[19][22];
        sum += (~(((perm >> 19) & 1) ^ ((perm >> 23) & 1))) & is_pair[19][23];
        sum += (~(((perm >> 20) & 1) ^ ((perm >> 21) & 1))) & is_pair[20][21];
        sum += (~(((perm >> 20) & 1) ^ ((perm >> 22) & 1))) & is_pair[20][22];
        sum += (~(((perm >> 20) & 1) ^ ((perm >> 23) & 1))) & is_pair[20][23];
        sum += (~(((perm >> 21) & 1) ^ ((perm >> 22) & 1))) & is_pair[21][22];
        sum += (~(((perm >> 21) & 1) ^ ((perm >> 23) & 1))) & is_pair[21][23];
        sum += (~(((perm >> 22) & 1) ^ ((perm >> 23) & 1))) & is_pair[22][23];
        answer[sum] = perm;
    } 
    std::vector<char> best;
    for (int i = (int)answer.size()-1; i >= 0; --i) {
        if (answer[i] != -1) {
            // printf("i = %d\n", i);
            for (int j = 0; j < n; ++j) {
                best.push_back((answer[i] >> j) & 1);
            }
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (best[i] == 1) {
            printf("%d ", i+1);
        }
    }
    printf("\n");
    return 0;
}