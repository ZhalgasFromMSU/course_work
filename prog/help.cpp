#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
#include <iterator>
#include <string>
#include <random>
#include <cstdlib>


template <typename TFunc>
void dispatcher(int base, int num, std::vector<int>& inp, TFunc& foo) {
    foo(inp);
    std::cout << std::endl;
}


template <typename TFunc, typename... TArgs>
void dispatcher(int base, int num, std::vector<int>& inp, TFunc&& foo, TArgs... args) {
    if (inp.size() == num) {
        foo(inp);
        std::cout << '\t';
        dispatcher(base, num, inp, args...);
    } else {
        for (int i = 0; i < base; ++i) {
            inp.push_back(i);
            dispatcher(base, num, inp, std::forward<TFunc>(foo), args...);
            inp.pop_back();
        }
    }
}


class SetPrinter {
private:
    int base_;
public:
    SetPrinter(int base)
       :    base_(base)
    {}

    void operator()(const std::vector<int>& inp) {
        std::string sep;
        for (int i: inp) {
            std::cout << sep << i;
            sep = ' ';
        }
    }
};


class LinFunc {
private:
    int base_;
    int vars_;
    std::vector<std::vector<int>> coefs_;
public:
    LinFunc(int base, int vars)
        :   base_(base)
        ,   vars_(vars) {
        std::vector<int> tmp;
        GenCoefs(0, tmp);
    }

    void GenCoefs(int cur, std::vector<int>& tmp) {
        if (cur == vars_ + 1) {
            coefs_.push_back(tmp);
            return;
        }
        for (int i = 0; i < base_; ++i) {
            tmp.push_back(i);
            GenCoefs(cur + 1, tmp);
            tmp.pop_back();
        }
    }

    void operator()(const std::vector<int>& inp) {
        std::string sep;
        for (const auto& vec: coefs_) {
            int ans = vec[vec.size() - 1];
            for (int i = 0; i < vars_; ++i) {
                ans += inp[i] * vec[i];
            }
            std::cout << sep << ans % base_;
            sep = '\t';
        }
    }
};


class WebbFunc {
private:
    int base_;
public:
    WebbFunc(int base)
        :   base_(base)
    {}

    void operator()(const std::vector<int>& inp) {
        std::cout << (std::max(inp[0],inp[1]) + 1) % base_;
    }
};


class FullFunc {
private:
    int base_;
public:
    FullFunc(int base)
        :   base_(base)
    {}

    void operator()(const std::vector<int>& inp) {
        std::cout << base_ - 1 << '\t' <<
                    (inp[0] - inp[1] ? inp[0] > inp[1] : 0) << '\t' <<
                    (inp[0] + inp[1]) % base_;
    }
};


class RandomFunc {
private:
    int base_;
    int vars_;
    std::vector<int> resultVector;
public:
    RandomFunc(int base, int vars)
        :   base_(base)
        ,   vars_(vars)
    {
        GenerateFunc();
    }

    int BinPow(int base, int power) {
        if (power == 0) {
            return 1;
        } else if (power % 2 == 0) {
            int tmp = BinPow(base, power / 2);
            return tmp * tmp;
        } else {
            return base * BinPow(base, power - 1);
        }
    }

    int VecToInt(const std::vector<int>& inp) const {
        int ret = 0;
        for (int i: inp) {
            ret = ret * base_ + i;
        }
        return ret;
    }

    void GenerateFunc() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, base_ - 1);
        int num = BinPow(base_, vars_);
        for (int i = 0; i < num; ++i) {
            resultVector.push_back(dis(gen));
        }
    }

    void operator()(const std::vector<int>& inp) {
        std::cout << resultVector.at(VecToInt(inp));
    }

    void print() const {
        std::string sep;
        for (int i: resultVector) {
            std::cout << sep << i;
            sep = " ";
        }
        std::cout << '\n';
    }
};


int main(int argc, char* argv[]) {
    int base = atoi(argv[1]);
    int vars = atoi(argv[2]);
    std::vector<int> inp;
    dispatcher(base, vars, inp, SetPrinter(base), RandomFunc(base, vars), RandomFunc(base, vars), RandomFunc(base, vars));
    return 0;
}
