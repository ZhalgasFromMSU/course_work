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
    const TGf x;
    std::vector<TGf> primitiveElems;
    int fieldPower;
    std::unordered_map<TGf, int> poly2IdMap;
    std::unordered_map<int, TGf> id2PolyMap;
    std::vector<int> generator;

public:
    Coder(Poly primitivePoly)
        : primitivePoly(primitivePoly)
        , x({1, 0})
    {
        int curPow = 1;
        for (int i = 1; i <= m; ++i) {
            primitiveElems.push_back(x.Power(curPow));
            curPow *= q;
        }
        fieldPower = curPow;
        TGf cur(1);
        for (int i = 0; i < fieldPower - 1; ++i) {
            poly2IdMap[cur] = i;
            id2PolyMap[i] = cur;
            cur *= x;
        }
        MakeGenerator();
    }

    // gen = (x - alp)(x - alp^2)(x - alp^3)...(x-alp^(2t))
    void MakeGenerator() {
        std::vector<std::unordered_map<int, int>> ch{{{0, 1}}, {{1, -1}}};
        for (int i = 2; i <= 2 * t; ++i) {
            ch.push_back({});
            for (int j = ch.size() - 1; j >= 1; --j) {
                for (auto& [alp, cnt]: ch[j - 1]) {
                    ch[j][(alp + i) % (fieldPower - 1)] -= cnt;
                }
            }
        }
        for (int i = 0; i <= 2 * t; ++i) {
            TGf cur(0);
            for (auto& [alp, cnt]: ch[i]) {
                cur += PolyById(alp) * TGf(cnt);
            }
            generator.push_back(IdByPoly(cur));
        }
    }

    TGf PolyById(int i) const {
        return id2PolyMap.at(i);
    }

    int IdByPoly(const TGf& poly) const {
        return poly2IdMap.at(poly);
    }

    const std::vector<int>& GetGenerator() const {
        return generator;
    }
};

int Coder::q = 3;
int Coder::m = 6;
int Coder::k = 48;
int Coder::t = 4;