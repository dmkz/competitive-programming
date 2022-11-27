import sys
checks = ['a1', 'h7', 'c4']

def itr(x):
	print(x)
	sys.stdout.flush()
	return int(input()) == 0
	
def step():
	if itr(checks[0]) and itr(checks[1]):
		itr(checks[2])

T = int(input())
for _ in range(T):
	step()