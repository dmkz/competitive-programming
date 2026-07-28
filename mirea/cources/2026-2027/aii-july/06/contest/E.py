# Будем рекурсивно расставлять ферзей, двигаясь по строкам сверху вниз. Ферзь бьёт
# строку, столбец и две диагонали. Поддерживаем множество столбцов и диагоналей, которые
# находятся под боем. При переходе от row к row+1:
# 1. номера столбцов, находящихся под боем, не меняются;
# 2. диагонали вида row+col на доске сдвигаются на 1 влево;
# 3. диагонали вида row-col на доске сдвигаются на 1 вправо.
# Оптимальная скорость перебора достигается с использованием битовых масок и битовых сдвигов
# на один влево и на один вправо.
def solve():
    # читаем исходные данные:
    n = int(input())
    board = [input() for _ in range(n)]
    # инициализируем вспомогательные данные:
    available = [0] * n
    for row in range(n):
        for col in range(n):
            if board[row][col] == '.':
                available[row] |= 1 << col
    answ = 0

    def dfs(row, used_col, used_diag1, used_diag2):
        nonlocal answ
        if row == n:
            answ += 1
            return
        can_put = available[row] & ~(used_col | used_diag1 | used_diag2)
        for col in range(n):
            if can_put & (1 << col):
                # копируем состояние поля:
                new_used_col = used_col
                new_used_diag1 = used_diag1
                new_used_diag2 = used_diag2
                # отмечаем текущую клетку:
                new_used_col |= 1 << col
                new_used_diag1 |= 1 << col
                new_used_diag2 |= 1 << col
                # при переходе от row к row+1: столбцы не меняются
                new_used_diag1 <<= 1  # диагонали (row-col): вправо на доске, влево в маске
                new_used_diag2 >>= 1  # диагонали (row+col): влево на доске, вправо в маске
                # рекурсивный вызов:
                dfs(row + 1, new_used_col, new_used_diag1, new_used_diag2)

    # запускаем рекурсивный перебор
    dfs(0, 0, 0, 0)
    # выводим ответ:
    print(answ)


tt = int(input())
while tt > 0:
    solve()
    tt -= 1