// Задача: I, Вердикт: OK, Время: 0.506s, Память: 3.96Mb
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int ll
using ll = long long;
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
const int AMAX = (int)1e9;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
// общение с программой Жюри:
vi ask(const vi& b) {
    // самопроверка на ограничения по b:
    for (auto &it : b)
        assert(0 <= it && it <= AMAX);
    // задаём вопрос:
    std::cout << "?";
    for (auto it : b)
        std::cout << ' ' << it;
    std::cout << std::endl;
    // читаем ответ в 1-индексации:
    vi res(isz(b));
    for (auto &it : res)
        std::cin >> it;
    // делаем 0-индексацию:
    for (auto &it : res)
        it--;
    return res;
}
void answer(const vi &a) {
    std::cout << "!";
    for (auto it : a)
        std::cout << ' ' << it;
    std::cout << std::endl;
}
// решение задачи:
void solve() {
    int n; std::cin >> n;
    // задав запрос, в котором все b[i] == 0, найдём позицию нуля в массиве:
    vi sortedIndexes = ask(vi(n, 0));
    int zero = sortedIndexes.front();
    // введём массивы L и R, которые будут хранить текущие границы отрезка для элемента
    // будем считать что L[i] <= a[i] <= R[i]
    vi L(n, 0), R(n, AMAX), b(n);
    L[zero] = R[zero] = 0; // мы точно знаем где стоит 0
    // запускаем бинарный поиск:
    for (int step = 0; step < 30; ++step) {
        // проверяем условие выхода из бинпоиска:
        int mxLen = 1;
        for (int i = 0; i < n; i++)
            setmax(mxLen, R[i] - L[i] + 1);
        if (mxLen == 1)
            break;
        // теперь мы можем одним запросом поделить все отрезки примерно пополам
        // для этого сначала подберём b[i] такие, чтобы левые границы всех отрезков
        // совпали, ведь b[i] - это просто сдвиг:
        // L[i] <= a[i] <= R[i] => L[i]+b[i] <= a[i]+b[i] <= R[i]+b[i]
        int mxLeft = *std::max_element(all(L));
        for (int i = 0; i < n; i++)
            b[i] = mxLeft - L[i];
        // теперь нужно выбрать mid который будем спрашивать:
        // середину максимального отрезка:
        int mid = mxLeft + mxLen / 2;
        b[zero] = mid; // выставляем ноль в границу бинпоиска:
        // теперь все наши элементы отсортируются относительно zero
        
        // могло получиться так, что можно выгоднее поделить отрезки, сделав +/- 1
        // к элементу b[i]. Проверим это:
        
        // если элемент, стоящий слева от нуля, так и остался там, то он был <= mid
        // а если он оказался справа, то он стал > mid
        for (int i = 0; i < zero; i++) {
            // границы
            int Li = L[i] + b[i], Ri = R[i] + b[i];
            // мы получим либо [Li, mid], либо [mid+1, Ri] (в зависимости от ответа жюри)
            int leftLen = mid - Li + 1;
            int rightLen = Ri - (mid + 1) + 1;
            if (leftLen - 1 > rightLen) {
                // можно поделить отрезок получше, уменьшив left, но увеличив right
                b[i]++;
            } else if (leftLen + 1 < rightLen) {
                // можно поделить отрезок получше, уменьшив right, но увеличив left
                b[i]--;
            }
        }
        // если элемент, стоящий справа от нуля, после запроса переместился налево,
        // то значит, что он был строго меньше mid, иначе он >= mid
        for (int i = zero + 1; i < n; i++) {
            // границы
            int Li = L[i] + b[i], Ri = R[i] + b[i];
            // мы получим либо [Li, mid-1], либо [mid, Ri]
            int leftLen = (mid-1) - Li + 1;
            int rightLen = Ri - mid + 1;
            if (leftLen - 1 > rightLen) {
                // можно поделить отрезок получше
                b[i]++;
            } else if (leftLen + 1 < rightLen) {
                // можно поделить отрезок получше
                b[i]--;
            }
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
        // теперь задаём вопрос:
        vi res = ask(b);
        // обрабатываем ответы:
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
    }
    answer(L);
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
