#include <bits/stdc++.h>
using namespace std;

const int mod = (int)1e9+7;

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int add(int a, int b) {
    return (a += b) >= mod ? a - mod : a;
}

int sub(int a, int b) {
    return (a -= b) < 0 ? a + mod : a;
}

int binpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1)
            res = mul(res, a);
        n >>= 1;
        a = mul(a, a);
    }
    return res;
}

int inv(int a) {
    return binpow(a, mod-2);
}

main() {
    // считаем факториалы и обратные факториалы:
    vector<int> fact(1+1000, 1), ifact(1+1000, 1);
    for (int i = 2; i <= 1000; ++i) {
        fact[i] = mul(fact[i-1], i);
        ifact[i] = inv(fact[i]);
    }
    // заполняем массив из лампочек которые горят / не горят
    int n, m;
    cin >> n >> m;
    vector<int> in(n);
    for (int i = 0, v; i < m; ++i) {
        cin >> v;
        in[v-1] = 1;
    }
    // Для каждого подотрезка без лампочек считаем его длину
    // для такого подотрезка (кроме префикса и суффикса), мы можем зажигать
    // лампочку либо слева, либо справа. В итоге 2^(длина подотрезка-1) вариантов
    // Последняя лампочка выбирается единственным способом.
    // Теперь, выбирая последовательность действий, каждый раз мы выбираем
    // подотрезок, в котором будем зажигать лампочку. Если мы пронумеруем
    // подотрезки от 1 до K (их количества), то получится последовательность
    // из чисел от 1 до K. Количество цифры i равно длине i-го подотрезка.
    
    // считаем длины всех непрерывных отрезков из нулей двумя указателями
    vector<int> segLen;
    for (int i = 0, j; i < n; i = j) {
        for (j = i; j < n && in[i] == in[j]; j++);
        // подотрезок [i, j) состоит из символов, равных in[i]
        if (j > i && !in[i])
            segLen.push_back(j-i);
    }
    // считаем ответ. Сначала формируем последовательность из выбранных номеров
    // подотрезков:
    int answ = fact[n - m];
    for (auto len : segLen)
        answ = mul(answ, ifact[len]);
    // теперь для внутренних отрезков считаем количество вариантов их заполнения:
    bool prefixExists = !in[0];
    bool suffixExists = !in[n-1];
    for (int i = prefixExists; i + suffixExists < (int)segLen.size(); i++)
        answ = mul(answ, binpow(2, segLen[i]-1));
    cout << answ << endl;
}
