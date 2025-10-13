# Задача: D, Вердикт: OK, Время: 124ms, Память: 32.23Mb
import sys
import math

def main():
    # читаем данные: сразу в вещественных числах
    downloadTime, speed, downloaded = map(float, sys.stdin.read().strip().split())
    # проще всего посчитать длину дуги: 360 умножить на процент скачивания
    circleLength = 360.0 * downloaded / 100.0
    # считаем стартовую позицию: время скачивания умножить на процент скачивания
    # умножить на скорость вращения — получим количество пройденных градусов
    # так как могло быть сделано несколько полных оборотов, то нужно вычесть
    # все полные обороты. Таким образом найдём текущее положение на окружности
    path = speed * downloadTime * downloaded / 100.0
    fullCircles = math.floor(path / 360.0)
    start = path - fullCircles * 360.0
    finish = start + circleLength
    if finish >= 360.0:
        finish -= 360.0
    # выводим в фиксированной форме с 4-мя знаками после запятой с помощью f-строк
    print(f"{start:.4f} {finish:.4f}")

if __name__ == "__main__":
    main()
