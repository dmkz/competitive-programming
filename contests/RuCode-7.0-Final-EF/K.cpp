/*
    Идея: мы можем отправить дополнительно 24 * 64 = 1500 бит. То есть,
    примерно 1.5 бит информации на каждое число. Нам хватит и одного бита.
    Для этого для каждого числа отправим 1 бит информации: больше он себя же, но
    ревёрснутого, или меньше. Так мы сможем контролировать, надо ли нам ревёрснуть
    или нет, если выяснится противоречие.
    Чтобы наша дополнительная инфа не пострадала, будем использовать 62 бита из 64
    для каждого дополнительго uint64_t
    Выставим служебные биты:
    - нулевой бит в 0
    - симметричный ему (64-8) бит в 1
    Тогда мы сможем проверить однозначно перевернулся ли наш uint64_t или нет
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()

using Arr = std::array<uint8_t, 8>;
using ull = uint64_t;

Arr ull2arr(ull a) {
// конвертит число в массив байтов
    Arr res;
    for (int i = 0; i < 8; i++)
        res[i] = uint8_t(a >> (8 * i));
    return res;
}

ull arr2ull(Arr a) {
// конвертит массив байтов в число
    ull res = 0;
    for (int i = 7; i >= 0; i--) {
        res <<= 8;
        res |= a[i];
    }
    return res;
}

ull rev(ull x) {
// разворачивает порядок байт на противоположный    
    Arr y = ull2arr(x);
    std::reverse(all(y));
    return arr2ull(y);
}

int getbit(auto x, int i) {
// возвращает i-й бит числа
    return int(x >> i & 1);
}
template<typename T>
void setbit(T &x, int i, int val) {
// устанавливает i-й бит в значение val
    x &= ~(T(1) << i);
    x |= T(val) << i;
}

const int FIXED_POS_OF_ZERO = 0, FIXED_POS_OF_ONE = 64 - 8;

bool isReversed(ull x) {
    return !(getbit(x, FIXED_POS_OF_ZERO) == 0 && getbit(x, FIXED_POS_OF_ONE) == 1);
}

const int GREATER = 1, LESS = 0;

std::vector<ull> encode(std::vector<ull> a) {
// первым элементом записываем количество чисел в оригинальном массиве
// делаем это таким образом, чтобы реверс байт не повлиял на него (палиндром)
    uint16_t sz = uint16_t(a.size());
    uint8_t fi = uint8_t(sz >> 8);
    uint8_t se = uint8_t(sz & ((1ULL << 8) - 1));
    std::vector<ull> kek = {arr2ull({fi,se,0,0,0,0,se,fi})};
// затем запишем сами числа
// затем запишем информацию о каждом числе: 1 бит, больше оно ревёрснутого
// самого себя или нет
// сохраняем доп инфу:
    std::vector<int> additional;
    for (int i = 0; i < isz(a); i++) {
        Arr arr = ull2arr(a[i]);
        int res = 0;
        for (int l = 0, r = 7; l <= r; l++, r--) {
            if (arr[l] != arr[r]) {
                res = (arr[l] < arr[r] ? LESS : GREATER);
                break;
            }
        }
        additional.push_back(res);
    }
// записываем доп. инфу (упаковываем):
    std::vector<ull> extra(1, 0);
    setbit(extra.back(), FIXED_POS_OF_ONE, 1);
    int group = 0, posInGroup = 0;
    int p = 0;
    while (p < isz(additional)) {
        while (true) {
            if (posInGroup == FIXED_POS_OF_ZERO) {
                posInGroup++;
                continue;
            }
            if (posInGroup == FIXED_POS_OF_ONE) {
                setbit(extra.back(), FIXED_POS_OF_ONE, 1);
                posInGroup++;
                continue;
            }
            break;
        }
        setbit(extra.back(), posInGroup, additional[p]);
        posInGroup++;
        if (posInGroup == 64) {
            posInGroup = 0;
            group++;
            extra.push_back(0);
            setbit(extra.back(), FIXED_POS_OF_ONE, 1);
        }
        p++;
    }
    kek.insert(kek.end(), all(a));
    kek.insert(kek.end(), all(extra));
    return kek;
}

std::vector<ull> decode(std::vector<ull> a) {
    int16_t sz = 0;
    {   // извлекаем размер исходного вектора:
        Arr arr = ull2arr(a[0]);
        a.erase(a.begin());
        sz = (uint16_t(arr[0]) << 8) | arr[1];
    }
// извлекаем дополнительную информацию об отношении больше/меньше, которую мы записали:
    std::vector<int> additional;
    int group = sz;
    int posInGroup = 0;
    while (isz(additional) < sz) {
        if (isReversed(a[group]))
            a[group] = rev(a[group]);
        while (true) {
            if (posInGroup == FIXED_POS_OF_ZERO) {
                posInGroup++;
                continue;
            }
            if (posInGroup == FIXED_POS_OF_ONE) {
                posInGroup++;
                continue;
            }
            break;
        }
        additional.push_back(getbit(a[group], posInGroup));
        posInGroup++;
        if (posInGroup == 64) {
            posInGroup = 0;
            group++;
        }
    }
// реверсим порядок байт на основе извлечённой дополнительной инфы:
    a.resize(sz);
    for (int i = 0; i < isz(a); i++) {
        Arr arr = ull2arr(a[i]);
        for (int l = 0, r = 7; l <= r; l++, r--) {
            if (arr[l] != arr[r]) {
                if (additional[i] == LESS && arr[l] > arr[r])
                    a[i] = rev(a[i]);
                else if (additional[i] == GREATER && arr[l] < arr[r])
                    a[i] = rev(a[i]);
                break;
            }
        }
    }
    return a;
}
int main()
{
    std::string s; std::cin >> s;
    int n; std::cin >> n;
    std::vector<ull> a(n);
    for (auto &it : a) std::cin >> it;
    if (s == "decode") {
        a = decode(a);
        for (auto it : a) std::cout << it << ' ';
        std::cout << std::endl;
    }
    if (s == "encode") {
        a = encode(a);
        std::cout << isz(a) << "\n";
        for (auto it : a) std::cout << rev(it) << ' ';
        std::cout << std::endl;
    }
}
