numbers = [2, 1, 4, 3, 5, 2]
stack = []
previous_greater = [-1] * len(numbers)

# В стеке храним индексы кандидатов на ближайший больший слева.
for i, value in enumerate(numbers):
    while stack and numbers[stack[-1]] <= value:
        stack.pop()

    if stack:
        previous_greater[i] = numbers[stack[-1]]

    stack.append(i)

print("previous greater values:", *previous_greater)