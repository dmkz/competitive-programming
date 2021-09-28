#include <bits/stdc++.h>
using namespace std;

int main() {
  const int LETTERS = 26;
  int tests;
  cin >> tests;
  for(int test = 0; test < tests; ++test) {
    vector<string> ciphered(LETTERS);
    for(int i = 0; i < LETTERS; ++i) {
      cin >> ciphered[i];
    }
    string s1, s2;
    cin >> s1 >> s2;
    int m = (int)s2.size();

    string res;
    for(int i = 0; i < m; ++i) {
      res.append(ciphered[s2[i] - 'a']);
    }
    bool ans = (res == s1);
    cout << (ans ? "Yes" : "No") << endl;
  }
}
