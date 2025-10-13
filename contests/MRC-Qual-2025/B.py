# Задача: B, Вердикт: OK, Время: 113ms, Память: 32.36Mb
import sys

def main():
    # читаем вход целыми числами
    data = list(map(int, sys.stdin.read().strip().split()))
    birthYear, joinYear, numSems, numFinals, numRegionals = data
    # определяем ответ
    answer = "+"  # изначально считаем, что участие разрешено, далее проверки
    if numFinals >= 2:
        answer = "-"  # участие запрещено
    elif numRegionals >= 6:
        answer = "-"  # участие запрещено
    elif numRegionals == 5 or (birthYear < 2002 and joinYear < 2021):
        # применяется правило 5
        if numSems >= 9:  # участие запрещено
            answer = "-"
        else:  # участие под вопросом
            answer = "?"
    print(answer)

if __name__ == "__main__":
    main()
