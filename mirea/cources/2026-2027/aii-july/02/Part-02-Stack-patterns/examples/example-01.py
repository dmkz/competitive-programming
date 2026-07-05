# Сокращение соседних одинаковых букв через стек.

s = "ABBACA"
stack = []

# В стеке храним уже сокращённую часть строки.
for ch in s:
    if stack and stack[-1] == ch:
        stack.pop()
    else:
        stack.append(ch)

print("result:", "".join(stack))