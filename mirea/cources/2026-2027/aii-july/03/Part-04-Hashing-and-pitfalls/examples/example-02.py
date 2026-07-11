from collections import defaultdict


def print_dict(name, mp):
    parts = [f"{key}: {value}" for key, value in mp.items()]
    print(f"{name} = {{{', '.join(parts)}}}")


words = ["pear", "apple", "kiwi", "pear", "plum", "apple"]

# Считаем частоты слов.
cnt = defaultdict(int)
for word in words:
    cnt[word] += 1

# Количество различных ключей.
print(len(cnt))

print_dict("cnt", cnt)

# Поиск по ключу.
for word in ["pear", "mango"]:
    if word in cnt:
        print(f"Find {word}: ok, value = {cnt[word]}")
    else:
        print(f"Find {word}: fail")

# Удаление ключей.
for word in ["pear", "mango", "apple"]:
    print(f"Delete {word}: ", end="")
    if word in cnt:
        print("ok", end="")
        del cnt[word]
    else:
        print("fail", end="")
    print_dict(", cnt", cnt)
