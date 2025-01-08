#include "../exercise.h"
#include <algorithm> // std::copy

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity) : capacity(capacity), cached(2) {
        cache = new size_t[capacity]; // 为缓存分配内存
        cache[0] = 0;
        cache[1] = 1;
    }

    // 移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr; // 使原对象失去对资源的拥有权
        other.cached = 0;
        other.capacity = 0;
    }

    // 移动赋值运算符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 防止自赋值
            delete[] cache; // 释放当前对象的缓存内存

            cache = other.cache;
            cached = other.cached;
            capacity = other.capacity;

            other.cache = nullptr; // 使原对象失去对资源的拥有权
            other.cached = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // 析构器
    ~DynFibonacci() {
        delete[] cache; // 释放缓存内存
    }

    // 缓存优化的斐波那契计算
    size_t operator[](int i) {
        // 如果 i 超过了当前缓存的大小，计算新的值并更新缓存
        if (i >= cached) {
            for (; cached <= i; ++cached) {
                cache[cached] = cache[cached - 1] + cache[cached - 2];
            }
        }
        return cache[i];
    }

    // 不可修改的方法
    size_t operator[](int i) const {
        ASSERT(i < cached, "i out of range");
        return cache[i];
    }

    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
