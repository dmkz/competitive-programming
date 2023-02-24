#include <bits/stdc++.h>

using namespace std;

#define watch(x) cout << #x << " = " << (x) << endl

int main()
{
    setlocale(LC_ALL, "Ru-ru");
    bitset<15> a;
    cin >> a;
    
    watch(a);
    
    cout << "меняет всё на противоположный:" << endl;
    a.flip();
    watch(a);
    
    cout << "ставит всё в 1" << endl;
    a.set();
    watch(a);
    
    cout << "ставит всё в 0" << endl;
    a.reset(); 
    watch(a);
    
}