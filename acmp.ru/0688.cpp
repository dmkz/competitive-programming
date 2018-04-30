#include <stdio.h>

int main() {
  	int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    
    int n; 
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        int x, y; 
        scanf("%d %d", &x, &y);
        // assert(4*((x1-x)*(x1-x)+(y1-y)*(y1-y)) != (x2-x)*(x2-x)+(y2-y)*(y2-y)); RE 11
        if (4*(1LL*(x1-x)*(x1-x)+1LL*(y1-y)*(y1-y)) <= 1LL*(x2-x)*(x2-x)+1LL*(y2-y)*(y2-y)) {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("NO\n");
	return 0;
}