// Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock
// A for Rock, B for Paper, and C for Scissors
// X for Rock, Y for Paper, and Z for Scissors.
// shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors)
// plus (0 if you lost, 3 if the round was a draw, and 6 if you won)
#include <bits/stdc++.h>
int char2num(char c) {
    const std::string s = "ABC";
    const std::string t = "XYZ";
    int ps = s.find(c);
    int pt = t.find(c);
    if (ps == s.npos) {
        assert(pt != t.npos);
        return pt;
    }
    return ps;
}
int result(int i, int j) {
    assert(0 <= i && i <= 2);
    assert(0 <= j && j <= 2);
    if (i == j) return 3;
    if ((i+1)%3==j%3) return 6;
    return 0;
}
// part 2: X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win
int main() {
    char a,b;
    int res = 0;
    const bool easy = false;
    while (std::cin >> a >> b) {
        if(easy) {
            int i = char2num(a), j = char2num(b);
            res += result(i,j)+(j+1);
        } else {
            int i = char2num(a), delta = char2num(b)-1;
            int j = (i+delta+3)%3;
            res += result(i,j) + (j+1);
        }
    }
    std::cout << res << std::endl;
}