_, x = [int(a) for a in input().split()]
nums = [int(a) for a in input().split()]

md = 998244353

def sm(n):
	if n%3 == 0:
		return 0
	elif n%3 == 2 or n == 1:
		return 1
	else:
		return 2

def remd(n):
	if (sm(n) == 2):
		return n - 3
	else:
		return n

free_sht = sum(sm(n) for n in nums)

main_sht = 3*sum((remd(n) // 3) // 2 for n in nums)

rem_sht = 2*sum((remd(n) // 3) % 2 for n in nums)

F = sum(n // 3 for n in nums) + sum(1 if n % 3 > 0 else 0 for n in nums)
accm = F

for i in range(x):
	if free_sht > 0:
		free_sht -= 1
		F -= 1
	elif main_sht > 0:
		if main_sht % 3 > 0:
			F -=1
		main_sht -= 1
	elif rem_sht > 0:
		if rem_sht % 2 > 0:
			F -=1
		rem_sht -= 1
	accm = (accm + F) % md

print(accm)