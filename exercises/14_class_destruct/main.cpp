#include "../exercise.h"
#include <iostream>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;  // 动态分配的缓存数组
    int cached;     // 当前已缓存的斐波那契数个数
    int capacity;   // 缓存的最大容量

public:
    /// 构造器，初始化缓存容量并分配缓存空间
    DynFibonacci(int capacity) : capacity(capacity), cached(2) {
        cache = new size_t[capacity];  // 动态分配缓存空间
        cache[0] = 0;  // 初始化斐波那契数列的前两个数
        cache[1] = 1;
    }

    /// 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;  // 释放动态分配的内存
    }

    /// 获取斐波那契数列的第 i 项，使用缓存优化
    size_t get(int i) {
        // 如果缓存的数目小于请求的索引，继续计算并更新缓存
        while (cached <= i) {
            if (cached >= capacity) {
                std::cerr << "Cache overflow! Requested index exceeds capacity." << std::endl;
                return -1;  // 返回错误代码，表示缓存溢出
            }
            cache[cached] = cache[cached - 1] + cache[cached - 2];  // 斐波那契递推公式
            ++cached;
        }
        return cache[i];  // 返回缓存中的第 i 项
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
