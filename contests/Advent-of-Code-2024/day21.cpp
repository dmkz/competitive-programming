#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define int ll
using ll = long long;
void setmin(auto &x, const auto &y) { if (y < x) x = y; }

auto path1dirs = [](){
    // для самого нижнего робота:
    // path1[откуда][куда] = с помощью какого перехода:
    std::map<char, std::map<char, char>> path1;
    path1['A']['0'] = '<';
    path1['A']['3'] = '^';
    path1['0']['A'] = '>';
    path1['0']['2'] = '^';
    path1['1']['2'] = '>';
    path1['1']['4'] = '^';
    path1['2']['0'] = 'v';
    path1['2']['1'] = '<';
    path1['2']['3'] = '>';
    path1['2']['5'] = '^';
    path1['3']['6'] = '^';
    path1['3']['2'] = '<';
    path1['3']['A'] = 'v';
    path1['4']['7'] = '^';
    path1['4']['5'] = '>';
    path1['4']['1'] = 'v';
    path1['5']['2'] = 'v';
    path1['5']['4'] = '<';
    path1['5']['6'] = '>';
    path1['5']['8'] = '^';
    path1['6']['9'] = '^';
    path1['6']['5'] = '<';
    path1['6']['3'] = 'v';
    path1['7']['8'] = '>';
    path1['7']['4'] = 'v';
    path1['8']['5'] = 'v';
    path1['8']['7'] = '<';
    path1['8']['9'] = '>';
    path1['9']['8'] = '<';
    path1['9']['6'] = 'v';
    return path1;
}();

auto path1moves = [](){
    // path1[откуда][какой переход] = куда:
    std::map<char, std::map<char, char>> path1;
    path1['A']['<'] = '0';
    path1['A']['^'] = '3';
    path1['0']['>'] = 'A';
    path1['0']['^'] = '2';
    path1['1']['>'] = '2';
    path1['1']['^'] = '4';
    path1['2']['v'] = '0';
    path1['2']['<'] = '1';
    path1['2']['>'] = '3';
    path1['2']['^'] = '5';
    path1['3']['^'] = '6';
    path1['3']['<'] = '2';
    path1['3']['v'] = 'A';
    path1['4']['^'] = '7';
    path1['4']['>'] = '5';
    path1['4']['v'] = '1';
    path1['5']['v'] = '2';
    path1['5']['<'] = '4';
    path1['5']['>'] = '6';
    path1['5']['^'] = '8';
    path1['6']['^'] = '9';
    path1['6']['<'] = '5';
    path1['6']['v'] = '3';
    path1['7']['>'] = '8';
    path1['7']['v'] = '4';
    path1['8']['v'] = '5';
    path1['8']['<'] = '7';
    path1['8']['>'] = '9';
    path1['9']['<'] = '8';
    path1['9']['v'] = '6';
    return path1;
}();

auto path2dirs = [](){
    // для более верхних уровней:
    // path2[откуда][куда] = с помощью какого перехода:
    std::map<char, std::map<char, char>> path2;
    path2['A']['^'] = '<';
    path2['A']['>'] = 'v';
    path2['^']['A'] = '>';
    path2['^']['v'] = 'v';
    path2['<']['v'] = '>';
    path2['>']['A'] = '^';
    path2['>']['v'] = '<';
    path2['v']['>'] = '>';
    path2['v']['^'] = '^';
    path2['v']['<'] = '<';
    return path2;
}();

auto path2moves = [](){
    // path2[откуда][какой переход] = куда:
    std::map<char, std::map<char, char>> path2;
    path2['A']['<'] = '^';
    path2['A']['v'] = '>';
    path2['^']['>'] = 'A';
    path2['^']['v'] = 'v';
    path2['<']['>'] = 'v';
    path2['>']['^'] = 'A';
    path2['>']['<'] = 'v';
    path2['v']['>'] = '>';
    path2['v']['^'] = '^';
    path2['v']['<'] = '<';
    return path2;
}();

// по номеру робота, его текущему положению и направлению перемещения
// определить, куда он перейдёт
char getMoves(int id, char from, char what) {
    assert(0 <= id);
    if (id == 0)
        return path1moves[from][what];
    return path2moves[from][what];
}

