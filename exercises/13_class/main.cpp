#include "../exercise.h"
#include <iostream>

class Fibonacci {
    size_t cache[16];  // 用于缓存斐波那契数列
    int cached;        // 当前已缓存的斐波那契数的个数

public:
    // 构造器，初始化前两个数并设置已缓存的数目
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 返回斐波那契数列的第 i 项
    size_t get(int i) {
        // 如果缓存的数目小于请求的索引，则需要计算并更新缓存
        while (cached <= i) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];  // 斐波那契递推公式
            ++cached;
        }
        return cache[i];  // 返回缓存中的第 i 项
    }
};

int main(int argc, char **argv) {
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");  // 验证第 10 项是 55
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
