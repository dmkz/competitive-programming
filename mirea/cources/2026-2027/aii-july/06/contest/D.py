# Прочитаем шаблон скобочной строки и запустим рекурсивный перебор вариантов.
# Если позиция равна "?", то мы можем поставить как открывающую скобку, так и закрывающую.
# Если позиция равна "(" или ")", то ставим именно эту скобку.
# Поддерживаем баланс открытых скобок. Запрещено ставить закрывающую скобку, если баланс
# становится отрицательным. В конце перебора выводим те строки, баланс которых равен 0.
def solve():
    # читаем данные
    n = int(input())
    pattern = input()
    # запускаем рекурсию
    s = []
    was = False

    def dfs(i, balance):
        nonlocal was
        if i == n:
            if balance == 0:
                print("".join(s))
                was = True
            return
        # ставим открывающую:
        if pattern[i] != ')':
            s.append('(')
            dfs(i + 1, balance + 1)
            s.pop()
        # ставим закрывающую:
        if pattern[i] != '(' and balance > 0:
            s.append(')')
            dfs(i + 1, balance - 1)
            s.pop()

    dfs(0, 0)
    if not was:
        print("NO SOLUTION")
    print()


tt = int(input())
while tt > 0:
    solve()
    tt -= 1