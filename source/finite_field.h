#pragma once

#include <iostream>


template<int N = 3>
class GF;


template<int N>
std::ostream& operator<<(std::ostream& out, const GF<N>& cur) {
    return out << cur.val;
}


template<int N>
class GF {
private:
    int val;
public:

    GF()
        :   val(0) {
    }

    GF(int a)
        :   val(a) {
    }

    GF<N> operator+(const GF<N>& other) const {
        int ret = val + other.val;
        if (ret >= 0) {
            ret = ret % N;
        } else {
            ret = (N - 1) + (ret + 1) % N;
        }
        return GF<N>(ret);
    }

    GF<N> operator-() const {
        return GF<N>(-val);
    }

    GF<N> operator-(const GF<N>& other) const {
        return *this + (-other);
    }

    GF<N> operator*(const GF<N>& other) const {
        int ret = val * other.val;
        if (ret >= 0) {
            ret %= N;
        } else {
            ret = (N - 1) + (ret + 1) % N;
        }
        return GF<N>(ret);
    }

    friend std::ostream& operator<< <>(std::ostream& out, const GF<N>& cur);
};

