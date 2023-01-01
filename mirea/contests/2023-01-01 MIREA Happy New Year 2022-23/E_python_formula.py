g = 9.81

from math import sqrt

def solve(x, y, t1):
    tga1 = (y+g*t1*t1/2)/x
    Vs = g*x*x*(1+tga1*tga1)/2/(x*tga1-y)
    A = g*x*x/2/Vs
    B = -x
    C = A+y
    tga2 = (-B-sqrt(B*B-4*A*C))/2/A
    t2 = sqrt(2*(x*tga2 - y)/g)
    return t2
    
    
t = int(input().strip())

for _ in range(t):
    print(solve(*[int(x) for x in input().strip().split()]))