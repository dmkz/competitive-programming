#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
std::map<int,std::string> s;
void initTest() {
               s[2]+='P';                                             s[7]+='C'; s[8]+= 'C';    
               s[2]+='W';                       s[5]+='B';            s[7]+='G'; s[8]+= 'V'; s[9]+='V';
               s[2]+='V';                       s[5]+='T'; s[6]+='Z'; s[7]+='J'; s[8]+= 'T'; s[9]+='S';
               s[2]+='D'; s[3]+='L';            s[5]+='Q'; s[6]+='F'; s[7]+='Z'; s[8]+= 'W'; s[9]+='R';
               s[2]+='C'; s[3]+='N'; s[4]+='R'; s[5]+='H'; s[6]+='L'; s[7]+='Q'; s[8]+= 'F'; s[9]+='G';
    s[1]+='F'; s[2]+='M'; s[3]+='Z'; s[4]+='H'; s[5]+='G'; s[6]+='W'; s[7]+='L'; s[8]+= 'R'; s[9]+='H';
    s[1]+='R'; s[2]+='H'; s[3]+='M'; s[4]+='C'; s[5]+='P'; s[6]+='C'; s[7]+='V'; s[8]+= 'N'; s[9]+='W';
    s[1]+='W'; s[2]+='T'; s[3]+='P'; s[4]+='J'; s[5]+='C'; s[6]+='G'; s[7]+='W'; s[8]+= 'P'; s[9]+='J';
    for (auto &[_,ss] : s)
        std::reverse(all(ss));
}

int main() {
    initTest();
    std::string line;
    const bool easy_subtask = false;
    while(std::getline(std::cin,line)) {
        int cnt,from,to;
        sscanf(line.c_str(), "move %d from %d to %d", &cnt, &from, &to);
        // std::cout << "cnt = " << cnt << ", from = " << from << ", to = " << to << std::endl;
        // std::cout << "sFrom = " << s[from] << std::endl;
        // std::cout << "sTo = " << s[to] << std::endl;
        if (easy_subtask) {
            while(cnt--) {
                assert(isz(s[from]));
                s[to] += s[from].back();
                s[from].pop_back();
            }
        } else {
            s[to] += s[from].substr(isz(s[from])-cnt,cnt);
            s[from].resize(isz(s[from])-cnt);
        }
        // std::cout << "sFrom = " << s[from] << std::endl;
        // std::cout << "sTo = " << s[to] << std::endl;
    }
    std::string answ1;
    for (auto &[_,ss] : s)
        answ1 += ss.back();
    std::cout << answ1 << std::endl;
}