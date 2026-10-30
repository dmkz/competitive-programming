# Вердикт: TIME_LIMIT_EXCEEDED [1000ms, 57MB]. Лучше сдавать на C++.
from collections import defaultdict
def solve():
    a, b, c, k = map(int,input().split())
    n = a + b + c
    # нужно определить, можно ли, чередуя группы из одинаковых букв с длинами len[i], получить:
    # sum(len[i]-1) = k => n - nGroups = k => nGroups = n - k. То есть, мы знаем количество групп.
    nGroups = n - k
    # попробуем сначала получить максимальное количество групп, затем объединить некоторые группы в одну
    # первую группу нам нужно построить аналитически: берём букву с максимальным количеством
    rem = [[a,'A'],[b,'B'],[c,'C']]
    rem.sort(reverse=True)
    mx = rem[0][0]
    sum = rem[1][0] + rem[2][0]
    # чтобы суметь разделить, нам нужно сделать mx <= sum
    answ = []
    if (delta := mx-sum) > 0:
        answ.append([delta,rem[0][1]])
        rem[0][0] -= delta
    # теперь первая группа построена. для каждой следующей группы отделяем один символ
    # с максимальным количеством и ставим группу с одним элементом:
    while True:
        rem.sort(reverse=True)
        was = False
        for it in rem:
            cnt, letter = it
            if cnt > 0 and (not answ or answ[-1][1] != letter):
                answ.append([1,letter])
                it[0] -= 1
                was = True
                break
        if not was: break
    if len(answ) < nGroups:
        print("NO")
        return
    # теперь нужно уменьшать количество групп, объединяя похожие. сохраняем номера групп для каждой буквы
    answ.reverse()
    ids = defaultdict(list)
    for i, (cnt, letter) in enumerate(answ):
        ids[letter].append(i)
    # объединяем группы, отделяя последнюю и сливая её с любой другой группой той же буквы
    while len(answ) > nGroups:
        # берём последнюю группу и сливаем её
        if len(ids[answ[-1][1]]) == 1:
            # но если не можем слить, смотрим с другого конца
            answ.reverse()
            ids.clear()
            for i, (cnt, letter) in enumerate(answ):
                ids[letter].append(i)
        lastCnt, lastLetter = answ[-1]
        answ.pop()
        ids[lastLetter].pop()
        if ids[lastLetter]:
            i = ids[lastLetter][0]
            answ[i][0] += lastCnt
        else:
            print("NO")
            return
    print("YES")
    print("".join(cnt*letter for cnt, letter in answ))
tt = int(input())
while tt > 0:
    tt -= 1
    solve()