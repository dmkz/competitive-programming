#include <bits/stdc++.h>
#ifndef __TIMER_HPP__
#define __TIMER_HPP__
class Timer {
    std::chrono::time_point<std::chrono::steady_clock> timePoint;
    size_t value;
public:
    void start() { timePoint = std::chrono::steady_clock::now(); }
    void finish() {
        auto curr = std::chrono::steady_clock::now();    
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(curr - timePoint);
        value = elapsed.count();
    }
    size_t operator()() const { return value; }
};
#endif // __TIMER_HPP__
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define int ll
using ll = long long;
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
template<typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::pair<A,B> &pr) {
    return os << "{" << pr.first << "," << pr.second << "}";
}
/*
    029A
    Чтобы первый робот набрал 0, его нужно заставить переместиться вторым роботом
    Второго нужно заставить переместиться третьим роботом
    Третьего робота мы двигаем
    
    Первый робот двигается между клетками и требует нажатия на 'A' после каждого завершения передвижения
    
    move1('A', '0'); press1('A');
    move1('0', '2'); press1('A');
*/

auto path1dirs = [](){
    // path1:
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
    // path1:
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
    // path2:
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
    // path2:
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

char getMoves(int id, char from, char what) {
    assert(0 <= id);
    //assert(3 >= id);
    if (id == 0)
        return path1moves[from][what];
    return path2moves[from][what];
}

auto getLetters(int id) {
    assert(0 <= id);
    //assert(3 >= id);
    if (id == 0)
        return std::string("A0123456789");
    return std::string("A<^v>");
}

std::string pattern = "029A";

struct State {
    std::string text, path, robots;
    
    auto toTuple() const {
        return std::make_tuple(text, path, robots);
    }
    
    friend std::ostream &operator<<(std::ostream &os, const State &st) {
        return os << "{text='" << st.text << "',path='" << st.path << "',robots=" << st.robots << "}";
    }
};

struct OptState {
    int16_t text;
    int16_t path{};
    char robots[4]{};
    
    
    
    friend std::ostream &operator<<(std::ostream &os, const OptState &st) {
        return os << "{text='" << st.text << "',path='" << st.path << "',robots='" << st.robots << "'}";
    }
};

int findPrefix(const std::string &text) {
    if (text.size() <= pattern.size() && pattern.substr(0, text.size()) == text)
        return (int)text.size();
    return -10000000;
}

std::pair<int,int> findCoords(char ch) {
    // 789
    // 456
    // 123
    //  0A
    int row = 0;
    if (ch == '7' || ch == '8' || ch == '9')
        row = 0;
    else if (ch == '4' || ch == '5' || ch == '6')
        row = 1;
    else if (ch == '1' || ch == '2' || ch == '3')
        row = 2;
    else if (ch == '0' || ch == 'A')
        row = 3;
    int col = 0;
    if (ch == '0' || ch == '2' || ch == '5' || ch == '8')
        col = 1;
    else if (ch == '9' || ch == '6' || ch == '3' || ch == 'A')
        col = 2;
    return std::make_pair(row, col);
}

int findDist(const std::string &text, const std::string &robots) {
    int pref = findPrefix(text);
    if (pref < 0) return 10000000;
    char need = pattern[pref];
    char have = robots[0];
    auto [r1, c1] = findCoords(need);
    auto [r2, c2] = findCoords(have);
    return std::abs(r1-r2)+std::abs(c1-c2);
}

struct Comp {
    bool operator()(const State &a, const State &b) const {
        // сначала сравниваем текст
        int prefLenA = findPrefix(a.text);
        int prefLenB = findPrefix(b.text);
        if (prefLenA < prefLenB)
            return true;
        if (prefLenA > prefLenB)
            return false;
        if (a.path.size() > b.path.size())
            return true;
        if (a.path.size() < b.path.size())
            return false;
        // расстояние к следующему символу
        int distA = findDist(a.text, a.robots);
        int distB = findDist(b.text, a.robots);
        if (distA > distB) return true;
        if (distA < distB) return false;
        return a.toTuple() > b.toTuple();
    }
};

int numRobots = 3;

std::tuple<std::string, std::string, bool>
process(const std::string &text, const std::string &robots, int id, char ch) {
// id = {0, 1, 2, 3}
// робот под номером id делает действие ch
    assert(0 <= id && id <= numRobots);
    //std::cout << "process(text='" << text << "', robots = '" << robots << "', id = " << id << ", ch = '" << ch << "')"  << std::endl;
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
        if (nextChar) {
            newRobots[id-1] = nextChar;
        }
        return std::make_tuple(text, std::move(newRobots), !!nextChar);
    }
}

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

