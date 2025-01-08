#include "../exercise.h"
#include <iostream>

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16]; // 用来存储斐波那契数列的缓存
    int cached;  // 用于跟踪已经计算的斐波那契数的数量
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 检查缓存中是否已经有计算结果
    if (i <= cache.cached) {
        return cache.cache[i];  // 如果已计算过，直接返回缓存值
    }

    // 如果缓存中没有，计算并缓存斐波那契数列
    for (int j = cache.cached; j <= i; ++j) {
        if (j == 0) {
            cache.cache[j] = 0;  // 斐波那契数列第 0 项是 0
        } else if (j == 1) {
            cache.cache[j] = 1;  // 斐波那契数列第 1 项是 1
        } else {
            cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];  // 其他项由前两项相加得到
        }
    }

    cache.cached = i;  // 更新缓存的最大索引
    return cache.cache[i];  // 返回计算结果
}

int main(int argc, char **argv) {
    // 初始化缓存结构体，确保所有值都被初始化
    FibonacciCache fib = { {0}, -1 };  // 初始化缓存为 {0} 并将 cached 设置为 -1

    // 测试 fibonacci 函数
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
