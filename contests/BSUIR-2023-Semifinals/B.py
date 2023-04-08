from fractions import Fraction
v = [0, Fraction(360,60), Fraction(360,60*60), Fraction(360,12*60*60)];
p,q = map(int, input().split());
x,y = map(int, input().split());
ans = []
v1,v2 = v[x],v[y]
for i in range(0,12*60*60+1):
    # два корня на текущем периоде:
    p1 = 360 * i / (v1-v2) - p / (q*(v1-v2));
    p2 = 360 * i / (v1-v2) + p / (q*(v1-v2));
    was=0
    if 0 <= p1 and p1 <= 12*60*60:
        ans.append(p1);
        was=1;
    if 0 <= p2 and p2 <= 12*60*60:
        ans.append(p2);
        was=1
    if not was: # не было найдено ни одного корня
        break;
print(len(ans))
for i in range(0,len(ans)):
    x = ans[i].numerator;
    y = ans[i].denominator;
    print(x,y)