void part1Research() {
    std::map<std::string, std::map<std::string, std::string>> dist;
    std::priority_queue<State, std::vector<State>, Comp> pq;
    //pq.push(State{"","","AAA"});
    pq.push(State{"02","","2AA"});
    std::string best = "02";
    pattern = "028";
    size_t reviewed = 0;
    Timer timer;
    timer.start();
    while (pq.size()) {
        auto top = pq.top();
        auto [text, path, robots] = top;
        reviewed++;
        if (reviewed % (int)1e6 == 0) {
            std::cout << "reviewed = " << reviewed << std::endl;
            timer.finish();
            std::cout << "time = " << timer() << " ms" << std::endl;
            timer.start();
        }
        pq.pop();
        if (dist[text].find(robots) == dist[text].end() ||
            dist[text][robots].size() > path.size())
        {
            if (text.size() && best.size() < text.size()) {
                best = text;
                std::cout << "reached '" << text << "'" << std::endl << ", path = " << path << ", robots = " << robots << std::endl;
                std::cout << "reviewed = " << reviewed << std::endl;
                while (pq.size()) pq.pop();
            }
            for (char what : getLetters(3)) {
                auto [nextText, nextRobots, ok] = process(text, robots, 3, what);
                if (ok && findPrefix(nextText) >= 0) {
                    path += what;
                    pq.push(State{nextText, path, nextRobots});
                    path.pop_back();
                }
            }
        }        
    }
}

const int inf = (int)1e18+7;

void part1Solve() {
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
            if (ok) {
                dist[mask][str2mask(robots)] = 1;
            }
        }
    }
    for (int t = 0; t < numVert; t++)
        for (int u = 0; u < numVert; u++)
            for (int v = 0; v < numVert; v++)
                setmin(dist[u][v], dist[u][t]+dist[t][v]);
    auto getDist = [&](const std::string &from, const std::string &to) {
        return dist[str2mask(from)][str2mask(to)];
    };
    int64_t answ{};
    std::string s;
    while (std::getline(std::cin, s)) {
        std::string curr = "AAA";
        int currLen{}, multiplier{0};
        for (int i = 0; i < isz(s); i++) {
            std::string next = curr;
            next[0] = s[i];
            if (std::isdigit(s[i]))
                (multiplier *= 10) += (s[i] - '0');
            int currDist = getDist(curr, next);
            //std::cout << "currDist = " << currDist << std::endl;
            currLen += currDist + 1;
            curr = next;
        }
        answ += multiplier * 1LL * currLen;
        //std::cout << currLen << std::endl;
    }
    std::cout << answ << std::endl;
}

template<typename T>
using PQLess = std::priority_queue<T, std::vector<T>, std::greater<T>>;

