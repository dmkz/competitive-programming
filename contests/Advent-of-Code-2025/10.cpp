#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vs = std::vector<std::string>;
using ld = double;
using vd = std::vector<ld>;
using vvd = std::vector<vd>;
using vb = std::vector<bool>;
const ld eps = 1e-2;
bool isAlmostEqual(ld a, ld b) {
    ld d = std::abs(a - b);
    return d <= std::max<ld>(1, std::abs(a)) * eps;
}
int parseFinalState(const std::string &s, int *sz = nullptr) {
    assert(s.front() == '[');
    assert(s.back() == ']');
    int res = 0;
    for (int i = 1; i + 1 < isz(s); i++)
        if (s[i] == '#')
            res |= (1 << (i-1));
    if (sz)
        *sz = isz(s)-2;
    return res;
}
bool isOpenBracket(char c) {
    return (c == '[' || c == '{' || c == '(');
}
bool isClosedBracket(char c) {
    return (c == ']' || c == '}' || c == ')');
}
vi parseVec(std::string s) {
    assert(isOpenBracket(s.front()));
    assert(isClosedBracket(s.back()));
    s.back() = ',';
    size_t p = 1;
    vi res;
    while (p < s.size()) {
        size_t next = s.find(',', p);
        assert(next != s.npos);
        res.push_back(std::stoi(s.substr(p, next-p)));
        p = next+1;
    }
    return res;
}
vi parseVolts(const std::string &s) {
    return parseVec(s);
}
vi parseSteps(const vs & vec, int begin, int end) {
    vi steps;
    for (int i = begin; i < end; i++) {
        steps.push_back(0);
        for (int id : parseVec(vec[i]))
            steps.back() |= (1 << id);
    }
    return steps;
}
const int inf = (int)1e9+7;
int bfs(int s, int f, const vi &steps, int n) {
    vi dist(1 << n, inf);
    std::queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        if (u == f)
            return dist[u];
        for (int mask : steps) {
            int v = u ^ mask;
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return inf;
}
void solveEasy() {
    std::string s;
    vi destination, sz;
    vvi steps;
    vvi volts;
    while (std::getline(std::cin, s)) {
        std::vector<std::string> blocks;
        std::stringstream ss(s);
        for (std::string temp; ss >> temp; )
            blocks.push_back(temp);
        // парсим
        sz.push_back(0);
        destination.push_back(parseFinalState(blocks.front(), &sz.back()));
        steps.push_back(parseSteps(blocks, 1, isz(blocks)-1));
        volts.push_back(parseVolts(blocks.back()));
    }
    ll answ{};
    for (int i = 0; i < isz(destination); i++)
        answ += bfs(0, destination[i], steps[i], sz[i]);
    std::cout << answ << std::endl;
}
int gauss(vvd &A, vb &isBasis, const int nRows, const int nCols) {
    int rank = 0;
    for (int c = 0; rank < nRows && c < nCols; c++) {
        int maxR = -1;
        for (int r = rank; r < nRows; r++)
            if (maxR == -1 || std::abs(A[r][c]) > std::abs(A[maxR][c]))
                maxR = r;
        if (maxR == -1)
            break;
        if (std::abs(A[maxR][c]) < eps)
            continue;
        std::swap(A[maxR], A[rank]);
        for (int r = 0; r < nRows; r++) {
            if (r == rank) continue;
            // coeff * A[rank][c] + A[r][c] = 0
            ld coeff = -A[r][c] / A[rank][c];
            for (int k = c; k < nCols; k++)
                A[r][k] += coeff * A[rank][k];
        }
        for (int k = nCols-1; k >= c; k--)
            A[rank][k] /= A[rank][c];
        assert(0 <= c && c < isz(isBasis));
        isBasis[c] = 1;
        rank++;
    }
    return rank;
}
void solveHard() {
    std::string s;
    vi destination, sz;
    vvi steps;
    vvi volts;
    while (std::getline(std::cin, s)) {
        std::vector<std::string> blocks;
        std::stringstream ss(s);
        for (std::string temp; ss >> temp; )
            blocks.push_back(temp);
        // парсим
        sz.push_back(0);
        destination.push_back(parseFinalState(blocks.front(), &sz.back()));
        steps.push_back(parseSteps(blocks, 1, isz(blocks)-1));
        volts.push_back(parseVolts(blocks.back()));
    }
    ll totalAnsw{};
    for (int id = 0; id < isz(destination); id++) {
        // строим систему линейных уравнений
        const int nRows = sz[id];
        const int nCols = isz(steps[id]);
        // решаем систему:
        // x[i] * steps[i] == volts[i]
        auto isSolution = [&](const vd &values) {
            vd want(nRows);
            for (int i = 0; i < isz(volts[id]); i++)
                want[i] = volts[id][i];
            for (int stepId = 0; stepId < isz(steps[id]); stepId++) {
                for (int bit = 0; bit < nRows; bit++) {
                    if ((steps[id][stepId] >> bit) & 1) {
                        want[bit] -= values[stepId];
                    }
                }
            }
            bool result = true;
            for (auto it : want)
                result &= isAlmostEqual(it, 0);
            return result;
        };
        vvd A(nRows, vd(nCols+1));
        for (int r = 0; r < nRows; r++) {
            for (int c = 0; c < nCols; c++)
                A[r][c] = (steps[id][c] >> r) & 1;
            A[r].back() = volts[id][r];
        }
        vb isBasis(nCols);
        int rank = gauss(A, isBasis, nRows, nCols+1);
        std::cout << "A:\n";
        for (int r = 0; r < nRows; r++) {
            for (int c = 0; c < nCols; c++)
                std::cout << ' ' << A[r][c];
            std::cout << " | " << A[r].back();
            std::cout << std::endl;
        }
        std::cout << "rank = " << rank << std::endl;
        std::cout << "System #" << id << ": rank = " << rank << ", sz = " << nCols << ", brute = " << nCols - rank << std::endl;
        int nBrute = nCols - rank;
        int answ = inf;
        if (nBrute == 0) {
            vd values(nRows);
            answ = 0;
            for (int r = 0; r < nRows; r++) {
                values[r] = A[r].back();
                answ += (int)std::round(A[r].back());
            }
            assert(isSolution(values));
        } else if (nBrute == 3) {
            vi bruteIndex;
            for (int i = 0; i < isz(isBasis); i++)
                if (!isBasis[i])
                    bruteIndex.push_back(i);
            vd values(nCols);
            // более быстрый вариант:
            const int sum = std::accumulate(all(volts[id]), 0);
            size_t iters = 0;
            for (int cnt0 = 0; cnt0 <= sum; cnt0++) {
                for (int cnt1 = 0; cnt1 <= sum - cnt0; cnt1++) {
                    for (int cnt2 = 0; cnt2 <= sum - cnt0 - cnt1; cnt2++) {
                        iters++;
                        values[bruteIndex[0]] = cnt0;
                        values[bruteIndex[1]] = cnt1;
                        values[bruteIndex[2]] = cnt2;
                        int row = 0;
                        for (int i = 0; i < isz(values); i++) {
                            if (isBasis[i]) {
                                ld temp = A[row].back();
                                for (int j = 0; j < isz(bruteIndex); j++) {
                                    int colId = bruteIndex[j];
                                    assert(0 <= row && row < isz(A));
                                    assert(0 <= colId && colId < isz(A[row]));
                                    temp -= values[colId] * A[row][colId];
                                }
                                values[i] = temp;
                                row++;
                            }
                        }
                        //assert(isSolution(values));
                        int currRes = 0, ok = 1;
                        for (int i = 0; i < isz(values); i++)
                            if (values[i] >= -eps && isAlmostEqual(std::round(values[i]),values[i])) {
                                currRes += (int)std::round(values[i]);
                            } else {
                                ok = false;
                            }
                        if (ok && answ > currRes)
                            answ = currRes;
                        if (iters % (int)1e6 == 0) {
                            std::cout << iters << " completed" << std::endl;
                        }
                    }
                }
            }
        } else {
            vi bruteIndex;
            for (int i = 0; i < isz(isBasis); i++)
                if (!isBasis[i])
                    bruteIndex.push_back(i);
            vi bruteValue(isz(bruteIndex));
            vd values(nCols);
            std::function<void(int,int)> dfs = [&](int pos, int sum) {
                if (pos == isz(bruteValue)-1) {
                    bruteValue.back() = sum;
                    for (int i = 0; i < isz(bruteValue); i++) {
                        assert(bruteIndex[i] < isz(values));
                        values[bruteIndex[i]] = bruteValue[i];
                    }
                    int row = 0;
                    for (int i = 0; i < isz(values); i++) {
                        if (isBasis[i]) {
                            ld temp = A[row].back();
                            for (int j = 0; j < isz(bruteValue); j++) {
                                int colId = bruteIndex[j];
                                assert(0 <= row && row < isz(A));
                                assert(0 <= colId && colId < isz(A[row]));
                                temp -= bruteValue[j] * A[row][colId];
                            }
                            values[i] = temp;
                            row++;
                        }
                    }
                    // ПРОВЕРКА
                    //assert(isSolution(values));
                    // обновляем ответ:
                    int currRes = 0, ok = 1;
                    for (int i = 0; i < isz(values); i++)
                        if (values[i] >= -eps && isAlmostEqual(std::round(values[i]),values[i])) {
                            currRes += (int)std::round(values[i]);
                        } else {
                            ok = false;
                        }
                    if (ok && answ > currRes)
                        answ = currRes;
                    return;
                }
                for (int val = 0; val <= sum; val++) {
                    bruteValue[pos] = val;
                    dfs(pos+1, sum - val);
                }
            };
            const int maxSum = std::accumulate(all(volts[id]), 0);
            for (int sum = 0; sum <= maxSum; sum++)
                dfs(0, sum);
        }
        assert(answ < inf);
        std::cout << "presses: " << answ << std::endl;
        totalAnsw += answ;
    }
    std::cout << totalAnsw << std::endl;
}
main() {
    solveHard();
}
