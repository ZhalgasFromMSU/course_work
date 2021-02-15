#pragma once


#include <chrono>


class Timer {

    using TStamp = std::chrono::high_resolution_clocl::time_point;

private:
    TStamp begin_, end_;

public:
    void Start() {
        begin_ = std::chrono::high_resolution_clock::now();
    }


    void End() {
        end_ = std::chrono::high_resolution_clock::now();
    }


    auto Count() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(eng - begin).count();
    }
};
