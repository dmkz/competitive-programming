numbers = [5, 2, 4, 1, 3]
stack = []
next_smaller = [-1] * len(numbers)

# Идём справа налево и ищем ближайший меньший элемент справа.
for i in range(len(numbers) - 1, -1, -1):
    while stack and numbers[stack[-1]] >= numbers[i]:
        stack.pop()

    if stack:
        next_smaller[i] = numbers[stack[-1]]

    stack.append(i)

print("next smaller values:", *next_smaller)