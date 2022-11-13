#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k; cin >> k;
    // вставляем в set всё, что нужно:
    // (сумма, номер последовательности, удаляемый элемент)
    // ищем в сете по сумме: set.lower_bound
    multiset<tuple<int64_t, int, int>> st;
    vector<int> answer;
    for (int currId = 1; currId <= k; currId++) {
        // читаем последовательность:
        int n; cin >> n;
        vector<int> a(n);
        int64_t currSum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            currSum += a[i];
        }
        // в данный момент в сет вставлены все суммы для всех
        // предыдущих последовательностей. самое время найти пару!
        
        // перебираем каждый удаляемый элемент и ищем пару по сумме в сете:
        for (int i = 0; i < n; i++) {
            // удаляем i-й элемент:
            currSum -= a[i];
            // ищем пару: lower_bound найдёт тройку с суммой >= currSum
            // и какими-то вторым и третьим параметром
            auto candidate = st.lower_bound(make_tuple(currSum, 0, 0));
            if (candidate != st.end()) {
                auto [prevSum, prevId, prevItem] = *candidate;
                if (prevSum == currSum) {
                    // нашли пару:
                    answer = {prevId, prevItem, currId, i+1};
                }
            }
            // возвращаем i-й элемент обратно:
            currSum += a[i];
        }
        // осуществили поиск, теперь надо вставить все суммы текущей и
        // перейти к следующей последовательности:
        for (int i = 0; i < n; i++) {
            // удаляем i-й элемент:
            currSum -= a[i];
            // вставляем тройку
            // (сумма, номер последовательности, номер удаляемого эл-та)
            st.insert(make_tuple(currSum, currId, i+1));
            // возвращаем i-й элемент обратно:
            currSum += a[i];
        }
    }
    // выводим ответ:
    if (answer.empty()) {
        // нет ответа
        cout << "NO\n";
    } else {
        assert(answer.size() == 4u);
        // нашли ответ:
        cout << "YES\n";
        cout << answer[0] << ' ' << answer[1] << '\n';
        cout << answer[2] << ' ' << answer[3] << '\n';
    }
}