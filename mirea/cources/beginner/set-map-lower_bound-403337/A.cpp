#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем множество цитат
    string s;
    getline(cin, s);
    int n = stoi(s);
    set<string> st;
    while(n--){
        getline(cin,s);
        st.insert(s);
    }
    // читаем запросы и отвечаем на них:
    getline(cin, s);
    int q = stoi(s);
    while(q--){
        getline(cin,s);
        cout<<(st.count(s)?"YES\n":"NO\n");
    }
}