#include <iostream>
#include <cassert>

// 使用普通的函数来计算斐波那契数列，不再依赖于 `constexpr`
unsigned long long fibonacci(int i) {
    if (i == 0) return 0;
    if (i == 1) return 1;

    unsigned long long a = 0, b = 1;
    for (int j = 2; j <= i; ++j) {
        unsigned long long next = a + b;
        a = b;
        b = next;
    }
    return b;
}

int main(int argc, char **argv) {
    // 这里计算 fibonacci(20) 和 fibonacci(90)
    const auto FIB20 = fibonacci(20);
    assert(FIB20 == 6765); // 断言检查 fibonacci(20) 的结果
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    const auto ANS_N = 90;
    const auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
