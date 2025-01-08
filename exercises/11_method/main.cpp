#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];  // 用于缓存斐波那契数列的值
    int cached;  // 记录已缓存的最大索引

    // 构造函数：初始化缓存数组并设置初始值
    Fibonacci() {
        // 初始化缓存数组的前两个值
        cache[0] = 0;
        cache[1] = 1;
        cached = 1;  // 目前缓存了 cache[0] 和 cache[1]
    }

    // 获取斐波那契数列第 i 项的值
    unsigned long long get(int i) {
        // 如果 i 小于等于已缓存的位置，直接返回缓存的值
        if (i <= cached) {
            return cache[i];
        }

        // 从已缓存的位置开始计算并缓存
        for (int j = cached + 1; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        // 更新缓存的最大位置
        cached = i;

        // 返回缓存的第 i 项
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化 Fibonacci 结构体
    Fibonacci fib;
    
    // 测试：斐波那契数列第 10 项应该是 55
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");

    // 输出斐波那契数列的第 10 项
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    return 0;
}
