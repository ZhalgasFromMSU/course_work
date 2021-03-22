#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <array>


template<typename T, T Base>
class GF;

template<int Base, int Power>
class Polynomial;


template<typename T, T Base>
struct std::hash<GF<T, Base>> {
    size_t operator()(const GF<T, Base>& cur) const {
        return std::hash<T>(cur);
    }
};


template<typename T, T Base>
class GF {
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
        T ret = gcd(elem.Normal().GetVal(), Base, x, y);

        if (ret != 1) {
            return GF(0);
        } else {
            return GF(x);
        }
    }

    GF power(const GF& elem, int power) const {
        if (power == 0) {
            return 1;
        }

        GF ret = power(elem, power / 2);
        if (power % 2 == 0) {
            return ret * ret;
        }

        return ret * elem;
    }

public:
//Constructors
    constexpr GF()
        : _val(0)
    {}

    constexpr GF(const T& val)
        : _val((val % Base + Base) % Base)
    {}

    constexpr GF(T&& val)
        : _val(val)
    {}

    constexpr GF(std::initializer_list<T> val)
        : _val(val)
    {}

    constexpr GF(const GF& other)
        : _val(other._val)
    {}

    constexpr GF(GF&& other)
        : _val(other._val)
    {}

    GF& operator=(const GF& other) {
        _val = other._val;
        return *this;
    }

//Helper
    const T& GetVal() const {
        return _val;
    }

    GF& Normalize() {
        _val = (_val % Base + Base) % Base;
        return *this;
    }

    GF Normal() const {
        GF ret = *this;
        return ret.Normalize();
    }

    GF Reverse() const {
        return reverse(*this);
    }

    GF Power(int n) const {
        return power(*this, n);
    }

//Operators
    GF operator+(const GF& other) const {
        return GF(_val + other._val);
    }

    GF operator-() const {
        return GF(-_val);
    }

    GF operator-(const GF& other) const {
        return *this + (-other);
    }

    GF operator*(const GF& other) const {
        return GF(_val * other._val);
    }

    GF operator/(const GF& other) const {
        return *this * other.Reverse();
    }

    T operator%(const GF& other) const {
        return _val % other._val;
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
        return this->Normal()._val == other.Normal()._val;
    }

    bool operator!=(const GF& other) const {
        return !(*this == other);
    }

//Friends
    friend std::ostream& operator<<(std::ostream& out, const GF& cur) {
        out << cur.GetVal();
        return out;
    }

    friend std::hash<GF>;

private:
    T _val;
};


template<int Base, int Power>
class Polynomial {
private:
    using TVal = GF<int, Base>;
    static constexpr int ArrSize = Power + 1;
    static constexpr int BufSize = 2 * Power + 1;

public:
//Constructors
    constexpr Polynomial()
    {}

    constexpr Polynomial(const std::array<TVal, ArrSize>& val)
        : _val(val)
    {}

    constexpr Polynomial(std::array<TVal, ArrSize>&& val)
        : _val(val)
    {}

    constexpr Polynomial(std::initializer_list<TVal>& val)
        : _val()
    {
        auto idx(0);
        for (auto i: val) {
            _val[idx] = i;
            idx += 1;
        }
        for (auto i = 0; i < idx; ++i) {
            _val[ArrSize - 1 - i] = _val[idx - 1 - i];
        }
    }

    constexpr Polynomial(const Polynomial& other)
        : _val(other._val)
    {}

    constexpr Polynomial(Polynomial&& other)
        : _val(other.val)
    {}

    Polynomial& operator=(const Polynomial& other) {
        _val = other._val;
        return *this;
    }

//Helpers
    const std::array<TVal, ArrSize>& GetVal() const {
        return _val;
    }

    Polynomial& NormalizeCoeffs() {
        for (auto& i: _val) {
            i.Normalize();
        }
        return *this;
    }

private:
    std::array<TVal, ArrSize> _val;
    std::array<TVal, BufSize> _buff;
};