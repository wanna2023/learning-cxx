#include "../exercise.h"

// TODO: 改正函数实现，实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(int i) {
    // 用一个静态缓存数组来保存已经计算的斐波那契数列值
    static unsigned long long cache[96] = {0};  // 初始化数组
    static bool initialized = false;  // 标记是否已初始化
    
    if (i == 0) return 0;  // 斐波那契数列的第一个数是 0
    if (i == 1) return 1;  // 斐波那契数列的第二个数是 1
    
    // 如果缓存尚未初始化，则执行初始化
    if (!initialized) {
        cache[0] = 0;  // 定义第0个斐波那契数
        cache[1] = 1;  // 定义第1个斐波那契数
        // 从2开始计算并填充缓存
        for (int j = 2; j < 96; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        initialized = true;  // 标记为已初始化
    }
    
    // 返回缓存中的值
    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}
