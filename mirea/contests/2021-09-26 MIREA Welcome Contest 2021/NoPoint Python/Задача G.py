def main():
  tests = int(input())
  for test in range(tests):
    n = int(input())
    prob0, prob1, prob2, prob3 = map(float, input().split())
    ans = (prob1 + prob2 * 2 + prob3 * 3) * n
    print(f"{ans:.12f}")


main()

