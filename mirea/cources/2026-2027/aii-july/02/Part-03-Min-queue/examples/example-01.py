from collections import deque


q = int(input())
mins = deque()
left_pos = 0
right_pos = 0

for _ in range(q):
    parts = input().split()
    op = parts[0]

    if op == '+':
        x = int(parts[1])

        while mins and mins[-1][0] >= x:
            mins.pop()
        mins.append((x, right_pos))
        right_pos += 1
    elif op == '-':
        if mins and mins[0][1] == left_pos:
            mins.popleft()
        left_pos += 1
    else:
        print(mins[0][0])