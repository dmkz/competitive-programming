#include "template.hpp"
#include "numeric.hpp"
#include "segmenttreelazy.hpp"
using namespace algos::SegmentTreeLazy;
using namespace algos::numeric;
const int mod = (int)1e9+7;
using Int = IntMod<mod>;
// не меньше => больше либо равно
// не больше => меньше либо равно
int main() {
    //const bool debug = 1;
    int n; std::cin >> n;
    // произведение всех ашек
    // b[i] * A(j < i)
    Int A = 1;
    vpii arr(n);
    std::vector<Int> coeff;
    int nZeros = 0;
    for (auto &[a, b] : arr) {
        std::cin >> a >> b;
        coeff << (A * b);
        if (a != 0)
            A *= a;
        else
            nZeros++;
    }
    SegmentTree<Int,Int,TraitsSumMul<Int,Int>> st;
    st.build(coeff);
    auto getAnswer = [&]() -> int {
        if (nZeros > 0) {
            return -1;
        } else {
            // A * x + B = 0
            // Int B = 0;
            // for (auto it : coeff)
            //     B += it;
            Int B = st.get(0, isz(coeff)-1);
            Int x = -B / A;
            return x.value;
        }
    };
    vi pos;
    for (int i = 0; i < n; i++)
        pos << i;
    for (int id = 0; id < n-1; id++) {
        std::cout << getAnswer() << "\n";
        int c; std::cin >> c;
        c--;
        int pc = pos[c];
        auto [a, b] = arr[pc];
        nZeros -= (a == 0);
        if (a != 0) {
            Int ia = Int(1) / a;
            /*
            for (int i = pc+1; i < isz(coeff); i++)
                coeff[i] *= ia;
            */
            if (int l = pc+1, r = isz(coeff)-1; l <= r)
                st.update(l, r, ia);
            A *= ia;
        }
        st.update(pc, pc, 0);
        pos.erase(pos.begin() + c);
    }
    std::cout << getAnswer() << "\n";
}
