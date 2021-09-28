# Сдавать под pypy3
def main():
  tests = int(input())

  for test in range(tests):
    n = int(input())
    arr = [int(num) for num in input().split()]
    ans = 10 ** 18
    for split in range(1, n):
      one = arr[split - 1]
      other = arr[split]
      p1 = split - 2
      p2 = split + 1
      ans = min(ans, abs(one - other))
      while True:
        if one < other:
          if p1 >= 0:
            one += arr[p1]
            p1 -= 1
          else:
            break
        else:
          if p2 < n:
            other += arr[p2]
            p2 += 1
          else:
            break
        ans = min(ans, abs(one - other))
    print(ans)


main()

