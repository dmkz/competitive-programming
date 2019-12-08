/*
    Problem: 479C. Exams
    Solution: greedy, events, sorting, O(n log(n))
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

const int FIRST = 1, FINAL = 0;

struct Event {
	int day, type, id;
};

inline bool operator<(const Event& a, const Event& b) {
	return a.day < b.day || (a.day == b.day && (a.type < b.type || (a.type == b.type && a.id < b.id)));
}

int main() {
	int n; std::cin >> n;
	std::vector<Event> events;
	std::set<std::pair<int,int>> set;
	std::vector<int> lastDay(n);
	std::vector<std::pair<int,int>> input(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> input[i].second >> input[i].first;
	}
	std::sort(input.begin(), input.end());
	input.erase(std::unique(input.begin(), input.end()), input.end());
	n = (int)input.size();
	for (int id = 0; id < n; ++id) {
		int day2 = input[id].second, day1 = input[id].first;
		events.push_back(Event{day2, FINAL, id});
		events.push_back(Event{day1, FIRST, id});
		set.insert(std::make_pair(day2, id));
		lastDay[id] = day2;
	}
	std::sort(events.begin(), events.end());
	int answ = 0;
	for (auto& e : events) {
		if (e.type == FIRST) {
			if (set.begin() -> first >= lastDay[e.id]) {
				set.erase(std::make_pair(lastDay[e.id], e.id));
				answ = e.day;
			}
		} else {
			auto it = set.find(std::make_pair(e.day, e.id));
			if (it != set.end()) {
				set.erase(it);
				answ = e.day;
			}
		}
	}
	assert(answ != 0);
	std::cout << answ;
	return 0;
}