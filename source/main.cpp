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
    GF<int, 3> a(1235), b(a * 123454231);
    decltype(b.normal()) c(3);
    c.asd();
    std::cout << a + b << '\n';
    return 0;
}
