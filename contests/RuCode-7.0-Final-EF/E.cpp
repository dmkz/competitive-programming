#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef pair<ull, ull> state_t;

int n;
string s;
bool ans;

void read() {
  cin >> s;
  n = (int)s.size();
}

void write() {
  cout << (ans ? "Alice" : "Bob") << '\n';
}

const int B = 64;
const int K = 8;
const int CHARS = 1 << 8;
ull KNIGHT[B];
ull BISHOP[B];
ull ROOK[B];
ull QUEEN[B];
ull ARCH[B];
ull CANC[B];
ull MAG[B];
//template<typename T>
//void
//hash_combine(std::size_t &seed, T const &key) {
//  std::hash<T> hasher;
//  seed ^= hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//}
//template<typename T1, typename T2>
//struct hash<std::pair<T1, T2>> {
//  std::size_t operator()(std::pair<T1, T2> const &p) const {
//    std::size_t seed1(0);
//    ::hash_combine(seed1, p.first);
//    ::hash_combine(seed1, p.second);
//
//    std::size_t seed2(0);
//    ::hash_combine(seed2, p.second);
//    ::hash_combine(seed2, p.first);
//
//    return std::min(seed1, seed2);
//  }
//};
//unordered_map<state_t, bool> win;
bool dfs(state_t &cur, int ind) {
  bool res = false;
  if (ind == n) {
    return res;
  }
  ull* masks;
  char c = s[ind];
  switch (c) {
    case 'B': masks = BISHOP; break;
    case 'R': masks = ROOK; break;
    case 'Q': masks = QUEEN; break;
    case 'A': masks = ARCH; break;
    case 'C': masks = CANC; break;
    case 'M': masks = MAG; break;
    default: assert(false);
  }
  auto &[attacked, pieces] = cur;
  for (int i = 0; i < B && !res; ++i) {
    bool not_attacked = (((attacked >> i) & 1) == 0);
    bool not_attacking = ((masks[i] & pieces) == 0);
    if (not_attacked && not_attacking) {
      state_t next = cur;
      next.first |= masks[i];
      next.second |= 1ULL << i;
      if (!dfs(next, ind + 1)) {
        res = true;
      }
    }
  }
  return res;
}

void solve() {
  const vector<pii> KNIGHT_SHIFTS = {
    {-2, 1}, {-1, 2}, {1, 2}, {2, 1},
    {2, -1}, {1, -2}, {-1, -2}, {-2, -1}
  };
  const vector<pii> BISHOP_DIRS = {
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
  };
  const vector<pii> ROOK_DIRS = {
    {1, 0}, {-1, 0}, {0, -1}, {0, 1}
  };
  auto wb = [&](int x, int y) {
    return ((0 <= x && x < K) && (0 <= y && y < K));
  };

  for (int i = 0; i < B; ++i) {
    int x = i >> 3;
    int y = i & 0b111;
    KNIGHT[i] |= 1ULL << i;
    for (auto &[dx, dy] : KNIGHT_SHIFTS) {
      int nx = x + dx;
      int ny = y + dy;
      if (wb(nx, ny)) {
        KNIGHT[i] |= 1ULL << ((nx << 3) | ny);
      }
    }
    BISHOP[i] |= 1ULL << i;
    for (auto &[dx, dy] : BISHOP_DIRS) {
      for (int len = 1; len <= 8; ++len) {
        int nx = x + dx * len;
        int ny = y + dy * len;
        if (wb(nx, ny)) {
          BISHOP[i] |= 1ULL << ((nx << 3) | ny);
        }
      }
    }
    ROOK[i] |= 1ULL << i;
    for (auto &[dx, dy] : ROOK_DIRS) {
      for (int len = 1; len <= 8; ++len) {
        int nx = x + dx * len;
        int ny = y + dy * len;
        if (wb(nx, ny)) {
          ROOK[i] |= 1ULL << ((nx << 3) | ny);
        }
      }
    }
    QUEEN[i] = BISHOP[i] | ROOK[i];
    ARCH[i]  = BISHOP[i] | KNIGHT[i];
    CANC[i]  = ROOK[i]   | KNIGHT[i];
    MAG[i]   = QUEEN[i]  | KNIGHT[i];
  }
  state_t start;
  ans = dfs(start, 0);
}

signed main() {
  int tests = 1;
  while (tests --> 0) {
    read();
    solve();
    write();
  }
  cout.flush();
  return 0;
}
