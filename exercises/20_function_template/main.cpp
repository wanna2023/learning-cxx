#include "../exercise.h"
#include <cmath>  // 用于浮点数比较时使用 std::fabs

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>

// 模板化的 plus 函数，支持多种数据类型
template <typename T>
T plus(T a, T b) {
    return a + b;
}

// 比较浮点数时，考虑到浮点数的精度误差
bool are_close(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // 浮点数的加法
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");

    // 浮点数加法比较，使用 are_close 来判断浮点数相等
    ASSERT(are_close(plus(0.1, 0.2), 0.3), "How to make this pass?");

    return 0;
}
