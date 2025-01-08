#include "../exercise.h"
#include <algorithm>
#include <cstring>
#include <iostream>

// READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 初始化形状并计算 size
        std::memcpy(shape, shape_, sizeof(shape));
        for (int i = 0; i < 4; ++i) {
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 处理单向广播加法
    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查是否可以进行广播
        for (int i = 0; i < 4; ++i) {
            if (shape[i] != others.shape[i] && others.shape[i] != 1) {
                // 如果两个张量的形状在该维度上不匹配且 others 的维度不为 1，则无法广播
                throw std::invalid_argument("Shapes are not compatible for broadcasting.");
            }
        }

        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= shape[i];
        }

        // 执行加法操作，处理广播
        for (unsigned int i = 0; i < size; ++i) {
            unsigned int idx[4] = {0};  // 当前元素在 4 维空间中的索引
            unsigned int tmp = i;

            // 反向计算四个维度的索引
            for (int d = 3; d >= 0; --d) {
                idx[d] = tmp % shape[d];
                tmp /= shape[d];
            }

            // 处理广播：对每一维度进行适当的处理
            T val = 0;
            for (int d = 0; d < 4; ++d) {
                if (others.shape[d] == 1 || others.shape[d] == shape[d]) {
                    val += others.data[i]; // 直接加上对应的元素
                }
            }

            // 执行广播加法
            data[i] += val;
        }

        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D<int>(shape, data);
        auto t1 = Tensor4D<int>(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D<float>(s0, d0);
        auto t1 = Tensor4D<float>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D<double>(s0, d0);
        auto t1 = Tensor4D<double>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
