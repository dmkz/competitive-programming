#include <stdio.h>
#include <vector>
#include <cassert>
#include <cmath>

struct Record {
    
    bool positive;
    
    double value;
    
    double rounded;
    
    static Record read() {
        char sign; int val;
        scanf(" %c %d", &sign, &val);
        return Record{(sign == '+'), double(val), -1.0};
    }
    
};

int main() {
    int n;
    scanf("%d", &n);
    
    std::vector<Record> r;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        r.push_back(Record::read());
        sum += r[i].value;
    }
    int stat = 0;
    for (auto& it : r) {
        (it.value /= sum) *= 100;
        if (it.positive) {
            it.rounded = std::ceil(it.value);
        } else {
            it.rounded = std::floor(it.value);
        }
        stat += int(it.rounded);
    }
    //printf("stat = %d\n", stat);
    int i = 0;
    while (stat > 100 && i < n) {
        while (i < n && !r[i].positive) ++i;
        assert(i < n);
        stat -= int(r[i].rounded);
        stat += int((r[i].rounded = std::floor(r[i].value)));
        ++i;
    }
    i = 0;
    while (stat < 100 && i < n) {
        while (i < n && r[i].positive) ++i;
        assert(i < n);
        stat -= int(r[i].rounded);
        stat += int(r[i].rounded = std::ceil(r[i].value));
        ++i;
    }
    assert(stat == 100);
    for (auto& it : r) {
        printf("%d\n", int(it.rounded));
    }
    return 0;
}