#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    int t;
    cin >> t;
    for (int it=0; it<t; it++){
        double x, y, t1;
        cin >> x >> y >> t1;
        double sv=y/t1+9.81*t1/2;
        double cv=x/t1;
        double v=sqrt(sv*sv+cv*cv);
        double a=9.81*9.81;
        double b=y*9.81*4-4*v*v;
        double c=4*x*x+4*y*y;
        double d=b*b-4*a*c;
        double x1=(-b-sqrt(d))/(2*a);
        cout << sqrt(x1) << '\n';
    }
}
