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

void flip_simple(auto&a,
                  int l,
                  int r)
{
    for (int i = l; i <= r; i++)
        a.flip(i);
    //return a;
}

auto flip_fast(auto a,
                int l,
                int r)
{
    auto b = a; // bitset<N> b = a;
    b.set();
    //watch(l);
    ((b >>= l) <<= l);
    b <<= (b.size() - r - 1);
    b >>= (b.size() - r - 1);
    a ^= b;
    return a;
}

template<size_t N>
void flip_faster(bitset<N> &a,
                     int l,
                     int r)
{
    thread_local bitset<N> b;
    b.set();
    ((b >>= l) <<= l);
    b <<= (b.size() - r - 1);
    b >>= (b.size() - r - 1);
    a ^= b;
}


int main()
{
    setlocale(LC_ALL, "Ru-ru");
    bitset<200200> a;
    int q; cin >> q;
    while (q-->0) {
        int l = rand() % a.size();
        int r = rand() % a.size();
        if (l > r) swap(l, r);
        //flip_faster(a, l, r);
        flip_simple(a, l, r);
    }
    cout << a.count() << endl;
}