from bisect import bisect_left, bisect_right
# решение задачи:
def solve():
    b, d, n = input().split()
    b = int(b)
    # если n состоит целиком из > максимальных цифр, то ответ имеет длину |n|+1
    if n > d[-1] * len(n):
        answ = [d[0]] * (len(n) + 1)
        if d[0] == "0":
            if len(d) > 1:
                answ[0] = d[1]
            else:
                answ = ["-1"]
        print("".join(answ))
        return
    # иначе ответ имеет такую же длину, строим его слева-направо
    answ = [d[0]] * len(n)
    for i in range(len(n)):
        it = bisect_left(d, n[i])
        if it == len(d):
            # не нашлось цифры, пытаемся увеличить предыдущие разряды
            while i > 0 and answ[i-1] == d[-1]:
                i -= 1
            assert i > 0
            jt = bisect_right(d, answ[i-1])
            assert jt != len(d)
            answ[i-1] = d[jt]
            answ[i:] = [d[0]] * (len(n)-i)
            break
        # иначе ставим найденную цифру:
        answ[i] = d[it]
        if d[it] > n[i]:
            break
    print("".join(answ))
tt = int(input())
while tt > 0:
    tt -= 1
    solve()