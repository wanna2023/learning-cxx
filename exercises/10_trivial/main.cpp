#include <iostream>
#include <cassert>

// 斐波那契数列缓存结构体
struct FibonacciCache {
    unsigned long long cache[16]; // 存储最多16个缓存值
    int cached; // 记录当前已缓存的最大位置
};

// Fibonacci计算函数
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 如果目标数字 i 小于或等于当前已缓存的数字，直接返回缓存值
    if (i <= cache.cached) {
        return cache.cache[i];
    }
    
    // 计算并缓存斐波那契数列，直到 i
    for (int j = cache.cached + 1; j <= i; ++j) {
        cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
    }
    
    // 更新已缓存的最大值
    cache.cached = i;
    
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化FibonacciCache结构体
    FibonacciCache fib = {{0, 1}, 1};  // 初始化前两个斐波那契数（0和1），并标记已缓存的最大位置为1
    
    // 计算并验证斐波那契数列
    assert(fibonacci(fib, 10) == 55);  // fibonacci(10)应该是55
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;  // 输出结果
    
    return 0;
}
