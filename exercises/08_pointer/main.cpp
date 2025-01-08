#include "../exercise.h"

// 判断从 ptr 开始，每 stride 个元素取 1 个元素，组成的数列是否满足斐波那契数列的关系
bool is_fibonacci(int *ptr, int len, int stride) {
    ASSERT(len >= 3, "`len` should be at least 3");
    // 如果 len 小于 3，直接返回 false，避免越界
    if (len < 3) return false;

    // 检查是否每组三个元素满足斐波那契关系
    for (int i = 0; i < len - 2; i++) {
        // 从第 i 个元素开始，按照 stride 跳跃取数
        int a = *(ptr + i * stride);         // arr[i]
        int b = *(ptr + (i + 1) * stride);   // arr[i+1]
        int c = *(ptr + (i + 2) * stride);   // arr[i+2]
        
        // 检查是否满足 arr[i+2] = arr[i] + arr[i+1]
        if (c != a + b) {
            return false;
        }
    }
    return true;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    int arr0[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55},
        arr1[]{0, 1, 2, 3, 4, 5, 6},
        arr2[]{99, 98, 4, 1, 7, 2, 11, 3, 18, 5, 29, 8, 47, 13, 76, 21, 123, 34, 199, 55, 322, 0, 0};
    // clang-format off
    ASSERT( is_fibonacci(arr0    , sizeof(arr0) / sizeof(*arr0)    , 1),         "arr0 is Fibonacci"    );
    ASSERT( is_fibonacci(arr0 + 2, sizeof(arr0) / sizeof(*arr0) - 4, 1), "part of arr0 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr1    , sizeof(arr1) / sizeof(*arr1)    , 1),         "arr1 is not Fibonacci");
    ASSERT( is_fibonacci(arr1 + 1,  3                              , 1), "part of arr1 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2    , sizeof(arr2) / sizeof(*arr2)    , 1),         "arr2 is not Fibonacci");
    ASSERT( is_fibonacci(arr2 + 2, 10                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT( is_fibonacci(arr2 + 3,  9                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2 + 3, 10                              , 2), "guard check"                  );
    ASSERT(!is_fibonacci(arr2 + 1, 10                              , 2), "guard check"                  );
    // clang-format on
    return 0;
}
