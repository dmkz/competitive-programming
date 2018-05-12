# -*- coding: utf-8 -*-
import os, sys

# Reading all input as array:
arr = [[int (x) for x in s.split()] for s in sys.stdin.read().split('\n')]

# Copy size of array:
n = arr[0][0]
arr = arr[1:]

# Copy:
def copy(a):
    return a.copy()
        
# Struct Record:
class Record:
    
    def __init__(self, dist = 10000, count = 2, row = -1, col = -1):
        self.dist, self.count, self.row, self.col = dist, count, row, col
    
    def copy(self):
        return Record(**self.__dict__)
    
    def inc(self):
        self.dist = self.dist + 1
        return self

# Combine two records:
def combine(a, b):
    if (a.dist < b.dist):
        return copy(a)
    elif (a.dist > b.dist):
        return copy(b)
    elif a.row == b.row and a.col == b.col:
        return copy(a)
    else:
        return Record(a.dist, a.count + b.count, -1, -1)    
    
# 2-D arrays:
best_l_u = [[Record() for _ in range(n)] for _ in range(n)]
best_l_d = [[Record() for _ in range(n)] for _ in range(n)]
best_r_u = [[Record() for _ in range(n)] for _ in range(n)]
best_r_d = [[Record() for _ in range(n)] for _ in range(n)]

for i in range(n):
    for j in range(n):
        if (arr[i][j] != 0):
            best_l_u[i][j] = Record(0, 1, i, j)
            best_l_d[i][j] = Record(0, 1, i, j)
            best_r_u[i][j] = Record(0, 1, i, j)
            best_r_d[i][j] = Record(0, 1, i, j)

# Walk from left-up corner:
for i in range(1, n):
    best_l_u[i][0] = Record(0, 1, i, 0) if (arr[i][0] != 0) else copy(best_l_u[i-1][0]).inc()

for j in range(1, n):
    best_l_u[0][j] = Record(0, 1, 0, j) if (arr[0][j] != 0) else copy(best_l_u[0][j-1]).inc()
    
for i in range(1, n):
    for j in range(1, n):
        temp = combine(best_l_u[i-1][j], best_l_u[i][j-1]).inc()
        if (temp.dist < best_l_u[i][j].dist):
            best_l_u[i][j] = temp

# Walk from left-down corner:
for i in range(n-2, -1, -1):
    best_l_d[i][0] = Record(0, 1, i, 0) if (arr[i][0] != 0) else copy(best_l_d[i+1][0]).inc()

for j in range(1, n):
    best_l_d[n-1][j] = Record(0, 1, n-1, j) if (arr[n-1][j] != 0) else copy(best_l_d[n-1][j-1]).inc()

for i in range(n-2, -1, -1):
    for j in range(1, n):
        temp = combine(best_l_d[i+1][j], best_l_d[i][j-1]).inc()
        if (temp.dist < best_l_d[i][j].dist):
            best_l_d[i][j] = temp

# Walk from right-down corner:
for i in range(n-2, -1, -1):
    best_r_d[i][n-1] = Record(0, 1, i, n-1) if (arr[i][n-1] != 0) else copy(best_r_d[i+1][n-1]).inc()

for j in range(n-2, -1, -1):
    best_r_d[n-1][j] = Record(0, 1, n-1, j) if (arr[n-1][j] != 0) else copy(best_r_d[n-1][j+1]).inc()
    
for i in range(n-2, -1, -1):
    for j in range(n-2, -1, -1):
        temp = combine(best_r_d[i+1][j], best_r_d[i][j+1]).inc()
        if (temp.dist < best_r_d[i][j].dist):
            best_r_d[i][j] = temp

# Walk from right-up corner:
for i in range(1, n):
    best_r_u[i][n-1] = Record(0, 1, i, n-1) if (arr[i][n-1] != 0) else copy(best_r_u[i-1][n-1]).inc()
    
for j in range(n-2, -1, -1):
    best_r_u[0][j] = Record(0, 1, 0, j) if (arr[0][j] != 0) else copy(best_r_u[0][j+1]).inc()
    
for i in range(1, n):
    for j in range(n-2, -1, -1):
        temp = combine(best_r_u[i-1][j], best_r_u[i][j+1]).inc();
        if (temp.dist < best_r_u[i][j].dist):
            best_r_u[i][j] = temp

# Combine answers for each corners:
for i in range(0, n):
    for j in range(0, n):
        if (arr[i][j] == 0):
            best = combine(combine(best_l_u[i][j], best_r_u[i][j]), combine(best_l_d[i][j], best_r_d[i][j]))
            if (best.count == 1):
                arr[i][j] = arr[best.row][best.col]

# Creating string for fast output:
s_out = ""
for row in arr:
    for x in row:
        s_out += str(x) + " ";
    s_out += "\n"

# Fast output:
os.write(1, s_out.encode())