from collections import deque

queue = deque()

queue.append(10)
queue.append(20)
queue.append(30)

print("front =", queue[0])
queue.popleft()
print("front after pop =", queue[0])
print("back =", queue[-1])