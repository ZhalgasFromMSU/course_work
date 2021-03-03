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
    constexpr Polynomial<2> base(3, 2);
    GF<Polynomial<2>, base> inp(0);
    return 0;
}
