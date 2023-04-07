n, m = map(int, input().split())
a = [int(x) for x in input().split()]
b = [int(x) for x in input().split()]
prodA, prodB = int(1), int(1);
for i in range(n):
    prodA *= a[i];
    prodB *= b[i];
# для каждого i надо найти минимальное число x, которое подходит условию:
# prodA / a[i] * x >= prodB, или:
# x >= a[i] * prodB / prodA
ratio = prodB / prodA; # примерное отношение
answ = 0;
for i in range(n):
    # примерное решение уравнения:
    minReplacement = int(ratio * a[i]);
    if minReplacement > m:
       minReplacement = m+1;
    # подгоняем под ограничения:
    while ((minReplacement <= m) and (minReplacement * prodA < prodB * a[i])):
        minReplacement+=1;
    # подгоняем под ограничения:
    while ((minReplacement > 0) and ((minReplacement-1) * prodA >= prodB * a[i])):
        minReplacement-=1;
    # прибавляем количество чисел, на которые можем заменить:
    answ += m - minReplacement + 1;
    # вычитаем, если учли само число - по условию задачи нельзя менять на себя же
    answ -= (a[i] >= minReplacement);
print(answ);