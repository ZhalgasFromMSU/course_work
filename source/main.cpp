#include "trits.h"
#include "time.h"
#include "finite_field.h"
#include "coder.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


int main() {
    GF<int>::N = 3;
    Coder::q = 3;
    Coder::m = 6;
    Coder::k = 48;
    Coder::t = 4;
    Polynomial prim3({1, 0, 2, 2, 1, 2, 2});
    Polynomial prim2({1, 0, 0, 0, 1, 1, 1, 0, 1});
    //Polynomial prim2({1, 0, 1, 1});
    GF<Polynomial>::N = prim3;

    Coder a(prim2);

    return 0;
}
