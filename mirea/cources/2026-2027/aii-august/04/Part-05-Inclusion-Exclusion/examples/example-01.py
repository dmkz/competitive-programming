s = int(input())
limit = 1 << s
# intersection[mask] хранит размер пересечения множеств, выбранных маской.
intersection = [0] + list(map(int, input().split()))
# Нечётное число свойств даёт плюс, чётное число свойств даёт минус.
answ = 0
for mask in range(1, limit):
	if mask.bit_count() % 2 == 1: answ += intersection[mask]
	else: answ -= intersection[mask]
print(answ)