// алфавит на карте для конкретного робота
auto getLetters(int id) {
    assert(0 <= id);
    if (id == 0)
        return std::string("A0123456789");
    return std::string("A<^v>");
}

int numRobots = 3; // количество роботов - глобальная константа

// обработать движение конкретного робота
// text - текущий текст на экране
// robots - положение роботов на картах, например, robots = AAA - стартовое положение
// id = номер робота, который совершает действие
// ch = его действие
std::tuple<std::string, std::string, bool>
process(const std::string &text, const std::string &robots, int id, char ch) {
// id = {0, 1, 2, 3}
// робот под номером id делает действие ch
    assert(0 <= id && id <= numRobots);
    if (id == 0) {
        // печатает на экран тот символ, на котором сейчас стоит
        std::string newText = text;
        newText += robots.front();
        return std::make_tuple(std::move(newText), robots, true);
    }
    assert(id > 0);
    if (ch == 'A') {
        // вынуждает нажатие для робота id-1
        // рекурсивно заставить сделать предыдущего робота то действие
        // на котором он сейчас стоит
        return process(text, robots, id-1, robots[id-1]);
    } else {
        // иначе это перемещение
        // предыдущий робот просто перемещается
        char nextChar = getMoves(id-1, robots[id-1], ch);
        std::string newRobots = robots;
        if (nextChar)
            newRobots[id-1] = nextChar;
        return std::make_tuple(text, std::move(newRobots), !!nextChar);
    }
}

// преобразование строкового представления положения роботов в число
int str2mask(const std::string &robots) {
    int mask = 0;
    for (int i = 0; i < isz(robots); i++) {
        const auto &alp = getLetters(i);
        int j = (int)alp.find(robots[i]);
        mask *= isz(alp);
        mask += j;
    }
    return mask;
}

// преобразование числа в строковое представление положения роботов
std::string mask2str(int mask) {
    std::string robots(numRobots, '?');
    for (int i = isz(robots)-1; i >= 0; i--) {
        const auto &alp = getLetters(i);
        int rem = mask % isz(alp);
        mask /= isz(alp);
        robots[i] = getLetters(i)[rem];
    }
    return robots;
}

const int inf = (int)1e18+7;

void part1Solve(const std::vector<std::string> &codes) {
    int numVert = 11; // кол-во различных состояний, в которых
                      // могут находиться роботы
    for (int i = 1; i < numRobots; i++)
        numVert *= 5;
    // матрица кратчайших расстояний
    std::vector dist(numVert, std::vector(numVert, inf));
    // инициализация:
    for (int mask = 0; mask < numVert; mask++) {
        dist[mask][mask] = 0;
        for (char ch : getLetters(numRobots)) {
            auto [text, robots, ok] = process("", mask2str(mask), numRobots, ch);
            if (ok)
                setmin(dist[mask][str2mask(robots)], 1);
        }
    }
    // Алгоритм Флойда-Уоршелла для поиска кратчайших растояний между всеми парами вершин:
    for (int t = 0; t < numVert; t++)
        for (int u = 0; u < numVert; u++)
            for (int v = 0; v < numVert; v++)
                setmin(dist[u][v], dist[u][t]+dist[t][v]);
    // функция возврата расстояния между двумя состояниями:
    auto getDist = [&](const std::string &from, const std::string &to) {
        return dist[str2mask(from)][str2mask(to)];
    };
    int64_t answ{};
    for (const auto &s : codes) {
        std::string curr = "AAA";
        int currLen{}, multiplier{0};
        for (int i = 0; i < isz(s); i++) {
            std::string next = curr;
            next[0] = s[i];
            if (std::isdigit(s[i]))
                (multiplier *= 10) += (s[i] - '0');
            // идём из curr в next
            int currDist = getDist(curr, next);
            currLen += currDist + 1; // +1 из-за нажатия на кнопку
            curr = next;
        }
        answ += multiplier * 1LL * currLen;
    }
    std::cout << "part1 = " << answ << std::endl;
}

