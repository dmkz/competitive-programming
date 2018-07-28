/*
    Problem: 1470. UFOs
    
    Solution: 3D-Fenwick, O(q*log(n)^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

struct Fenwick3D {

    int s1, s2, s3;
    std::vector<std::vector<std::vector<int>>> data;
    
    Fenwick3D(int s1_, int s2_, int s3_) : s1(s1_), s2(s2_), s3(s3_) {
        data.resize(s1);
        for (auto& it : data) {
            it.resize(s2);
            for (auto& jt : it) {
                jt.resize(s3);
            }
        }
    }
    
    void inc(int x, int y, int z, int val) {
        for (int i = x; i < s1; i |= i+1) {
            for (int j = y; j < s2; j |= j+1) {
                for (int k = z; k < s3; k |= k+1) {
                    data[i][j][k] += val;
                }
            }
        }
    }
    
    ll get(int x, int y, int z) const {
        ll answ = 0;
        for (int i = x; i >= 0; i = (i&(i+1))-1) {
            for (int j = y; j >= 0; j = (j&(j+1))-1) {
                for (int k = z; k >= 0; k = (k&(k+1))-1) {
                    answ += data[i][j][k];
                }
            }
        }
        return answ;
    }
    
    ll get(int x1, int y1, int z1, int x2, int y2, int z2) {
        assert(0 < x1 && x1 <= x2 && x2 < s1);
        assert(0 < y1 && y1 <= y2 && y2 < s2);
        assert(0 < z1 && z1 <= z2 && z2 < s3);
        return get(x2, y2, z2) 
            - get(x1-1, y2, z2) - get(x2, y1-1, z2) - get(x2, y2, z1-1) 
            + get(x1-1, y1-1, z2) + get(x1-1, y2, z1-1) + get(x2, y1-1, z1-1) 
            - get(x1-1, y1-1, z1-1);
    }
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    Fenwick3D fw(n+1, n+1, n+1);
    while (true) {
        int t; std::cin >> t;
        if (t == 3) {
            break;
        } else if (t == 1) {
            int x, y, z, k;
            std::cin >> x >> y >> z >> k;
            x++,y++,z++;
            fw.inc(x,y,z,k);
        } else if (t == 2) {
            int x1,y1,z1,x2,y2,z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            x1++,y1++,z1++,x2++,y2++,z2++;
            std::cout << fw.get(x1,y1,z1,x2,y2,z2) << '\n';
        }
    }
    
    return 0;
}