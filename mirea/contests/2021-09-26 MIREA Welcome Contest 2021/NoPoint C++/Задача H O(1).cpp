#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<double, double> pdd;
typedef pair<int, int> pii;
typedef tuple<double, double, double> td;
#define int ll


void guess(pii ans) {
  cout << "! " << ans.first << ' ' << ans.second << endl;
}

pdd ask(pii point) {
  cout << "? " << point.first << ' ' << point.second << endl;
  cout.flush();
  pdd res;
  cin >> res.first >> res.second;
  return res;
}

int32_t main() {
  const double EPS = 1e-9;
  cout << setprecision(12) << fixed;

  auto get_line = [](pdd vec, pdd from) {
    return td(vec.second, -vec.first, from.second * vec.first - from.first * vec.second);
  };
  auto get_len = [](pdd vec) {
    return sqrtl(vec.first * vec.first + vec.second * vec.second);
  };
  auto det = [](double a, double b, double c, double d) {
    return a * d - b * c;
  };
  auto intersect = [&det](td m, td n) {
    auto &[a1, b1, c1] = m;
    auto &[a2, b2, c2] = n;
    double zn = det(a1, b1, a2, b2);
    return pii(std::round(-det(c1, b1, c2, b2) / zn), std::round(-det(a1, c1, a2, c2) / zn));
  };

  // Точки one и two выбраны таким образом, чтобы на прямой,
  // построенной на этих точках в отрезке [-1e9, 1e9] были
  // только целые точки one и two
  pii one(339697208, 412598734);
  pdd vec1 = ask(one);
  if (get_len(vec1) < EPS) {
    guess(one);
    return 0;
  }
  td line1 = get_line(vec1, one);
  pii two(-579719491, 144305795);
  pdd vec2 = ask(two);
  if (get_len(vec2) < EPS) {
    guess(two);
    return 0;
  }
  td line2 = get_line(vec2, two);

  pii ans = intersect(line1, line2);
  guess(ans);
}
