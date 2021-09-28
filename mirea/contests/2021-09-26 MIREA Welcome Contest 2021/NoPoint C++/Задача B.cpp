#include <bits/stdc++.h>
using namespace std;

long long pown(long long n, long long power) {
  long long res = 1;
  for(int i = 0; i < power; ++i) {
    res *= n;
  }
  return res;
}

int main() {
  int tests;
  cin >> tests;
  for(int test = 0; test < tests; ++test) {
    int n;
    cin >> n;
    cout << 3LL * pown(7LL, n) << endl;
  }
}
