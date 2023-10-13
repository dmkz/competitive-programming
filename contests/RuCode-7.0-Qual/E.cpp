#include "template.hpp"
#include "numeric.hpp"
const int mod = (int)1e9+7;
using namespace algos::numeric;
using Int = IntMod<mod>;
int main() {
    Int a,b,c,d;
    std::cin >> a >> b >> c >> d;
    std::cout << a / b + c / d << std::endl;
}
