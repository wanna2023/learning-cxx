#include "../exercise.h"
#include <iostream>

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity) : capacity(capacity), cached(2) {
        // 分配内存并初始化前两个斐波那契数
        cache = new size_t[capacity];
        cache[0] = 0;
        cache[1] = 1;
    }

    // 复制构造器：深拷贝
    DynFibonacci(const DynFibonacci& other) : capacity(other.capacity), cached(other.cached) {
        cache = new size_t[capacity]; // 分配新内存
        std::copy(other.cache, other.cache + cached, cache); // 深拷贝缓存
    }

    // 析构器：释放缓存空间
    ~DynFibonacci() {
        delete[] cache; // 释放动态分配的内存
    }

    // 实现缓存优化的斐波那契计算
    size_t get(int i) {
        // 如果 i 小于已缓存的数量，直接返回
        if (i < cached) {
            return cache[i];
        }

        // 否则，计算新的斐波那契数并填充缓存
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // const 版本的 get 方法：只读
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
        return -1; // 避免编译器警告
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");

    // 测试复制构造器
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");

    return 0;
}
