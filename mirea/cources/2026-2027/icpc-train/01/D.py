# храним таблицу игры: побеждает ли человек, который ходит в этой ситуации, и каким конкретно ходом
lose = (0,0)
table = [[lose for b in range(201)] for a in range(201)]
def precalc():
    # исследуем всю таблицу игры до начала запросов:
    table[0][0] = lose
    for sum in range(1,401):
        for a in range(201):
            b = sum - a
            if 0 <= b <= 200:
                step = lose
                # исследуем состояние (a, b): нужно найти такой ход, который ставит соперника в проигрыш
                # ход 1. берём с первой тарелки
                for x in range(1,a+1):
                    if table[a-x][b] == lose:
                        step = (x,0)
                        break
                # ход 2. берём со второй тарелки
                for x in range(1,b+1):
                    if table[a][b-x] == lose:
                        step = (0,x)
                        break
                # ход 3. берём сразу с обеих тарелок
                x = 1
                while x*x <= min(a,b):
                    xx = x*x
                    if table[a-xx][b-xx] == lose:
                        step = (xx,xx)
                        break
                    x += 1
                table[a][b] = step
def solve():
    # начинаем играть
    a, b = map(int,input().split())
    if table[a][b] == lose:
        print("Second",flush=True)
    else:
        print("First",flush=True)
        x, y = table[a][b]
        print(x,y,flush=True)
        a -= x; b -= y
    while a+b > 0:
        # ход жюри:
        x, y = map(int,input().split())
        a -= x; b -= y
        # наш ход:
        x, y = table[a][b]
        print(x,y,flush=True)
        a -= x; b -= y
precalc()
tt = int(input())
while tt > 0:
    tt -= 1
    solve()