MAX_A = 10 ** 4
SHIFTS = (2, 3, 5)
MOVES = len(SHIFTS)

dp = [[[] for __ in range(MAX_A)] for _ in range(MOVES)]


def precalc():
  for row in range(1, MAX_A + 1):
    cols = MAX_A // row
    for sub in dp:
      sub[row - 1].extend([False] * cols)

  for i in range(MAX_A):
    for j in range(len(dp[0][i])):
      for k in range(MOVES):
        prev_i = i - SHIFTS[k]
        if prev_i >= 0 and dp[(k + 1) % MOVES][prev_i][j] is False:
          dp[k][i][j] = True
        prev_j = j - SHIFTS[k]
        if prev_j >= 0 and dp[(k + 1) % MOVES][i][prev_j] is False:
          dp[k][i][j] = True


def main():
  precalc()

  tests = int(input())
  for test in range(tests):
    n, m = map(int, input().split())
    print("Alice" if dp[0][n - 1][m - 1] else "Bob")


main()