template<typename T>
using PQLess = std::priority_queue<T, std::vector<T>, std::greater<T>>;


void part2Final(const int numRobs, const std::vector<std::string> &codes) {
    // считаем динамику с конца в начало:
    numRobots = numRobs;
    std::vector dp(numRobots, std::vector(5, std::vector(5, inf)));
    // dp[i][a][b] = стоимость получить из aAAA... суффикс ...bAAA
    for (int i = 0; i < 5; i++)
        dp[numRobots-1][i][i] = 0;
    // "A<^v>" - инициализация:
    const std::string letters = "A<^v>";
    auto getId = [&](char ch) { return (int)letters.find(ch); };
    dp.back()[0] = {0, 3, 1, 2, 1};
    dp.back()[1] = {3, 0, 2, 1, 2};
    dp.back()[2] = {1, 2, 0, 1, 2};
    dp.back()[3] = {2, 1, 1, 0, 1};
    dp.back()[4] = {1, 2, 2, 1, 0};
    // поиск в ширину для поиска всех путей между любыми парами вершин:
    std::vector paths(5, std::vector(5, std::set<std::string>{}));
    for (int start = 0; start < 5; start++) {
        // {где, путь}
        std::queue<std::pair<int, std::string>> q;
        q.push({start,""});
        while (q.size()) {
            auto [last, path] = q.front();
            q.pop();
            if (isz(path) <= 3) {
                paths[start][last].insert(path);
            } else {
                continue;
            }
            for (int next = 0; next < 5; next++)
                if (dp.back()[last][next] == 1) {
                    path += path2dirs[letters[last]][letters[next]];
                    q.push({next, path});
                    path.pop_back();
                }
        }
    }
    // динамика:
    for (int i = numRobots-2; i > 0; i--) {
        for (int from = 0; from < 5; from++) {
            for (int to = 0; to < 5; to++) {
                if (from == to) {
                    dp[i][from][to] = 0;
                } else {
                    assert(isz(paths[from][to]));
                    for (const std::string &path : paths[from][to]) {
                        char curr = 'A';
                        int dist = 0;
                        for (char next : path) {
                            dist += dp[i+1][getId(curr)][getId(next)]+1;
                            curr = next;
                        }
                        dist += dp[i+1][getId(curr)][0];
                        setmin(dp[i][from][to], dist);
                    }
                }
            }
        }
    }
    // используя динамику, отвечаем на запросы:
    {
        const auto &letters0 = getLetters(0);
        auto getId0 = [&](char ch) { return (int)letters0.find(ch); };
        int64_t totalAnsw{};
        for (auto s : codes) {
            int curr = 0;
            int currAnsw = 0;
            int multiplier = 0;
            for (auto ch : s) {
                if (std::isdigit(ch))
                    (multiplier *= 10) += (ch - '0');
                std::string nextState(numRobots, 'A');
                nextState.front() = ch;
                std::vector dist(11, std::vector(5, inf));
                PQLess<std::tuple<int64_t, int, int>> pq;
                // (расстояние, позиция последнего робота, позиция предпоследнего)
                pq.push({0,curr,0});
                int best = inf;
                while (pq.size()) {
                    auto [currDist, where, prev] = pq.top();
                    pq.pop();
                    if (where == -1)
                        continue;
                    if (where == getId0(ch)) {
                        setmin(best, currDist + dp[1][prev][0]);
                    }
                    if (dist[where][prev] > currDist) {
                        dist[where][prev] = currDist;
                        for (const auto &[move, next] : path1moves[letters0[where]]) {
                            auto delta = currDist;
                            delta += dp[1][prev][getId(move)] + 1;
                            pq.push({delta, getId0(next), getId(move)});
                        }
                    }
                }
                curr = getId0(ch);
                currAnsw += best+1; // +1 из-за вывода на экран
            }
            totalAnsw += multiplier * 1LL * currAnsw;
        }
        std::cout << "part2 = " << totalAnsw << std::endl;
    }
}

main() {
    std::vector<std::string> codes;
    for (std::string s; std::getline(std::cin, s); codes.push_back(s));
    part1Solve(codes);
    part2Final(26, codes);
}
