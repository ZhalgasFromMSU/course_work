#pragma once


#include <cstdint>
#include <vector>


class Converter {

private:
    size_t ternSize;
    size_t binSize;

public:
    typedef int_fast8_t TNum;

    Converter();
    Converter(size_t binSize, size_t ternSize);

    void setBinSize(size_t a);
    void setTernSize(size_t a);
    /*
        bits - vector of 0/1s, representing binary number
        out - vector, already allocated

        transforms binary number in inp into ternary number and writes it in out in revere order
    */
    static void ConvertFromBase (const std::vector<TNum>& bits,
                                 std::vector<TNum>& out,
                                 int fromBase = 2,
                                 int toBase = 3);


    /*
        bits - vector of 0/1s, representing binary 
        return - smallest number of trits, required to present inp in ternary
    */
    static size_t CountNumPos (const std::vector<TNum>& bits, int base = 3);


    static int VecToNum(const std::vector<TNum>& bits, int base = 2);
    static void NumToVec(int num, std::vector<TNum>& out, int base = 2);
};
