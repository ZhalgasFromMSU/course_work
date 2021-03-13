#include "trits.h"
#include "time.h"
#include "finite_field.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


using TNum = Converter::TNum;


template<typename T>
void print(const T& a) {
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}


int main() {
    GF<int>::N = 3;
    GF<Polynomial>::N = {1, 0, 0, 1};

    auto b = Polynomial({1, 0, 8, 1, 2});
    std::cout << b.NormalizeCoeffs() << '\n';
    return 0;
}
