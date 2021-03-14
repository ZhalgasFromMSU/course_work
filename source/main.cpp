#include "trits.h"
#include "time.h"
#include "finite_field.h"
#include "coder.h"

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
    Polynomial prim({1, 0, 2, 2, 1, 2, 2});
    GF<int>::N = 3;
    GF<Polynomial>::N = prim;
    Coder a(prim);
    return 0;
}
