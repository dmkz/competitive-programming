from sys import stdout


def ask(point):
  print(f"? {point[0]} {point[1]}")
  stdout.flush()
  x, y = map(float, input().split())
  return x, y


def guess(point):
  print(f"! {point[0]} {point[1]}")
  stdout.flush()


def main():
  EPS = 1e-9

  def get_line(vec, point):
    return vec[1], -vec[0], point[1] * vec[0] - point[0] * vec[1]

  def get_len(vec):
    return (vec[0] * vec[0] + vec[1] * vec[1]) ** 0.5

  def det(a, b, c, d):
    return a * d - b * c

  def intersect(m, n):
    a1, b1, c1 = m
    a2, b2, c2 = n
    zn = det(a1, b1, a2, b2)
    return round(-det(c1, b1, c2, b2) / zn), round(-det(a1, c1, a2, c2) / zn)

  one = (339697208, 412598734)
  vec1 = ask(one)
  if get_len(vec1) < EPS:
    guess(one)
    return

  line1 = get_line(vec1, one)
  two = (-579719491, 144305795)
  vec2 = ask(two)
  if get_len(vec2) < EPS:
    guess(two)
    return
  line2 = get_line(vec2, two)

  ans = intersect(line1, line2)
  guess(ans)


main()

