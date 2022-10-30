#include <bits/stdc++.h>

int main() {
    int n, k; std::cin >> n >> k;
    
    std::vector<int> arr(n);
    for (auto& it : arr)
        std::cin >> it;
    
    // Надо выбрать k максимумов в массиве и сделать так, чтобы
    // каждый максимум принадлежал одному отрезку.
    
    
    // создаём пары (значение, индекс). Будем сортировать их в порядке убывания
    std::vector<std::pair<int,int>> pairs;
    for (int i = 0; i < n; ++i) {
        pairs.push_back(std::make_pair(arr[i], i));
    }
    
    // сортируем в порядке убывания и выбираем ровно k элементов из начала:
    std::sort(pairs.begin(), pairs.end(), std::greater<>());
    pairs.resize(k);
    
    // строим отрезки, где выбранные элементы будут максимумами
    // сначала посчитаем сумму выбранных элементов (sum) и достанем их индексы в вектор
    std::vector<int> indexes;
    int sum = 0;
    for (auto& it : pairs) {
        sum += it.first;
        indexes.push_back(it.second);
    }
    // индексы выбранных элементов нужны в порядке возрастания:
    std::sort(indexes.begin(), indexes.end());
    
    // теперь приводим к тому формату ответа, который требуется:
    // надо вывести количество элементов в каждом отрезке
    // количество элементов в текущем отрезке это:
    // "начало следующего отрезка" минус "начало текущего"
    for (int i = (int)indexes.size()-1; i > 0; --i) {
        indexes[i] -= indexes[i-1];
    }
    
    indexes[0]++; // index[0] - последний элемент первого отрезка, значит
                  // количество элементов в первом отрезке это (index[0] + 1)
    
    // надо увеличить последний отрезок до предела, чтобы arr.back() вошёл в него
    int len = 0;
    for (auto& it : indexes) {
        len += it;
    }
    indexes.back() += n - len;
    
    // выводим ответ:
    std::cout << sum << '\n';
    for (auto& it : indexes) {
        std::cout << it << ' ';
    }
    
    return 0;
}