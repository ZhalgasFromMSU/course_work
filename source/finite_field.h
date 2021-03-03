#pragma once

#include <iostream>
#include <vector>


template<typename T, T N>
class GF;

template<int N>
class Polynomial;

template<typename T, T N>
std::ostream& operator<<(std::ostream& out, const GF<T, N>& cur) {
    return out << cur.val;
}

template<int N>
std::ostream& operator<<(std::ostream& out, const Polynomial<N>& cur) {
    char c(0);
    for (auto i: cur.val) {
        out << c << i;
        c = '\t';
    }
    return out;
}


template<typename T, T N>
class GF {
private:
    T val;

private:
    T gcd(T a, T b, T& x, T& y) const {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        T x1, y1;
        T ret = gcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return ret;
    }

    GF reverse(const GF& elem) const {
        T x, y;
        T ret = gcd(elem.val, N, x, y);
        if (ret != 1) {
            return GF(0);
        } else {
            return GF(x).Normal();
        }
    }

public:

    GF()
        :   val(0) {
    }

    GF(T a)
        :   val(a) {
    }

    GF& Normalize() {
        val = (val % N + N) % N;
        return *this;
    }
    
    GF Normal() const {
        GF ret = *this;
        return ret.Normalize();
    }

    GF Reverse() const {
        return reverse((*this).Normal());
    }

    GF& operator=(const GF& other) {
        val = other.val;
        return *this;
    }

    GF operator+(const GF& other) const {
        T ret = val + other.val;
        return GF(ret).Normal();
    }

    GF operator-() const {
        return GF(-val);
    }

    GF operator-(const GF& other) const {
        return *this + (-other);
    }

    GF operator*(const GF& other) const {
        T ret = (*this).Normal().val * other.Normal().val;
        return GF(ret).Normal();
    }
    
    GF operator/(const GF& other) const {
        return *this * other.Reverse();
    }

    T operator%(const GF& other) const {
        return val % other.val;
    }

    GF& operator+=(const GF& other) {
        return *this = *this + other;
    }

    GF& operator-=(const GF& other) {
        return *this = *this - other;
    }
    
    GF& operator*=(const GF& other) {
        return *this = *this * other;
    }

    GF& operator/=(const GF& other) {
        return *this = *this / other;
    }

    bool operator==(const GF& other) const {
        return val == other.val;
    }

    bool operator!=(const GF& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<< <>(std::ostream& out, const GF& cur);
};


template<int N>
class Polynomial {
private:
    std::vector<GF<int, N>> val;

public:
    constexpr Polynomial()
        :   val(1, 0) {
    }

    constexpr Polynomial(int a)
        :   val(1, a) {
    }

    constexpr Polynomial(int n, int def)
        :   val(n, def) {
    }

    constexpr Polynomial(const std::vector<GF<int, N>>& a)
        :   val(a) {
    }

    Polynomial& NormalizeCoeffs() {
        for (auto& i: val) {
            i.Normalize();
        }
        int idx(0);
        while (idx < val.size() && val[idx] == 0) {
            ++idx;
        }
        if (idx != 0 && val.size() != 1) {
            for (int i = idx; i < val.size(); ++i) {
                val[i - idx] = val[i];
            }
            val.resize(val.size() - idx);
        }
        return *this;
    }

    Polynomial& operator=(const Polynomial& other) {
        val = other.val;
        return *this;
    }

    Polynomial operator+(const Polynomial& other) const {
        int ind1 = val.size() - 1;
        int ind2 = other.val.size() - 1;
        if (ind2 > ind1) {
            auto ret = other;
            while (ind1 >= 0) {
                ret.val[ind2] += val[ind1];
                ind1 -= 1;
                ind2 -= 1;
            }
            return ret.NormalizeCoeffs();
        } else {
            auto ret = *this;
            while (ind2 >= 0) {
                ret.val[ind1] += other.val[ind2];
                ind1 -= 1;
                ind2 -= 1;
            }
            return ret.NormalizeCoeffs();
        }
    }

    Polynomial operator-() const {
        auto ret = *this;
        for (int i = 0; i < ret.val.size(); ++i) {
            ret.val[i] = -ret.val[i];
        }
        return ret;
    }

    Polynomial operator-(const Polynomial& other) const {
        return *this + (-other);
    }

    Polynomial operator*(const Polynomial& other) const {
        Polynomial ret(val.size() + other.val.size() - 1, 0);
        for (int i = val.size() - 1; i >= 0; --i) {
            int ind = i + other.val.size() - 1;
            for (int j = other.val.size() - 1; j >= 0; --j) {
                ret.val[ind] += val[i] * other.val[j];
                --ind;
            }
        }
        return ret.NormalizeCoeffs();
    }

    Polynomial operator/(const Polynomial& other) const {
        if (other.val.size() > val.size()) {
            return Polynomial(0);
        }
        Polynomial tmp(val);
        Polynomial ret(val.size() - other.val.size() + 1, 0);
        for (int i = 0; i < ret.val.size(); ++i) {
            ret.val[i] = tmp.val[i] / other.val[0];
            for (int j = 0; j < other.val.size(); ++j) {
                tmp.val[i + j] -= ret.val[i] * other.val[j];
            }
        }
        return ret.NormalizeCoeffs();
    }

    Polynomial operator%(const Polynomial& other) const {
        return ((*this) - (*this) / other * other).NormalizeCoeffs();
    }
    

    bool operator==(const Polynomial& other) const {
        return val == other.val;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<< <>(std::ostream& out, const Polynomial& cur);
};