void part2Experimental(const int numRobs, const std::vector<std::string> &codes) {
    numRobots = numRobs;
    int numVert = 11; // кол-во различных состояний, в которых
                      // могут находиться роботы
    for (int i = 1; i < numRobots; i++)
        numVert *= 5;
    std::cout << "numVert = " << numVert << std::endl;
    // матрица кратчайших расстояний
#ifdef USE_DIJKSTRA
    std::map<int, std::vector<int>> dist;
#else
    std::vector dist(numVert, std::vector(numVert, inf));
#endif
    std::vector adj(numVert, std::vector<int>{});
    // инициализация:
    for (int mask = 0; mask < numVert; mask++) {
        #ifndef USE_DIJKSTRA
            dist[mask][mask] = 0;
        #endif
        for (char ch : getLetters(numRobots)) {
            auto [text, robots, ok] = process("", mask2str(mask), numRobots, ch);
            if (ok) {
                #ifndef USE_DIJKSTRA
                    setmin(dist[mask][str2mask(robots)], 1);
                #else
                    adj[mask].push_back(str2mask(robots));
                #endif
            }
        }
    }
    #ifndef USE_DIJKSTRA
    for (int t = 0; t < numVert; t++)
        for (int u = 0; u < numVert; u++)
            for (int v = 0; v < numVert; v++)
                setmin(dist[u][v], dist[u][t]+dist[t][v]);
    #else
    for (char ch : getLetters(0)) {
        std::string start(numRobots, 'A');
        start.front() = ch;
        int startMask = str2mask(start);
        std::queue<int> q;
        q.push(startMask);
        auto &currDist = (dist[startMask] = std::vector(numVert, inf));
        currDist[startMask] = 0;
        while (q.size()) {
            auto curr = q.front();
            q.pop();
            //std::cout << dist[startMask][curr] << std::endl;
            for (int next : adj[curr]) {
                //std::cout << "dnext = " << dist[startMask][next] << std::endl;
                if (currDist[next] > 1 + currDist[curr]) {
                    currDist[next] = 1 + currDist[curr];
                    q.push(next);
                }
            }
        }
        //std::cout << "calculated " << startMask << std::endl;
    }
    #endif
    auto getDist = [&](const std::string &from, const std::string &to) {
        //std::cout << "requested " << str2mask(from) << std::endl;
        return dist[str2mask(from)][str2mask(to)];
    };
    
    std::cout << "table:\n";
    for (char ch1 : getLetters(numRobots)) {
        for (char ch2 : getLetters(numRobots)) {
            std::string a(numRobots, 'A');
            std::string b(numRobots, 'A');
            a[1] = ch1;
            b[1] = ch2;
            std::cout << getDist(a,b) << ' ';
        }
        std::cout << std::endl;
    }
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
                
    for (int i = numRobots-2; i > 0; i--) {
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "i = " << i << ":\n";
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
                std::cout << dp[i][from][to] << " ";
            }
            std::cout << std::endl;
        }
    }
    {
        const auto &letters0 = getLetters(0);
        std::cout << "letters0='" << letters0 << "'" << std::endl;
        auto getId0 = [&](char ch) { return (int)letters0.find(ch); };
        int64_t totalAnsw{};
        for (auto s : codes) {
            std::string currState(numRobots, 'A');
            std::cout << "read code '" << s << "'" << std::endl;
            int curr = 0;
            int currAnsw = 0;
            int multiplier = 0;
            for (auto ch : s) {
                if (std::isdigit(ch)) {
                    (multiplier *= 10) += (ch - '0');
                }
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
                    //std::cout << "where = " << where << std::endl;
                    //std::cout << "State{" << currDist << "," << letters0[where] << "}" << std::endl;
                    
                    
                    if (where == getId0(ch)) {
                        setmin(best, currDist + dp[1][prev][0]);
                    }
                    //std::cout << "dist = " << dist[where][prev] << std::endl;
                    if (dist[where][prev] > currDist) {
                        //std::cout << "set to " << currDist << std::endl;
                        dist[where][prev] = currDist;
                        for (const auto &[move, next] : path1moves[letters0[where]]) {
                            auto delta = currDist;
                            //std::cout << "prev = " << letters[prev] << ", move = " << move << std::endl;
                            //std::cout << "required = " << dp[1][prev][getId(move)] << std::endl;
                            delta += dp[1][prev][getId(move)] + 1;
                            pq.push({delta, getId0(next), getId(move)});
                        }
                    }
                }
                std::cout << "from " << letters0[curr] << " to " << ch << ": " << best << std::endl;
                std::cout << "check(" << currState << "," << nextState << ") = " << getDist(currState, nextState) << std::endl;
                curr = getId0(ch);
                currAnsw += best+1; // +1 из-за вывода на экран
                currState = nextState;
            }
            std::cout << "multiplier = " << multiplier << std::endl;
            std::cout << "currAnsw = " << currAnsw << std::endl;
            totalAnsw += multiplier * 1LL * currAnsw;
        }
        std::cout << "totalAnsw = " << totalAnsw << std::endl;
    }
}

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
                
    for (int i = numRobots-2; i > 0; i--) {
        //std::cout << std::string(40, '-') << std::endl;
        //std::cout << "i = " << i << ":\n";
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
                //std::cout << dp[i][from][to] << " ";
            }
            //std::cout << std::endl;
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
            //std::cout << "multiplier = " << multiplier << std::endl;
            //std::cout << "currAnsw = " << currAnsw << std::endl;
            totalAnsw += multiplier * 1LL * currAnsw;
        }
        std::cout << "totalAnsw = " << totalAnsw << std::endl;
    }
}

void test1() {
    auto [text, robots, ok] = process("", "0AA", 3, 'A');
    std::cout << "text = " << text << std::endl;
    std::cout << "robots = " << robots << std::endl;
    std::cout << "ok = " << ok << std::endl;
}
void test2() {
    auto [text, robots, ok] = process("", "0>A", 3, 'A');
    std::cout << "text = " << text << std::endl;
    std::cout << "robots = " << robots << std::endl;
    std::cout << "ok = " << ok << std::endl;
}
main() {
    std::vector<std::string> codes;
    for (std::string s; std::getline(std::cin, s); codes.push_back(s));
    part2Final(26, codes);
    //for (int num = 3; num <= 3; num++)
    //    part2Final(num, codes);
    //test1();
    //test2();
    //std::vector<double> a{7, 17, 45, 107, 273, 673, 1685, 4187};
    //for (int i = 1; i < isz(a); i++) {
    //    std::cout << a[i] / a[i-1] << std::endl;
    //}
}


