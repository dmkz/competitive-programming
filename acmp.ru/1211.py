# -*- coding: utf-8 -*-
treesPerDay1, dayOff1, treesPerDay2, dayOff2, nTrees = (int(x) for x in input().split())
    
# Сколько деревьев будет срублено одним работником?
def nCutTrees(nDays, treesPerDay, dayOff):
    return (nDays - nDays // dayOff) * treesPerDay;

# Сколько потребуется дней для одного работника?
def nDaysForOne(nTrees, treesPerDay, dayOff):
    low = 0; high = 2 * nTrees;
    while high - low > 1:
        mid = (high + low) // 2;
        if nCutTrees(mid, treesPerDay, dayOff) >= nTrees:
            high = mid;
        else:
            low = mid;
    return high;

# Сколько потребуется дней для двух работников?
low = 0; high = min(nDaysForOne(nTrees, treesPerDay1, dayOff1), nDaysForOne(nTrees, treesPerDay2, dayOff2));
while high - low > 1:
    mid = (low + high) // 2
    if nCutTrees(mid, treesPerDay1, dayOff1) + nCutTrees(mid, treesPerDay2, dayOff2) >= nTrees:
        high = mid;
    else:
        low = mid;

print(high)