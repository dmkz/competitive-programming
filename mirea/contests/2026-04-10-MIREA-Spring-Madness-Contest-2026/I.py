# префиксные суммы, бинарный поиск, геометрия, площадь сектора, O(n + q * log(n))
import sys
import math
import bisect

it = iter(sys.stdin.buffer.read().split())
pi = math.acos(-1.0)

n = int(next(it))
q = int(next(it))
R = int(next(it))

sa = [0] * (n + 1)
for i in range(1, n + 1):
    a = int(next(it))
    sa[i] = a + sa[i - 1]


def solve(t):
    if t <= 0:
        return pi * R * R
    if t > sa[n]:
        t = sa[n]

    coeff = 2.0 * t * R + pi * R * R
    i = bisect.bisect_left(sa, t) - 1

    if i >= 2:
        coeff -= (i - 1) * (1.0 - pi / 4) * R * R

    if i >= 1:
        delta = min(float(R), float(t - sa[i]))
        coeff -= delta * R
        h = R - delta
        alpha = math.acos(h / float(R))
        coeff += (alpha - 0.5 * math.sin(2 * alpha)) * R * R / 2.0

    return coeff

out = []
for _ in range(q):
    l = int(next(it))
    r = int(next(it))
    out.append(f"{solve(r) - solve(l):.15f}")

sys.stdout.write('\n'.join(out))