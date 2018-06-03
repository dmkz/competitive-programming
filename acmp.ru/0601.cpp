#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

int main() {
    std::map<int, int> next[10000]; // next[curr][color] -> next vertex
    int nVert, nEdges; 
    scanf("%d %d", &nVert, &nEdges);
    while (nEdges--) {
        int a, b, color;
        scanf("%d %d %d", &a, &b, &color);
        --a, --b;
        next[a][color] = b;
        next[b][color] = a;
    }
    
    int nSteps;
    scanf("%d", &nSteps);
    int cur = 0;
    while (nSteps--) {
        int color;
        scanf("%d", &color);
        if (next[cur].find(color) == next[cur].end()) {
            printf("INCORRECT");
            return 0;
        }
        cur = next[cur][color];
    }
    printf("%d", cur+1);
    return 0;
}