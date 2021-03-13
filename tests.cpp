#include "source/finite_field.h"

#include <iostream>
#include <cassert>


int main() {
    GF<int>::N = 3;
    GF<int> a(0), b(1), c(2);
    // Arithmetics
    {
        assert(a + 1 == b);
        assert(b + 1 == c);
        assert(c + 1 == a);
        assert(a + b == b);
        assert(b + c == a);
        assert(c + c == b);
        assert(a * 123243212 == a);
        assert(b * 123345321 == 123345321);
        assert(b * c == c * b);
        assert(b / c == c);
        assert(b / (3 * 123421 + 2) == c);
        assert(a / c == a);
        assert(a - c == b);
        assert(b - c == c);
        assert((b - c) / 2 == b);
    }
    // Polynomials Arithmetics
    using P = Polynomial;
    {
        assert(P({1, 2, 9, -1}) + P({1, -17, 1}) == P({1, 3, -8, 0}));
        assert(P({1, 2, 9, -1}) + 1 == P({1, 2, 9, 0}));
        assert(P({1, 2, 9, -1}) * P({1, -17, 1}) == P({1, -15, -24, -152, 26, -1}));
        assert(P({1, 2, 9, -1}) * 2 == P({2, 4, 18, -2}));
        assert(P({1, 2, 9, -1}) * (-2) == P({1, 2, 9, -1}));
        assert(P({4, 5, 0, 2, 4}) / (-2) == P({4, 5, 0, 2, 4}));
        assert(P({4, 5, 0, 2, 4}) / 2 == P({2, 1, 3, 1, -1}));
        assert(P({3, 5, 0, 2, 4}) / P({1, 2, 1}) == P({3, -1, -1}));
        assert(P({3, 5, 0, 2, 4}) % P({1, 2, 1}) == P({5, 5}));
        auto a = P({1, 2, 3, 4, 5});
        auto b = P({6, 7, 8});
        assert(b * (a / b) + a % b == a);
    }
    //Galois Field Arithmetics
    GF<Polynomial>::N = P({1, 0, 0, 1, 2});
    using G = GF<Polynomial>;
    std::vector<G> ch;
    {
        G a({2, 1});
        G tmp(1);
        for (int i = 0; i < 80; ++i) {
            ch.push_back(tmp);
            tmp *= a;
        }
        for (int i = 0; i < ch.size() - 1; ++i) {
            for (int j = i + 1; j < ch.size(); ++j) {
                if (ch[i] == ch[j]) {
                    std::cout << i << '\t' << j << '\n';
                }
            }
        }
    }
    return 0;
}