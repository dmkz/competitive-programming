#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// Задача: G, Вердикт: OK, Время: 0.58s, Память: 198.64Mb

// Длина лучшего ответа не превосходит sqrt(n), потому что всегда можно разбить
// нашу строку на последовательность из чисел длины 1, 2, 3, 4, ..., sqrt(n).
// Переберём длину ответа и для каждой длины проверим, можно ли её достичь
// Чтобы не перебирать одни и те же варианты несколько раз, используем технику
// динамического программирования с запоминанием, какие варианты мы уже перебрали

// --- Блок суффиксных структур данных ---
// Строим суффиксный массив (алгоритм сортировки циклических сдвигов, O(n log n)).
// Это даст порядок всех суффиксов строки по возрастанию и позиции каждого суффикса в этом порядке. [Теория: cp-algorithms]
static vector<int> sort_cyclic_shifts(const string &s) {
    int n = (int)s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[(unsigned char)s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[(unsigned char)s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int,int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

static vector<int> build_suffix_array(const string &s) {
    // Добавляем минимальный страж '$' и сортируем циклические сдвиги,
    // затем удаляем позицию стража и получаем SA исходной строки. [Теория: cp-algorithms]
    string t = s;
    t.push_back(' '); // символ меньше любого другого (эквивалент '$' для байтов)
    vector<int> p = sort_cyclic_shifts(t);
    p.erase(p.begin()); // убрать позицию стража
    return p;
}

// Алгоритм Касаи: строит массив LCP между соседними суффиксами в порядке SA за O(n).
// lcp[i] = LCP(suffix at SA[i], suffix at SA[i+1]). [Теория: cp-algorithms]
static vector<int> build_lcp_kasai(const string &s, const vector<int> &sa) {
    int n = (int)s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int k = 0;
    vector<int> lcp(max(0, n - 1), 0);
    for (int i = 0; i < n; i++) {
        int r = rank[i];
        if (r == n - 1) { // у последнего в SA нет правого соседа
            k = 0;
            continue;
        }
        int j = sa[r + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[r] = k;
        if (k) k--;
    }
    return lcp;
}

// Sparse Table (RMQ) для минимума на массиве LCP: предобработка O(n log n), запрос O(1).
// Работает на неизменяемых массивах, что нам подходит (LCP фиксирован). [Теория: sparse table]
struct SparseTable {
    int N = 0, K = 0;
    vector<int> lg;
    vector<vector<int>> st;
    void build(const vector<int> &a) {
        N = (int)a.size();
        if (N == 0) { K = 0; lg.assign(1, 0); st.clear(); return; }
        lg.assign(N + 1, 0);
        for (int i = 2; i <= N; i++) lg[i] = lg[i >> 1] + 1;
        K = lg[N];
        st.assign(K + 1, vector<int>(N));
        st[0] = a;
        for (int k = 1; k <= K; k++) {
            for (int i = 0; i + (1 << k) <= N; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    inline int rmq(int L, int R) const {
        if (L > R) return 0; // пустой диапазон для безопасности
        int k = lg[R - L + 1];
        return min(st[k][L], st[k][R - (1 << k) + 1]);
    }
};

// --- Конец блока суффиксных структур данных ---

string solve(const string &s) {
    // Предобработка для LCP(i, j) за O(1):
    // 1) строим SA и rank; 2) строим LCP по Касаи; 3) строим RMQ по LCP (sparse table);
    // 4) реализуем LCP_suffix(i, j) через RMQ по отрезку lcp[rank[i]..rank[j]-1]. [Идея: LCP двух суффиксов = минимум lcp между ними в SA]
    // Это стандартная редукция LCP-запросов к RMQ по lcp-массиву. 
    const int n = (int)s.size();
    const vector<int> sa = build_suffix_array(s); // SA: индексы суффиксов в отсортированном порядке
    vector<int> rank(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i; // rank[pos] = позиция суффикса pos в SA
    const vector<int> lcp = build_lcp_kasai(s, sa); // lcp[i] = LCP(SA[i], SA[i+1])
    SparseTable st;
    st.build(lcp);

    // LCP(i, j) за O(1):
    // Возвращает длину наибольшего общего префикса двух суффиксов s[i..] и s[j..].
    // Если обозначить r1 = rank[i], r2 = rank[j], то LCP(s[i..], s[j..]) = min(lcp[r1], lcp[r1+1], ..., lcp[r2-1]).
    // Значение минимума берём через RMQ по sparse table. Граница учитывает, что lcp[i] хранит смежные пары в SA. 
    auto lcp_suffix = [&](int i, int j) -> int {
        if (i == j) return n - i;          // совпадающие суффиксы: весь конец строки
        int r1 = rank[i], r2 = rank[j];
        if (r1 > r2) swap(r1, r2);         // хотим минимум на [r1 .. r2-1]
        return st.rmq(r1, r2 - 1);         // O(1) на запрос после предобработки
    };

    // сравнение подстрок s[a...b] > s[c...d] как чисел
    // Заменяем memcmp на сравнение через LCP:
    // 1) Если длины различаются — больше та, у которой длина больше.
    // 2) Иначе находим общую длину совпадения L = min(LCP(a, c), длина), и сравниваем первый несовпадающий символ.
    auto isGreater = [&](int a, int b, int c, int d) -> bool {
        int len1 = b - a + 1, len2 = d - c + 1;
        if (len1 != len2) return len1 > len2; // как числа: больше тот, у кого больше цифр
        int L = min(lcp_suffix(a, c), len1);  // общая совпадающая часть в пределах длины
        if (L == len1) return false;          // строки равны -> не строго больше
        return s[a + L] > s[c + L];           // первый несовпадающий символ решает
    };

    // находим ограничение на максимальный ответ
    int maxAnswer = 1;
    while (maxAnswer * (maxAnswer+1) / 2 <= n)
        maxAnswer++;
    // выделяем память под хранение результатов вычисления динамики
    vector canLeft(n+1, vector<bool>(maxAnswer+1, false));
    vector canRight(n+1, vector<bool>(maxAnswer+1, false));
    vector canLeftSum(n+1, vector<int16_t>(maxAnswer+1, 0));
    vector canRightSum(n+1, vector<int16_t>(maxAnswer+1, 0));
    for (int len = 1; len <= n; len++) {
        for (int last = 1; last <= min(len, maxAnswer); last++) {
            // можно ли выбрать возрастающую последовательность на префиксе
            // s[0 ... len-1] так, чтобы последнее число имело длину last?
            
            // можем, если можем для префикса s[0 ... len - last] выбрать
            // подпоследоследовательность, оканчивающуюся на число длины < last:
            // проверяем сначала меньшие предыдущие длины:
            bool ok = (canLeftSum[len - last][last - 1] > 0);
            if (ok) {
                canLeft[len][last] = true;
            } else {
                // иначе единственный вариант - нужно проверить такую же длину
                // для этого сравниваем подстроки лексикографически. справа должна
                // быть бОльшая
                int pos = len - 2 * last;
                if (pos >= 0 && canLeft[len - last][last] &&
                    isGreater(pos + last, len - 1, pos, pos + last - 1))
                {
                    canLeft[len][last] = true;
                }
            }
        }
        // крайний случай когда берём весь префикс как одно число:
        if (len <= maxAnswer && !canLeft[len][len])
            canLeft[len][len] = true;
        // предподсчитываем префикс-суммы для текущего столбца на будущее:
        canLeftSum[len][0] = canLeft[len][0];
        for (int i = 1; i <= maxAnswer; i++)
            canLeftSum[len][i] = canLeftSum[len][i-1] + canLeft[len][i];
    }
    // аналогично, но теперь справа-налево
    for (int len = 1; len <= n; len++) {
        for (int last = 1; last <= min(len, maxAnswer); last++) {
            // можно ли выбрать убывающую последовательность на суффиксе
            // s[n-len ... n-1] так, чтобы самое левое число имело длину last?
            
            // можем, если можем для суффикса s[n-len+last ... n-1] выбрать
            // подпоследоследовательность, самое левое число которой имеет
            // длину < last:
            bool ok = (canRightSum[len - last][last - 1] > 0);
            if (ok) {
                canRight[len][last] = true;
            } else {
                // иначе нужно проверять такую же длину
                // число слева должно быть больше чем число справа
                int pos = n - len;
                if (pos + 2 * last <= n && canRight[len - last][last] &&
                    isGreater(pos, pos + last - 1, pos + last, pos + 2 * last - 1))
                {
                    canRight[len][last] = true;
                }
            }
        }
        // крайний случай, когда мы берём весь суффикс как число
        if (len <= maxAnswer && !canRight[len][len])
            canRight[len][len] = true;
        // предподсчитываем префикс-суммы для текущего столбца на будущее:
        canRightSum[len][0] = canRight[len][0];
        for (int i = 1; i <= maxAnswer; i++)
            canRightSum[len][i] = canRightSum[len][i-1] + canRight[len][i];
    }
    // выбираем лучший ответ:
    auto answer = make_pair(n, s);
    for (int prefLen = 1; prefLen <= maxAnswer; prefLen++)
        if (canRight[n][prefLen]) { // лучший префикс
            answer = min(answer, make_pair(prefLen, s.substr(0, prefLen)));
            break;
        }
    for (int suffLen = 1; suffLen <= maxAnswer; suffLen++)
        if (canLeft[n][suffLen]) { // лучший суффикс
            answer = min(answer, make_pair(suffLen, s.substr(n - suffLen, suffLen)));
            break;
        }
    return answer.second; // возвращаем ответ
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    cout << solve(s) << '\n';
    return 0;
}