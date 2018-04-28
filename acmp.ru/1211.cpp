#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdint>

typedef uint64_t Int;

int main() {
    Int treesPerDay1, dayOff1, treesPerDay2, dayOff2, nTrees;
    std::cin >> treesPerDay1 >> dayOff1 >> treesPerDay2 >> dayOff2 >> nTrees;
    
    // Сколько деревьев будет срублено одним работником?
    std::function<Int(Int, Int, Int)> nCutTrees = [](Int nDays, Int treesPerDay, Int dayOff) {
        return (nDays - nDays / dayOff) * treesPerDay;
    };
    
    // Сколько потребуется дней для одного работника?
    std::function<Int(Int, Int, Int)> nDaysForOne = [&nCutTrees](Int nTrees, Int treesPerDay, Int dayOff) {
        Int low = 0, high = 2 * (nTrees + treesPerDay - 1) / treesPerDay;
        while (high - low > 1) {
            Int mid = (high + low) >> 1;
            if (nCutTrees(mid, treesPerDay, dayOff) >= nTrees) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return high;
    };
    
    // Сколько потребуется дней для двух работников?
    Int low = 0, high = std::min(
        nDaysForOne(nTrees, treesPerDay1, dayOff1),
        nDaysForOne(nTrees, treesPerDay2, dayOff2)
    );
    
    while (high - low > 1) {
        Int mid = (low + high) >> 1;
        if (nCutTrees(mid, treesPerDay1, dayOff1) + nCutTrees(mid, treesPerDay2, dayOff2) >= nTrees) {
            high = mid;
        } else {
            low = mid;
        }
    }
    
    std::cout << high << std::endl;
    
    return 0;
}