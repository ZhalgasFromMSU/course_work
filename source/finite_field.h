#pragma once

#include <iostream>


template<typename T, int N = 3>
class GF;



template<typename T, int N>
std::ostream& operator<<(std::ostream& out, const GF<T, N>& cur) {
    return out << cur.val;
}


template<typename T, int N>
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

    GF& normalize() {
        if (val >= 0) {
            val %= N;
        } else {
            val = (N - 1) + (val + 1) % N;
        }
        return *this;
    }

    
    GF normal() const {
        GF ret = *this;
        return ret.normalize();
    }

    GF& operator=(const GF& other) {
        val = other.val;
        return *this;
    }

    GF operator+(const GF& other) const {
        int ret = val + other.val;
        return GF(ret).normal();
    }

    GF operator-() const {
        return GF(-val);
    }

    GF operator-(const GF& other) const {
        return *this + (-other);
    }

    GF operator*(const GF& other) const {
        int ret = (*this).normal().val * other.normal().val;
        return GF(ret).normal();
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

    bool operator==(const GF& other) const {
        return val == other.val;
    }

    friend std::ostream& operator<< <>(std::ostream& out, const GF& cur);
};

