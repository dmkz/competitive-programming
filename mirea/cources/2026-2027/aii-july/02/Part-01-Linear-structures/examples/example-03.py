from collections import deque


d = deque([20, 30])

# Deque позволяет работать с обоими концами.
d.appendleft(10)
d.append(40)

print("front =", d[0])
print("back =", d[-1])

# Индексация есть, но для середины ею не стоит злоупотреблять.
print("middle =", d[1])

d.popleft()
d.pop()
print("remaining:", *d)