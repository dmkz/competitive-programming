#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << #x << " = " << (x) << endl

int main()
{
    setlocale(LC_ALL, "Ru-ru");
    bitset<15> a;
    cin >> a;
    
    watch(a);
    
    cout << "меняет на противоположный:" << endl;
    watch(a.flip(3));
    
    cout << "ставит в 1" << endl;
    watch(a.set(5));
    
    cout << "ставит в 0" << endl;
    
    watch(a.reset(6));
    
}