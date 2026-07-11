from random import randrange


# 64-битная арифметика по модулю 2^64, как в C++ unsigned long long.
MASK64 = (1 << 64) - 1

# Один случайный сдвиг на весь запуск программы.
RANDOM = randrange(1 << 64)


# Тот же splitmix64, что часто используют в C++ custom_hash.
def splitmix64(x):
    x = (x + 0x9e3779b97f4a7c15) & MASK64
    x = ((x ^ (x >> 30)) * 0xbf58476d1ce4e5b9) & MASK64
    x = ((x ^ (x >> 27)) * 0x94d049bb133111eb) & MASK64
    return (x ^ (x >> 31)) & MASK64


# Обёртка над int со своей хеш-функцией.
class SafeInt:
    __slots__ = ("x",)

    def __init__(self, x):
        self.x = x

    def __hash__(self):
        # Перемешиваем ключ и случайный сдвиг.
        return splitmix64(self.x + RANDOM)

    def __eq__(self, other):
        # Равенство определяется исходным значением ключа.
        return isinstance(other, SafeInt) and self.x == other.x


data = [10, 20, 10, 35, 20, 10]

# used хранит уникальные ключи, cnt -- их частоты.
used = set()
cnt = {}
for x in data:
    # Вместо int кладём в hash-структуры объекты SafeInt.
    key = SafeInt(x)
    used.add(key)
    cnt[key] = cnt.get(key, 0) + 1

# Для запросов тоже оборачиваем число в SafeInt.
print(f"10 in used = {'yes' if SafeInt(10) in used else 'no'}")
print(f"15 in used = {'yes' if SafeInt(15) in used else 'no'}")
print(f"count[10] = {cnt.get(SafeInt(10), 0)}")
print(f"count[20] = {cnt.get(SafeInt(20), 0)}")

# Печатаем исходные значения, а не объекты SafeInt.
print("keys = {", end="")
first = True
for key in used:
    if not first:
        print(",", end="")
    print(key.x, end="")
    first = False
print("}")