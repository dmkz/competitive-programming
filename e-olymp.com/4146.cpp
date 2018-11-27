/*
    Задача: 4146. Двоичное дерево поиска
    
    Решение: SqrtList, O(q * sqrt(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>

template<typename T> class SqrtList {
private:
    const int gsize;
    std::vector<std::vector<T>> data;
    bool (*less)(const T &lhs, const T &rhs);

public:

    SqrtList(bool (*less_)(const T &lhs, const T &rhs), int gsize_ = 256)
        : gsize(gsize_), data(1, std::vector<T>(0)), less(less_) { }

    bool LowerBound(const T& key, int &group, int &pos) const {
        group = (int)data.size()-1, pos = (int)data.back().size();
        if (data.back().empty() || less(data.back().back(), key)) {
            return false;
        }
        // binary search by group:
        int low = -1, high = (int)data.size()-1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (!less(data[mid].back(), key)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        group = high;
        // binary search by position in group:
        const auto& vec = data[group];
        low = -1, high = (int)vec.size()-1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (!less(vec[mid], key)) {
                high = mid;
            } else {
                low = mid;
            }
        }
        pos = high;
        return true;
    }
    
    bool UpperBound(const T& key, int &group, int &pos) const {
        group = (int)data.size()-1, pos = (int)data.back().size();
        if (data.back().empty() || !less(key, data.back().back())) {
            return false;
        }
        // binary search by group:
        int low = -1, high = (int)data.size()-1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (less(key, data[mid].back())) {
                high = mid;
            } else {
                low = mid;
            }
        }
        group = high;
        // binary search by position in group:
        const auto& vec = data[group];
        low = -1, high = (int)vec.size()-1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (less(key, vec[mid])) {
                high = mid;
            } else {
                low = mid;
            }
        }
        pos = high;
        return true;
    }
    
    bool Next(int &group, int &pos) const {
        if (0 > group || (int)data.size() <= group ||
            0 > pos || (int)data[group].size() <= pos) {
            return false;
        }
        pos++;
        if ((int)data[group].size() == pos) {
            pos = 0, group++;
        }
        return true;
    }
    
    bool Prev(int &group, int &pos) const {
        if ((group == 0 && pos == 0)) {
            return false;
        }
        --pos;
        if (pos < 0) {
            group--;
            pos = (int)data[group].size()-1;
        }
        if (0 > group || (int)data.size() <= group || 
            0 > pos || (int)data[group].size() <= pos) {
            return false;
        }
        return true;
    }
    
    bool Exists(const T& key) const {
        int group, pos;
        bool flag = LowerBound(key, group, pos);
        if (!flag || less(key, data[group][pos])) {
            return false;
        }
        return true;
    }
    
    bool Insert(const T& key) {
        int group, pos;
        bool flag = LowerBound(key, group, pos);
        if (flag && !less(key, data[group][pos])) {
            return false;
        }
        data[group].insert(data[group].begin()+pos, key);
        Split(group);
        return true;
    }
    
    bool Delete(const T& key) {
        int group, pos;
        bool flag = LowerBound(key, group, pos);
        if (!flag || less(key, data[group][pos])) {
            return false;
        }
        data[group].erase(data[group].begin()+pos);
        Union(group);
        return true;
    }
    
    bool Split(int group) {
        if ((int)data[group].size() < 2 * gsize) {
            return false;
        }
        data.insert(data.begin()+group+1, std::vector<T>(data[group].begin()+gsize, data[group].end()));
        data[group].resize(gsize);
        return true;
    }
    
    bool Union(int group) {
        bool flag = false;
        if (group > 0 && (int)(data[group].size()+data[group-1].size()) >= gsize) {
            data[group-1].insert(data[group-1].end(), data[group].begin(), data[group].end());
            data.erase(data.begin()+group);
            flag = true;
        }
        if (group+1 < (int)data.size() && (int)(data[group].size()+data[group+1].size()) >= gsize) {
            data[group].insert(data[group].end(), data[group+1].begin(), data[group+1].end());
            data.erase(data.begin()+group+1);
            flag = true;
        }
        return flag;
    }
    
    bool ItemByOrder(int order, int &group, int &pos) const {
        group = (int)data.size()-1, pos = (int)data.back().size();
        for (int g = 0; g < (int)data.size(); ++g) {
            if ((int)data[g].size() < order) {
                order -= (int)data[g].size();
            } else {
                group = g;
                pos = order-1;
                return true;
            }
        }
        return false;
    }
    
    T& Get(int group, int pos) {
        return data[group][pos];
    }
    
    const T& Get(int group, int pos) const {
        return data[group][pos];
    }
};

bool Less(const int &lhs, const int &rhs) {
    return lhs < rhs;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    //SqrtList<int> set(Less, 256);
    std::set<int> set;
    std::string command; int value;
    while (std::cin >> command >> value) {
        if (command == "insert") {
            //set.Insert(value);
            set.insert(value);
        } else if (command == "delete") {
            //set.Delete(value);
            set.erase(value);
        } else {
            assert(command == "exists");
            //std::cout << (set.Exists(value) ? "true\n" : "false\n");
            std::cout << (set.count(value) ? "true\n" : "false\n");
        }
    }
    return 0;
}