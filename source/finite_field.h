#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <initializer_list>

template<typename T>
class GF;

class Polynomial;


template<typename T>
std::ostream& operator<<(std::ostream& out, const GF<T>& cur) {
    return out << cur.val;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& cur);


template<typename T>
class GF {
private:
    T val;
public:
    static T N;

private:
    T gcd(const T& a, const T& b, T& x, T& y) const {
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

    GF(const GF& other)
        :   val(other.val) {
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
        return this->Normal().val == other.Normal().val;
    }

    bool operator!=(const GF& other) const {
        return !(*this == other);
    }

    GF Power(int n) const {
        if (n == 0) {
            return GF(T(1));
        } else if (n % 2 == 0) {
            auto ret = Power(n / 2);
            return ret * ret;
        } else {
            return Power(n - 1) * *this;
        }
    }

    friend std::ostream& operator<< <>(std::ostream& out, const GF& cur);
    friend std::hash<GF<T>>;
};


class Polynomial {
private:
    std::vector<GF<int>> val;

public:
    Polynomial()
        :   val(1, 0) {
    }

    Polynomial(int a)
        :   val(1, a) {
    }

    Polynomial(int n, int def)
        :   val(n, def) {
    }

    Polynomial(const std::vector<GF<int>>& a)
        :   val(a) {
    }

    Polynomial(std::initializer_list<GF<int>> a)
        :   val(a) {
    }

    Polynomial& operator=(const std::vector<GF<int>>& a) {
        val = a;
        return *this;
    }

    Polynomial NormalCoeffs() const {
        auto ret = *this;
        for (auto& i: ret.val) {
            i.Normalize();
        }
        int idx(0);
        while (idx < ret.val.size() && ret.val[idx] == 0) {
            ++idx;
        }
        if (idx != 0 && ret.val.size() != 1) {
            for (int i = idx; i < ret.val.size(); ++i) {
                ret.val[i - idx] = ret.val[i];
            }
            ret.val.resize(ret.val.size() - idx);
        }
        return ret;
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
        return this->NormalCoeffs().val == other.NormalCoeffs().val;
    }

    bool operator!=(const Polynomial& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& cur);
    friend std::hash<Polynomial>;
};

template<>
int GF<int>::N = 2;

template<>
Polynomial GF<Polynomial>::N = 1;

template<typename T>
struct std::hash<GF<T>> {
    size_t operator()(const GF<T>& gfInt) const {
        return std::hash<T>()(gfInt.val);
    }
};

template<>
struct std::hash<Polynomial> {
    size_t operator()(const Polynomial& polynomial) const {
        size_t ret(0);
        for (auto i: polynomial.NormalCoeffs().val) {
            ret ^= std::hash<GF<int>>()(i);
        }
        return ret;
    }
};

std::ostream& operator<<(std::ostream& out, const Polynomial& cur) {
    char c(0);
    for (auto i: cur.val) {
        out << c << i;
        c = '\t';
    }
    return out;
}

