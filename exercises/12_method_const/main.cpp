#include "../exercise.h"
#include <iostream>

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    
    // 修改方法签名，使其成为 constexpr 函数
    constexpr int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    // 使用 constexpr 初始化 Fibonacci 对象
    constexpr Fibonacci FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    
    // 验证测试条件
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
