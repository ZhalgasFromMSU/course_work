#include "trits.h"
#include "time.h"

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
    Converter conv;
    std::vector<TNum> bin {0, 1, 1, 0, 0, 0, 1, 0};
    std::vector<TNum> out(6);

    Converter::ConvertFromBase(bin, out);

    print(out);
    return 0;
}
