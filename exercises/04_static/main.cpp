#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) {
    static int static_ = param;
    return static_++;
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");  // 第一次调用返回 5
    ASSERT(func(4) == 6, "static variable value incorrect");  // 第二次调用返回 6
    ASSERT(func(3) == 7, "static variable value incorrect");  // 第三次调用返回 7
    ASSERT(func(2) == 8, "static variable value incorrect");  // 第四次调用返回 8
    ASSERT(func(1) == 9, "static variable value incorrect");  // 第五次调用返回 9
    return 0;
}
