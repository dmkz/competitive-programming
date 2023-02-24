/*
    // Использовано: 2511 мс, 316 КБ: - обе строки
    // Использовано: 3369 мс, 312 КБ - Ofast
    // Использовано: 8517 мс, 300 КБ - только со второй
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

/*
    без неё: Использовано: 8517 мс, 316 КБ - ни одной строки
*/
#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << (x) << " <-- " << #x << endl

// reverse(a) -- развернуть порядок бит в числе
// 101010100010
// 010001010101

template<size_t N>
auto reverse(bitset<N> a)
{
    for (int i = 0, j = N-1; i < j; i++, j--)
    {
        //swap(a[i], a[j]); - WA
        //auto temp = a[i]; - WA
        // Accepted:
        bool temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    return a;
}


int main()
{
    setlocale(LC_ALL, "Ru-ru");
    bitset<15> a;
    cin >> a;
    watch(a);
    watch(reverse(a));
}