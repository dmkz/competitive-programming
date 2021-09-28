def main():
  tests = int(input())
  for test in range(tests):
    n, l, r = map(int, input().split())
    min_n = (l + n - 1) // n
    max_n = (r + n - 1) // n
    print(max_n - min_n)


main()

