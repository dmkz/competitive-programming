#include <bits/stdc++.h>

struct Exam {
    int begin, end, count;
};

int main() {
    int nDays, nExams;
    std::cin >> nDays >> nExams;
    
    std::vector<int> answ(nDays);
    
    std::vector<Exam> exams;
    std::vector<int> id_ended_exam(nDays, -1);
    for (int i = 0; i < nExams; ++i) {
        int s, d, c; std::cin >> s >> d >> c; --d, --s;
        exams.push_back(Exam{s, d, c});
        id_ended_exam[d] = i;
    }
    
    // If there is no exam which ended on the current day - we prepare for nearest
    // If there is no exam for which we have not prepared - we rest
    for (int day = 0; day < nDays; ++day) {
        if (id_ended_exam[day] == -1) { // we prepare for nearest
            int nearest_id = -1, nearest_end = nDays;
            for (int id = 0; id < nExams; ++id) {
                auto& ex = exams[id];
                if (ex.begin <= day && ex.count > 0 && nearest_end > ex.end) {
                    nearest_id = id;
                    nearest_end = ex.end;
                }
            }
            if (nearest_id != -1) {
                answ[day] = nearest_id+1;
                exams[nearest_id].count--;
            }
        } else { // we pass current exam
            auto id = id_ended_exam[day];
            if (exams[id].count == 0) {
                answ[day] = nExams+1;
            } else {
                std::cout << -1 << std::endl;
                return 0;
            }
        }
    }
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    return 0;
}