s = input().strip()
stack = []
ok = True

for ch in s:
    if ch == '(':
        stack.append(ch)
    else:
        if not stack:
            ok = False
            break
        stack.pop()

if stack:
    ok = False

print("correct" if ok else "incorrect")