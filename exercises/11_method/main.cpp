#include "../exercise.h"
#include <iostream>

struct Fibonacci {
    unsigned long long cache[128];  // 用于缓存斐波那契数列的值
    int cached;  // 用于标记缓存中最后计算的斐波那契数列项

    // 构造函数初始化缓存
    Fibonacci() : cached(-1) {
        // 初始化斐波那契数列的前两个值
        cache[0] = 0;
        cache[1] = 1;
    }

    // 获取斐波那契数列的第 i 项，利用缓存优化
    unsigned long long get(int i) {
        // 如果请求的值已经在缓存中，直接返回
        if (i <= cached) {
            return cache[i];
        }

        // 否则，从当前缓存项继续计算，直到计算到第 i 项
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        // 更新缓存标记
        cached = i;
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 创建 Fibonacci 对象，初始化时会处理缓存
    Fibonacci fib;

    // 测试 fibonacci(10) 的值是否正确
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    return 0;
}
