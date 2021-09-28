def main():
  tests = int(input())
  for test in range(tests):
    n, k, d = map(int, input().split())
    arr = [int(num) for num in input().split()]

    costs = [[] for _ in range(d)]
    ans = 0
    for i, val in enumerate(arr):
      costs[i % d].append(val)

    for i in range(d):
      elems = len(costs[i])
      ps = [0] * (elems + 1)
      for j in range(elems):
        ps[j + 1] = ps[j] + costs[i][j]

      def get_sum(left, right):
        return ps[right] - ps[left]

      for j in range(k, elems + 1):
        ans = max(ans, get_sum(j - k, j))

    print(ans)


main()

