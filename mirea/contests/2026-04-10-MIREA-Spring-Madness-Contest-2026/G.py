# префиксные суммы, бинарный поиск, O(n + q * log(n))
import sys
import bisect

it = iter(sys.stdin.buffer.read().split())

n = int(next(it))
q = int(next(it))
h = int(next(it))
w = int(next(it))

a = [0] * n
sh = [0] * (n + 1)
sw = [0] * (n + 1)
s = [0] * (n + 1)

for i in range(n):
    a[i] = int(next(it))
    sw[i + 1] = sw[i]
    sh[i + 1] = sh[i]
    if i % 2 == 0:
        sh[i + 1] += a[i]
    else:
        sw[i + 1] += a[i]
    s[i + 1] = s[i] + a[i]

def f(t):
    if t > s[-1]:
        t = s[-1]
    i = bisect.bisect_right(s, t) - 1
    coeffH = sh[i]
    coeffW = sw[i]
    if i % 2 == 0:
        coeffH += t - s[i]
    else:
        coeffW += t - s[i]
    return h * w + coeffH * h + coeffW * w

out = []
for _ in range(q):
    l = int(next(it))
    r = int(next(it))
    out.append(str(f(r) - f(l)))

sys.stdout.write('\n'.join(out))