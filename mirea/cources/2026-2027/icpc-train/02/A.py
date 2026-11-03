from collections import defaultdict
# функция для перевода из строки формата "HH:MM:SS" в секунды:
def time2sec(s):
    hh, mm, ss = map(int, s.split(":"))
    return ss + 60 * (mm + hh * 60)
# функция для перевода из секунд в строку формата "HH:MM:SS":
def sec2time(ss):
    hh = ss // 3600
    mm = ss // 60 % 60
    ss %= 60
    return f"{hh:02d}:{mm:02d}:{ss:02d}"
# решение задачи:
def solve():
    q = int(input())
    # храним для каждого чувака его последнее известное состояние (вышел/вошёл, время в секундах):
    cache = {}
    # а здесь храним ответ в секундах для каждого:
    answ = defaultdict(int)
    while q > 0:
        q -= 1
        sTime, sName, sType = input().split()
        sec = time2sec(sTime)
        # смотрим, что делал человек до этого, и обновляем ответ и его состояние
        if sType == "OUT":
            if sName not in cache:
                # не было, но ушёл
                answ[sName] += sec
            else:
                answ[sName] += sec - cache[sName][1]
            cache[sName] = ("OUT", sec)
        elif sType == "IN":
            if sName in cache and cache[sName][0] == "IN":
                # ничего не делаем, он повторно приложил пропуск
                pass
            else:
                cache[sName] = ("IN", sec)
    # все те, кто до сих пор внутри, должны выйти: обновляем для них ответ:
    for name, val in cache.items():
        if val[0] == "IN":
            answ[name] += 24*60*60 - val[1]
    # выводим ответ:
    for name, sec in sorted(answ.items()):
        print(name, sec2time(sec))
solve()