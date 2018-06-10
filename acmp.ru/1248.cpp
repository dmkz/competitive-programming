#include <stdio.h>

int main() {
    int h, m;
    scanf("%d:%d", &h, &m);
    m += 60 * h;
    if (m < 8 * 60 + 30) {
        printf("MORNING");
    } else if (m < 9 * 60 + 55) {
        printf("1");
    } else if (m < 10 * 60 + 10) {
        printf("BREAK");
    } else if (m < 11*60+35) {
        printf("2");
    } else if (m < 11*60+50) {
        printf("BREAK");
    } else if (m < 13 * 60 + 15) {
        printf("3");
    } else if (m < 13*60+45) {
        printf("BREAK");
    } else if (m < 15*60+10) {
        printf("4");
    } else if (m < 15*60 + 25) {
        printf("BREAK");
    } else if (m < 16*60+50) {
        printf("5");
    } else if (m < 17*60+5) {
        printf("BREAK");
    } else if (m < 18*60 + 30) {
        printf("6");
    } else {
        printf("EVENING");
    }
    return 0;
}