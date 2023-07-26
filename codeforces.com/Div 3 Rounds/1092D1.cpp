/*
    problem: 1092D1. Great Vova Wall (Version 1)
    solution: research, brute force, constructive
*/
#include "template.hpp"
#include "debug.hpp"

/*
    решение:
    1. находим максимум и увеличиваем так, чтобы все элементы были равны max или max+1
    2. получили строку из 0 и 1 (остатки от деления на 2). С ней и будем работать
    3. проверку делаем так:
        если последний и предыдущий символ равны,
            то мы можем забыть о них (сможем поменять в любой момент)
            именно: удалить их и продолжить проверку рекурсивно
        иначе мы должны сделать их равными
            для этого находим ближайшую с конца пару равных элементов и
            проводим операции переворачивания пары соседей на суффиксе
            после этого всегда последний будет равен предпоследнему
            удаляем их и продолжаем проверку рекурсивно
            данная операция изменит только первый и последний элемент
            выбранного суффикса
*/

std::string mask2str(int n, int mask) {
    std::string s(n, '?');
    for (int i = 0; i < n; i++)
        s[i] = "01"[getbit(mask,i)];
    return s;
}

bool constructive(std::string &s, int last) {
    if (isz(s) <= 1)
        return true;
    if (isz(s) == 2)
        return s[0] == s[1];
    if (s[isz(s)-1] == s[isz(s)-2])
    {
        s.pop_back();
        s.pop_back();
        return constructive(s, last);
    }
    // находим первую пару равных
    for (int i = std::min(last, isz(s)-2); i >= 0; i--)
        if (s[i] == s[i+1])
        {
            s[i] = '0' - s[i] + '1';
            s.pop_back();
            s.pop_back();
            return constructive(s, i);
        }
    return false;
}

bool constructive(std::string s) {
    return constructive(s, isz(s)-1);
}

template<bool debug = 0>
void research(int n)
{
    vi visited(1 << n);
    vi q = {0, (1 << n) - 1};
    visited[0] = visited[(1<<n)-1] = 1;
    for (int i = 0; i < isz(q); i++)
    {
        for (int j = 0; j + 1 < n; j++)
        {
            int next = q[i];
            if (getbit(next,j) != getbit(next,j+1))
                continue;
            flipbit(next,j);
            flipbit(next,j+1);
            std::string to = mask2str(n,next);
            std::string from = mask2str(n,q[i]);
            watch(from,to);
            if (!visited[next])
            {
                q << next;
                visited[next] = 1;
            }
        }
    }
    std::cout << std::string(40,'-') << std::endl;
    std::cout << "n = " << n << std::endl;
    std::cout << "visited:\n";
    for (int mask = 0; mask < isz(visited); mask++)
    {
        if (visited[mask])
        {
            std::cout << mask2str(n, mask) << std::endl;
            if (!constructive(mask2str(n, mask))) {
                std::cout << "WA on " << mask2str(n, mask) << std::endl;
                std::cout << "expected YES" << std::endl;
            }
        }
    }
    std::cout << "not visited:\n";
    for (int mask = 0; mask < isz(visited); mask++)
    {
        if (!visited[mask])
        {
            std::cout << mask2str(n, mask) << std::endl;
            if (constructive(mask2str(n, mask))) {
                std::cout << "WA on " << mask2str(n, mask) << std::endl;
                std::cout << "expected NO" << std::endl;
            }
        }
    }
    return;
    std::set<vi> ok, bad;
    for (int mask = 0; mask < isz(visited); mask++)
    {
        if (visited[mask])
        {
            ok << segments(mask2str(n, mask));
        }
        else
            bad << segments(mask2str(n, mask));
    }
    for (auto &it : ok)
        std::cout << it << std::endl;
    std::cout << "not visited:\n";
    for (auto &it : bad)
        std::cout << it << std::endl;
}

int main() {
    /*research<1>(3);
    for (int n = 1; n <= 20; n++)
        research(n);
    return 0;
    bool debug = 1;*/
    int n; std::cin >> n;
    vi a(n); std::cin >> a;
    auto max = *std::max_element(all(a));
    std::string s;
    for (auto &it : a)
    {
        // it + 2 * k >= max
        int diff = max - it;
        // 2 * k >= diff
        int k = (diff + 1) / 2;
        it += 2 * k;
        assert(it == max || it == max+1);
        s.push_back("01"[it == max]);
    }
    // now "s" is a sequence of 1 and 0
    // we can invert consecutive pair of equal items
    // 00100 - yes
    // 01101 - yes
    // 010 - no
    // 0100 ?? 0111
    std::cout << (constructive(s) ? "YES\n" : "NO\n");
}
