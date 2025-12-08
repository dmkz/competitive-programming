#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int ll
void assert_tle(bool q) {
    static size_t count = 0;
    while (!q) count++;
}
//#define TEST 1
using ll = long long;
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
const int AMAX = (int)1e9;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
int juryN = 2;
vi juryA = {0, 1};
int juryQueries = 0;
const bool debug = 0;

vi ask(const vi& b) {
    for (auto &it : b)
        assert_tle(0 <= it && it <= AMAX);
#ifdef TEST
    juryQueries++;
#endif
    if (debug) {
        std::cout << std::string(40,'-') << std::endl;
        std::cout << "Start Query #" << juryQueries << std::endl;
    }
#ifdef TEST
    vpii c(isz(b));
    for (int i = 0; i < isz(c); i++)
        c[i] = {juryA[i] + b[i], i+1};
    std::sort(all(c));
    vi res(isz(c));
    for (int i = 0; i < isz(c); i++)
        res[i] = c[i].second;
#else
    std::cout << "?";
    for (auto it : b)
        std::cout << ' ' << it;
    std::cout << std::endl;
    vi res(isz(b));
    for (auto &it : res)
        std::cin >> it;
#endif
    // сделать 0-индексацию
    for (auto &it : res)
        it--;
    if (debug) {
        std::cout << "receive:";
        for (auto it : res) std::cout << ' ' << it;
        std::cout << std::endl;
    }
    return res;
}
void answer(const vi &a) {
    std::cout << "!";
    for (auto it : a)
        std::cout << ' ' << it;
    std::cout << std::endl;
#ifdef TEST
    assert(a == juryA);
    assert(juryQueries <= 31);
    std::cout << "Answer has been accepted!" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
#endif
}
void solve() {
#ifdef TEST
    int n = juryN;
    std::cout << "Jury: n = " << n << ", a =";
    for (auto it : juryA) std::cout << ' ' << it;
    std::cout << std::endl;
#else
    int n; std::cin >> n;
#endif
    vi sortedIndexes = ask(vi(n, 0));
    int zero = sortedIndexes.front();
    vi L(n, 0), R(n, AMAX), b(n);
    L[zero] = R[zero] = 0; // мы точно знаем где стоит 0
    for (int i : sortedIndexes) {
        if (i == zero) continue;
        if (i < zero) { // справа стоит элемент, который был левее
            L[i] = 1;
        }
    }
    for (int step = 0; step < 30; ++step) {
        if (debug) {
            std::cout << "Before Query #" << juryQueries+1 << ":\n";
            for (int i = 0; i < n; i++)
                std::cout << "    Item #" << i << ": [" << L[i] << ", " << R[i] << "]" << std::endl;
        }
        int mxLen = 1;
        for (int i = 0; i < n; i++)
            setmax(mxLen, R[i] - L[i] + 1);
        if (mxLen == 1)
            break;
        // наша задача сделать так, чтобы все левые границы совпали:
        int mxLeft = *std::max_element(all(L));
        for (int i = 0; i < n; i++)
            b[i] = mxLeft - L[i];
        // теперь нужно выбрать mid который будем спрашивать
        int mid = mxLeft + mxLen / 2;
        b[zero] = mid;
        if (debug) {
            std::cout << "mxLeft = " << mxLeft << ", mxRight = " << mxLeft + mxLen - 1 << std::endl;
            std::cout << "mxLen = " << mxLen << std::endl;
        }
        auto printBalance = [&](int i) {
            std::cout << "Item #" << i << " balance: ";
            if (i == zero) {
                std::cout << "zero" << std::endl;
            } else if (i < zero) {
                int Li = L[i] + b[i];
                int Ri = R[i] + b[i];
                // мы получим либо [Li, mid], либо [mid+1, Ri]
                int leftLen = mid - Li + 1;
                int rightLen = Ri - (mid + 1) + 1;
                std::cout << "leftLen = " << leftLen << " vs rightLen = " << rightLen << " (i < zero)" << std::endl;
            } else {
                int Li = L[i] + b[i];
                int Ri = R[i] + b[i];
                // мы получим либо [Li, mid-1], либо [mid, Ri]
                int leftLen = (mid-1) - Li + 1;
                int rightLen = Ri - mid + 1;
                std::cout << "leftLen = " << leftLen << " vs rightLen = " << rightLen << " (i > zero)" << std::endl;
            }
        };
        // если элемент, стоящий слева от нуля, так и остался там, то он был <= mid
        // а если он оказался справа, то он стал > mid
        for (int i = 0; i < zero; i++) {
            // границы
            int Li = L[i] + b[i];
            int Ri = R[i] + b[i];
            // мы получим либо [Li, mid], либо [mid+1, Ri]
            int leftLen = mid - Li + 1;
            int rightLen = Ri - (mid + 1) + 1;
            if (debug) {
                std::cout << "i = " << i << "(i < zero)" << std::endl;
                std::cout << "leftLen = " << leftLen << " vs " << rightLen << std::endl;
            }
            if (leftLen - 1 > rightLen) {
                // можно поделить отрезок получше
                if (debug)
                    std::cout << "decide to increase b[i]" << std::endl;
                b[i]++;
            } else if (leftLen + 1 < rightLen) {
                // можно поделить отрезок получше
                b[i]--;
                if (debug)
                    std::cout << "decide to decrease b[i]" << std::endl;
            }
        }
        // если элемент, стоящий справа от нуля, после запроса переместился налево,
        // то значит, что он был строго меньше mid, иначе он >= mid
        for (int i = zero + 1; i < n; i++) {
            // границы
            int Li = L[i] + b[i];
            int Ri = R[i] + b[i];
            // мы получим либо [Li, mid-1], либо [mid, Ri]
            int leftLen = (mid-1) - Li + 1;
            int rightLen = Ri - mid + 1;
            if (debug) {
                std::cout << "i = " << i << "(i > zero)" << std::endl;
                std::cout << "leftLen = " << leftLen << " vs " << rightLen << std::endl;
            }
            if (leftLen - 1 > rightLen) {
                // можно поделить отрезок получше
                if (debug) std::cout << "decide to increase b[i]" << std::endl;
                b[i]++;
            } else if (leftLen + 1 < rightLen) {
                // можно поделить отрезок получше
                b[i]--;
                if (debug) std::cout << "decide to decrease b[i]" << std::endl;
            }
        }
        if (debug) {
            for (int i = 0; i < n; i++)
                printBalance(i);
        }
        // перед тем как задавать вопрос, нужно убедиться, что 0 <= b[i] <= AMAX
        auto [imin, imax] = std::minmax_element(all(b));
        int Min = *imin, Max = *imax;
        if (Min < 0) {
            for (auto &it : b)
                it -= Min;
            mid -= Min;
        } else if (Max > AMAX) {
            for (auto &it : b)
                it -= Max - AMAX;
            mid -= Max - AMAX;
        }
        vi res = ask(b);
        bool wasZero = false;
        for (int i : res) {            
            if (i == zero) wasZero = true;
            else if (!wasZero) {
                // элемент стоит слева от нуля
                // это значит что a[i] + b[i] <= mid, если i < zero
                // и строгое неравенство иначе: a[i] + b[i] <= mid - (i > zero)
                setmin(R[i], mid - (i > zero) - b[i]);
            } else {
                // элемент стоит справа от нуля
                // a[i] + b[i] >= mid, если i > zero
                // и строгое неравенство иначе: a[i] + b[i] >= mid + (i < zero)
                setmax(L[i], mid + (i < zero) - b[i]);
            }
        }
        if (debug) {
            std::cout << "After Query #" << juryQueries << ":\n";
            for (int i = 0; i < n; i++)
                std::cout << "    Item #" << i << ": [" << L[i] << ", " << R[i] << "]" << std::endl;
        }
    }
    answer(L);
}
void stress() {
    for (juryN = 2; juryN <= 10; juryN++) {
        juryA.resize(juryN);
        for (int i = 0; i < juryN; i++)
            juryA[i] = i;
        do {
            juryQueries = 0;
            solve();
        } while (std::next_permutation(all(juryA)));
        std::cout << "N = " << juryN << ": OK " << std::endl;
    }
    std::exit(0);
}
main() {
#ifdef TEST
    stress();
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
#ifdef TEST
    int tt = 1;
#else
    int tt; std::cin >> tt;
#endif
    while (tt --> 0) solve();
}
