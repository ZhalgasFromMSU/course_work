#include "finite_field2.h"

#include <iostream>
#include <vector>

using std::cerr;

int main() {
    constexpr Polynomial<3, 6> a({1, 2, 3, 4, 5});
    for (auto i: a.GetVal()) {
        cerr << i.GetVal() << '\t';
    }
    cerr << '\n';
    auto b = std::move(a);
    for (auto i: a.GetVal()) {
        cerr << i.GetVal() << '\t';
    }
    cerr << '\n';
    return 0;
}