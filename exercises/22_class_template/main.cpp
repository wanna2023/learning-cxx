#include "../exercise.h"
#include <cstring>
#include <algorithm>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    // 构造函数
    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 计算总元素个数
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape_[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    // 析构函数
    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动构造
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 单向广播的加法实现
    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查形状的广播规则：每个维度要么相等，要么其中一个维度为 1
        for (int i = 0; i < 4; ++i) {
            if (shape[i] != others.shape[i] && shape[i] != 1 && others.shape[i] != 1) {
                throw std::invalid_argument("Shapes are not broadcastable");
            }
        }

        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= shape[i]; // 计算当前张量的总元素个数
        }

        // 对于广播，我们需要进行元素逐个加法
        for (unsigned int i = 0; i < size; ++i) {
            unsigned int idx[4] = {0};
            unsigned int temp_idx = i;

            // 计算当前元素在 4D 张量中的坐标
            for (int j = 3; j >= 0; --j) {
                idx[j] = temp_idx % shape[j];
                temp_idx /= shape[j];
            }

            // 使用广播规则进行加法
            T other_value = 0;
            for (int j = 0; j < 4; ++j) {
                if (others.shape[j] == 1 || idx[j] < others.shape[j]) {
                    other_value = others.data[i];  // 如果这一维为1或idx小于对应维度大小，取others中的对应元素
                    break;
                }
            }

            data[i] += other_value;
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
