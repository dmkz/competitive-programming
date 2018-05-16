#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

typedef long long ll;

struct Record {
    int sit_score, stay_score, id;
    
    inline int diff_score() const {
        return sit_score - stay_score;
    }
};

const int IN = 1;
const int OUT = 0;

struct Event {
    int time, type, id;
};

bool operator<(const Record& a, const Record& b) {
    int a_diff = a.diff_score();
    int b_diff = b.diff_score();
    return a_diff > b_diff || (a_diff == b_diff && a.id < b.id);
}

int main() {
    int n, nPlaces, nStops; 
    scanf("%d %d %d", &n, &nPlaces, &nStops); 

    std::vector<Record> records(n);
    std::vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int a, b, c, d; scanf("%d %d %d %d", &a, &b, &c, &d);
        records[i] = Record{a, b, i};
        events.push_back(Event{c,  IN, i});
        events.push_back(Event{d, OUT, i});
    }
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b){
        return a.time < b.time || (a.time == b.time && (a.type < b.type || (a.type == b.type && a.id < b.id)));
    });
    
    std::set<Record> sit, stay;
    ll answer = 0, sum_stay = 0, sum_sit = 0;
    int cur = 0;
    std::vector<bool> is_stay(n, false);
    for (auto& e : events) {
        answer += (sum_stay + sum_sit) * (e.time - cur);
        cur = e.time;
        if (e.type == OUT) {
            if (is_stay[e.id]) {
                stay.erase(records[e.id]);
                sum_stay -= records[e.id].stay_score;
            } else {
                sit.erase(records[e.id]);
                sum_sit -= records[e.id].sit_score;
                if (stay.empty()) continue;
                auto top = stay.begin();
                if (top->diff_score() <= 0) continue;
                assert((int)sit.size() < nPlaces);
                sit.insert(records[top->id]);
                sum_stay -= records[top->id].stay_score;
                sum_sit += records[top->id].sit_score;
                is_stay[top->id] = false;
                stay.erase(stay.begin());
            }
        } else {
            if (records[e.id].diff_score() <= 0) {
                is_stay[e.id] = true;
                stay.insert(records[e.id]);
                sum_stay += records[e.id].stay_score;
                continue;
            }
            if ((int)sit.size() < nPlaces || sit.upper_bound(records[e.id]) != sit.end()) {
                is_stay[e.id] = false;
                sit.insert(records[e.id]);
                sum_sit += records[e.id].sit_score;
                if ((int)sit.size() > nPlaces) {
                    auto it = std::prev(sit.end());
                    is_stay[it->id] = true;
                    sum_sit -= records[it->id].sit_score;
                    sum_stay += records[it->id].stay_score;
                    stay.insert(records[it->id]);
                    sit.erase(it);
                }
                continue;
            }
            is_stay[e.id] = true;
            stay.insert(records[e.id]);
            sum_stay += records[e.id].stay_score;
        }
    }
    assert(sum_sit == 0 && sum_stay == 0);
    std::cout << answer << std::endl;
    
    return 0;
}