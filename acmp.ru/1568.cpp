#include <stdio.h>
#include <vector>

int main() {
    int nRes, nUnits;
    scanf("%d %d", &nRes, &nUnits);
    std::vector<int> res(nRes);
    for (auto& it : res) {
        scanf("%d", &it);
    }
    while (nUnits--) {
        bool flag = true;
        for (int i = 0; i < nRes; ++i) {
            int value; scanf("%d", &value);
            if (res[i] < value) {
                flag = false;
            }
        }
        printf("%c ", flag ? '1' : '0');
    }
    return 0;
}