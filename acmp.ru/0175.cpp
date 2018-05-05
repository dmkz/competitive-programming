#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

struct Record {
    bool up, left1, right1, mid, left2, right2, down;
    
    bool good() const {
        return up && left1 && right1 && mid && left2 && right2 && down;
    }
    
    Record& update(const Record& other) {
        up     |= other.up;
        left1  |= other.left1;
        right1 |= other.right1;
        mid    |= other.mid;
        left2  |= other.left2;
        right2 |= other.right2;
        down   |= other.down;
        return *this;
    }
    
    Record inverse() const {
        return Record{!up, !left1, !right1, !mid, !left2, !right2, !down};
    }
};

const Record digits[10] = {
    Record{1,1,1,0,1,1,1},
    Record{0,0,1,0,0,1,0},
    Record{1,0,1,1,1,0,1},
    Record{1,0,1,1,0,1,1},
    Record{0,1,1,1,0,1,0},
    Record{1,1,0,1,0,1,1},
    Record{1,1,0,1,1,1,1},
    Record{1,0,1,0,0,1,0},
    Record{1,1,1,1,1,1,1},
    Record{1,1,1,1,0,1,1}
};

std::string get_time_str(int m) {
    char buf[5]; sprintf(buf, "%02d%02d", m / 60 % 24, m % 60);
    std::string s = buf;
    assert(s.size() == 4u);
    return s;
}

int main() {
    std::vector<Record> on, off, curr;
    on.push_back({0, 1, 0, 0, 0, 0, 0});
    on.push_back({0, 0, 0, 0, 0, 0, 0});
    on.push_back({0, 0, 0, 0, 0, 0, 0});
    on.push_back({0, 0, 0, 0, 0, 0, 0});
    curr = off = on;
    
    std::function<bool()> good = [&]() {
        for (auto& it : on) {
            if (!it.good()) return false;
        }
        for (auto& it : off) {
            if (!it.good()) return false;
        }
        return true;
    };
    int h, m; scanf("%d:%d", &h, &m); 
    m = 60 * h + m;
    
    int inc = 0;
    while (!good()) {
        assert(on[0].left1 == true && off[0].left1 == true);
        auto s = get_time_str(m + inc);
        for (int i = 0; i < 4; ++i) {
            if (i == 0 && s[i] == '0') {
                curr[i] = Record{0, 1, 0, 0, 0, 0, 0};
            } else {
                curr[i] = digits[s[i]-'0'];
            }
            on[i].update(curr[i]);
            off[i].update(curr[i].inverse());
        }
        ++inc;
    }
    printf("%d\n", inc-1);
    return 0;
}