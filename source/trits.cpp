#include "trits.h"


#include <cmath>
#include <iostream>


using TNum = Converter::TNum;


Converter::Converter()
    :   ternSize(6)
    ,   binSize(8) {
}


Converter::Converter(size_t binSize, size_t ternSize)
    :   binSize(binSize)
    ,   ternSize(ternSize) {

}


void Converter::setBinSize(size_t a) {
    binSize = a;
}


void Converter::setTernSize(size_t a) {
    ternSize = a;
}


void Converter::ConvertFromBase (const std::vector<TNum>& bits,
                                 std::vector<TNum>& out,
                                 int fromBase,
                                 int toBase) {
    NumToVec(VecToNum(bits, fromBase), out, toBase);
}


size_t Converter::CountNumPos (const std::vector<TNum>& bits, int base) {
    return 0;
}


int Converter::VecToNum(const std::vector<TNum>& bits, int fromBase) {
    int ret(0);
    for (int i = bits.size() - 1; i >= 0; --i) {
        ret = ret * fromBase + bits[i];
    }
    return ret;
}


void Converter::NumToVec(int num, std::vector<TNum>& out, int toBase) {
    int ind(0);
    while (num != 0) {
        out[ind] = num % toBase;
        num /= toBase;
        ind += 1;
    }
}
