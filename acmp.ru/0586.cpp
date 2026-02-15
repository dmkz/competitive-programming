// перестановки, теория игр
#include <bits/stdc++.h>
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector posOfItem(n, std::vector<int>(k+1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++) {
            int x; std::cin >> x;
            posOfItem[i][x] = j;
        }
    // начинаем голосовать с конца в начало, определяя крайний
    // законопроект, который будет принят
    int lastAccepted = k;
    for (int j = k-1; j >= 1; j--) {
        // если i-й кандидат не голосует за j, то будет принят
        // lastAccepted. Считаем, кому это не выгодно.
        int votes = 0;
        for (int i = 0; i < n; i++)
            if (posOfItem[i][j] < posOfItem[i][lastAccepted])
                // i-й депутат предпочёл бы законопроект j
                votes++;
        if (votes >= m)
            lastAccepted = j;
    }
    std::cout << lastAccepted << std::endl;
}
