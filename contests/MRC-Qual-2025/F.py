# Задача: F, Вердикт: OK, Время: 453ms, Память: 153.75Mb
import sys

def main():
    # быстрый ввод миллиона чисел: читаем все данные из sys.stdin.buffer
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    nRows = int(next(it))
    nCols = int(next(it))
    a = [[0] * nCols for _ in range(nRows)]
    for r in range(nRows):
        for c in range(nCols):
            a[r][c] = int(next(it))
    # проверяем существование положительного ответа
    # достаточно проверять квадраты 2х2, потому что, если существует
    # ответ в виде прямоугольника, то существует и ответ в виде квадрата 2x2
    # это возможно, потому что нас не просят находить лучший ответ, а просто
    # найти любой, где сумма красных минус сумма синих больше нуля
    answer = [-1]
    found = False
    for r in range(nRows - 1):
        if found:
            break
        row0 = a[r]
        row1 = a[r + 1]
        for c in range(nCols - 1):
            diff = row0[c] + row1[c + 1] - row0[c + 1] - row1[c]
            if diff > 0:
                # координаты квадрата 2х2 в 1-индексации:
                answer = [r + 1, r + 2, c + 1, c + 2]
                found = True
                break
    print(" ".join(map(str, answer)))

if __name__ == "__main__":
    main()
