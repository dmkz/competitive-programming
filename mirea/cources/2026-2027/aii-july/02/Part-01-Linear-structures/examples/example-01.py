# В Python3 стек почти всегда пишут на обычном списке.

st = []

st.append(10)
st.append(20)
st.append(30)

print("top =", st[-1])
print("size =", len(st))
print("second element =", st[1])

st.pop()
print("top after pop =", st[-1])
print("empty =", "yes" if not st else "no")