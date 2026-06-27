#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T, typename Comp = less<T>>
using ordered_set = tree<T, null_type, Comp, rb_tree_tag,
                         tree_order_statistics_node_update>;
// x = s.find_by_order(k) = s[k] <-- найти k-й по порядку элемент
// k = s.order_of_key(x) <-- найти, на какую позицию встанет число x
auto generateAllPermutations(int n) {
    vector<vector<int>> result;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = i+1;
    //cout << string(20,'-') << endl;
    //cout << "n = " << n << ":\n";
    //int id = 0;
    do {
        result.push_back(a);
        //cout << setw(6) << id++ << ".";
        //for (auto it : a) cout << ' ' << it;
        //cout << endl;
    } while (next_permutation(a.begin(), a.end()));
    return result;
}

const auto fact = []()
{
    vector<int> result(100, 1);
    for (int i = 2; i < 100; i++)
        result[i] = result[i-1] * i;
    return result;
}();

int findNumber(int n, const vector<int> &a) {
    ordered_set<int> s;
    for (auto it : a)
        s.insert(it);
    int answ{};
    for (int i = 0; i < n; i++) {
        int k = (int)s.order_of_key(a[i]);
        answ += k * fact[n-i-1];
        s.erase(s.find(a[i]));
    }
    return answ;
}
auto findPermutation(int n, int number) {
    ordered_set<int> s; // s = {1,1,2,2,3,3,3,4,4,4,5}
    for (int i = 1; i <= n; i++)
        s.insert(i);
    vector<int> answer;
    for (auto it = s.begin(); it != s.end(); ) {
        if (number < fact[n-1]) {
            answer.push_back(*it);
            s.erase(it);
            n--;
            it = s.begin();
        } else {
            number -= fact[n-1];
            it++;
        }
    }
    return answer;
}
auto findPermutation2(int n, int number) {
    ordered_set<int> s;
    for (int i = 1; i <= n; i++)
        s.insert(i);
    vector<int> answer;
    // number >= k * fact[n-1] => floor(number / fact[n-1]) >= k
    while (!s.empty()) {
        int k = number / fact[n-1];
        number -= k * fact[n-1];
        auto iter = s.find_by_order(k);
        answer.push_back(*iter);
        s.erase(iter);
        n--;
    }
    return answer;
}
main() {
    for (int n = 1; n <= 9; n++) {
        auto data = generateAllPermutations(n);
        for (int i = 0; i < (int)data.size(); i++) {
            assert(i == findNumber(n, data[i]));
            assert(findPermutation(n, i) == data[i]);
            assert(findPermutation2(n, i) == data[i]);
        }
        cout << "n = " << n << ": OK" << endl;
    }
}
