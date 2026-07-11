def print_set(name, s):
    print(f"{name} = {{{','.join(s)}}}")


words = ["pear", "apple", "kiwi", "pear", "plum", "apple"]

# В set храним только уникальные слова.
s = set()
for word in words:
    s.add(word)

# Количество различных слов.
print(len(s))

print_set("s", s)

# Проверка принадлежности.
for word in ["pear", "mango"]:
    print(f"Have {word}: {'yes' if word in s else 'no'}")

# Удаление элементов.
for word in ["kiwi", "mango", "apple"]:
    print(f"Delete {word}: ", end="")
    if word in s:
        print("ok", end="")
        s.remove(word)
    else:
        print("fail", end="")
    print_set(", s", s)
