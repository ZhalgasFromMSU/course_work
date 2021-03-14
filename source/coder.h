#pragma once

#include "finite_field.h"

#include <iostream>
#include <vector>
#include <unordered_map>


class Coder {
public:
    using TGf = GF<Polynomial>;
    using Poly = Polynomial;

    static int q; // Prime base of Polynomials
    static int m; // Number of elems in one symbol (q^m different symbols)
    static int k; // Number of information symbols
    static int t; // Number of corrected errors 2t * 6 == k
    // n = k + 2 * t, n <= q^m - 1

private:
    Poly primitivePoly;
    const Poly x;
    std::vector<TGf> primitiveElems;
    std::unordered_map<TGf, int> poly2IdMap;
    std::unordered_map<int, TGf> id2PolyMap;
    Poly generator;

public:
    Coder(Poly primitivePoly)
        :   primitivePoly(primitivePoly)
        ,   x({1, 0})
        ,   generator({1}) {
        int cur_pow = 1;
        for (int i = 1; i <= m; ++i) {
            primitiveElems.push_back(x.Power(cur_pow));
            cur_pow *= q;
        }
        cur = x;
        for (int i = 1; i < cur_pow; ++i) {
            poly2IdMap[cur] = i;
            id2PolyMap[i] = cur;
            cur *= x;
        }
        MakeGenerator();
    }

    void MakeGenerator() {
        return;
    }

    TGf polyById(int i) const {
        return id2PolyMap[i];
    }

    int idByPoly(const TGf& poly) const {
        return poly2IdMap[poly];
    }
};

int Coder::q = 3;
int Coder::m = 6;
int Coder::k = 48;
int Coder::t = 4;