#include "source/finite_field.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
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
    GF<Polynomial>::N = P({1, 0, 2, 2, 1, 2, 2}); // x^6 + 2x^5 + 2x^4 + x + 2x + 2
    using G = GF<Polynomial>;
    G x({1, 0});
    for (int p: {1, 3, 9, 27, 81, 243}) {
        std::vector<G> ch;
        G a = x.Power(p);
        for (int i = 1; i <= 728; ++i) {
            ch.push_back(a.Power(i));
        }
        for (int i = 0; i < ch.size() - 1; ++i) {
            for (int j = i + 1; j < ch.size(); ++j) {
                assert(ch[i] != ch[j]);
            }
        }
    }
    //Hash check
    {
        std::unordered_set<G> ch1;
        G x({1, 2, 3, 4, 5});
        ch1.insert(x);
        assert(ch1.size() == 1);
        ch1.insert(x + G({3, 0, 0}));
        assert(ch1.size() == 1);
        std::unordered_map<G, int> ch2;
        ch2[x] = 1;
        assert(ch2.size() == 1);
        ch2[x] += 10;
        assert(ch2[x] == 11);
        G y({5, 4, 3, 2, 1});
        ch2[y] = 5;
        assert(ch2.size() == 2);
        ch2[y] += 1;
        assert(ch2[y] == 6);

        ch2.clear();
        x = G({1, 0});
        auto cur = x;
        std::unordered_set<int> nums;
        for (int i = 1; i <= 728; ++i) {
            ch2[cur] = i;
            cur *= x;
            nums.insert(i);
        }
        assert(ch2.size() == 728);
        assert(ch2[G({1, 0})] == 1);
        assert(ch2[G({1, 0, 0, 0})] == 3);
        assert(ch2[G({1, 0, 2, 1})] == 9);
        assert(ch2[G({2, 2})] == 27);
        assert(ch2[G({2, 0, 0, 2})] == 81);
        assert(ch2[G({2, 0, 1, 1})] == 243);
        for (auto& [x, idx]: ch2) {
            assert(nums.find(idx) != nums.end());
            nums.erase(idx);
        }
        assert(nums.size() == 0);
    }
    return 0;
}