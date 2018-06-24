#include <stdio.h>
#include <vector>

int main() {
    char c; int n;
    scanf(" %c %d", &c, &n);
    
    std::vector<int> left, right;
    int pow3 = 1;
    do {
        int rem = n % 3;
        n /= 3;
        if (rem == 1) {
            right.push_back(pow3);
        } else if (rem == 2) {
            left.push_back(pow3);
            ++n;
        }
        pow3 *= 3;
    } while (n > 0);
    
    if (c == 'R') {
        left.swap(right);
    }
    printf("L:");
    for(auto& it : left) {
        printf("%d ", it);
    }
    printf("\n");
    printf("R:");
    for(auto& it : right) {
        printf("%d ", it);
    }
    printf("\n");
    return 0;
}