n = int(input())
def f(n, a, b):
    if (n > 0):
        if ((a + b * 1) % 2 == 0):
            return f(n-1, (a + b * 1) // 2, b * 5) + "1"
        else:
            return f(n-1, (a + b * 2) // 2, b * 5) + "2"
    else:
        return "1"
print(f(n,0,1))