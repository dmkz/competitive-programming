# обработка строк, O(n)
import sys

input = sys.stdin.readline

n = int(input())
for _ in range(n):
    s = list(input().rstrip('\n'))
    open_ = True
    for i in range(len(s)):
        if s[i] == '|':
            s[i] = '[' if open_ else ']'
            open_ = not open_
    print(''.join(s))