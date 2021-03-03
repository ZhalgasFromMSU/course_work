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
    static int N(3);
    Polynomial<N> base(3, 1);
    std::cout << base << '\n';
    return 0;
}
