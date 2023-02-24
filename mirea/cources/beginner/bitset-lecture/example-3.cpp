#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << (x) << " <-- " << #x << endl

auto flip_simple(auto a,
                  int l,
                  int r)
{
    for (int i = l; i <= r; i++)
        a.flip(i);
    return a;
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
auto flip_faster(bitset<N> a,
                     int l,
                     int r)
{
    thread_local bitset<N> b;
    b.set();
    ((b >>= l) <<= l);
    b <<= (b.size() - r - 1);
    b >>= (b.size() - r - 1);
    a ^= b;
    return a;
}


int main()
{
    setlocale(LC_ALL, "Ru-ru");
    bitset<15> a;
    cin >> a;
    watch(a);
    // (A ^ B) == (A != B)
    watch(flip_simple(a, 3, 7));
    watch(flip_fast(a, 3, 7));
    watch(flip_faster(a, 3, 7));
}