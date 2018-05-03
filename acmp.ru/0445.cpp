#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

std::string input_name() {
    char buf[100+1];
    scanf("%100s", buf);
    std::string s(buf);
    for (auto& it : s) it = std::tolower(it);
    return s;
}

struct Record {
    int id;
    double need, price1, price2;
    std::string s;
};

int main() {
    int n, k1, k2; double limit;
    scanf("%d %lf %d %d", &n, &limit, &k1, &k2);
    
    std::vector<Record> records;
    std::map<std::string, int> indexOf;
    for (int i = 0; i < n; ++i) {
        double need;
        auto s = input_name();
        scanf("%lf", &need);
        indexOf[s] = i;
        records.push_back(Record{i, need, 0, 1e6+1, s});
    }
    for (int i = 0; i < k1; ++i) {
        double price;
        auto s = input_name();
        scanf("%lf", &price);
        if (indexOf.find(s) != indexOf.end()) {
            records[indexOf[s]].price1 = price;
        }
    }
    
    for (int i = 0; i < k2; ++i) {
        double price;
        auto s = input_name();
        scanf("%lf", &price);
        if (indexOf.find(s) != indexOf.end()) {
            records[indexOf[s]].price2 = price;
        }
    }
    
    // Сортируем в порядке возрастания отношений "новая цена" / "старая цена":
    std::stable_sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
        return 1.0L * a.price2 * b.price1 < 1.0L * b.price2 * a.price1;
    });
    
    // Набираем жадно самые выгодные товары до предела:
    std::vector<double> answer(n, 0);
    double sum = 0;
    for (auto& r : records) {
        if (r.price1 < r.price2) break;
        if (limit - sum >= r.need * r.price1) {
            answer[r.id] = r.need;
        } else {
            answer[r.id] = (limit-sum) / r.price1;
            break;
        }
        sum += answer[r.id] * r.price1;
    }
    for (auto& it : answer) {
        printf("%.4f\n", it);
    }
    
    return 0;
}