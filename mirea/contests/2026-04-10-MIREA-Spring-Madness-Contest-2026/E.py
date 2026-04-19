# префиксные суммы, O(n+q)
import sys

it = iter(sys.stdin.buffer.read().split())

n = int(next(it))
q = int(next(it))

# храним префикс-суммы для элементов, добавленных в конец, и для
# элементов, добавленных в начало, отдельно. Тогда запрос заспадается
# на два запроса в двух префикс-суммах.
prefSums1 = [0]
prefSums2 = [0]

def push_back(x):
    prefSums1.append(prefSums1[-1] + x)

def push_front(x):
    prefSums2.append(prefSums2[-1] + x)

def answer_back(l, r):
    return 0 if l > r else prefSums1[r + 1] - prefSums1[l]

def answer_front(l, r):
    return 0 if l > r else prefSums2[r + 1] - prefSums2[l]

def answer(l, r):
    addedInFront = len(prefSums2) - 1
    l -= addedInFront
    r -= addedInFront
    if r < 0:
        return answer_front(-r - 1, -l - 1)
    elif l >= 0:
        return answer_back(l, r)
    else:
        return answer_front(0, -l - 1) + answer_back(0, r)

# читаем элементы и добавляем их в конец:
for _ in range(n):
    x = int(next(it))
    push_back(x)

# обрабатываем запросы:
out = []
for _ in range(q):
    c = next(it).decode()
    if c == '?':
        l = int(next(it))
        r = int(next(it))
        out.append(str(answer(l, r)))
    elif c == '>':
        x = int(next(it))
        push_front(x)
    else:
        assert c == '<'
        x = int(next(it))
        push_back(x)

sys.stdout.write('\n'.join(out))