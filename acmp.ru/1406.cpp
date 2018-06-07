#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>

struct Record {
    std::string id, time; int type;
    
    static Record read() {
        char buf[11];
        scanf("%10s", buf);
        std::string id(buf);
        scanf("%8s", buf);
        std::string time(buf);
        scanf("%10s", buf);
        std::string type(buf);
        int t;
        if (type == "deposit" || type == "transfer") {
            t = 1;
        } else if (type == "loan" || type == "withdrawal") {
            t = 2;
        } else {
            assert(type == "card");
            t = 3;
        }
        return Record{id, time, t};
    }
};

int main() {
    int n; scanf("%d", &n);
    std::vector<Record> r(n);
    for (auto& it : r) {
        it = Record::read();
    }
    std::sort(r.begin(), r.end(), [](const Record& a, const Record& b){
        return a.time < b.time;
    });
    for (const auto& it : r) {
        printf("Ticket %s: counter %d\n", it.id.c_str(), it.type);
    }
    return 0;
}