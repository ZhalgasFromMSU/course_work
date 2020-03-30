#include <iostream>
#include <vector>


template <typename TArg, typename... TArgs>
void foo(int a, std::vector<int>&& b, TArg d, TArgs... args) {
    std::cout << a << b.empty() << d << sizeof...(args);
    return;
}


int main() {
    foo(0, std::vector<int>(), 3, 4, 5);
}
