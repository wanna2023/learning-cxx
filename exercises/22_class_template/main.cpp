#include <iostream>
#include <cstring>  // for std::memcpy
#include <stdexcept> // for std::invalid_argument

template <typename T>
class Tensor4D {
public:
    unsigned int shape[4];
    T *data;

    // 构造函数
    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];  // 计算元素的总个数
        }
        
        // 为 data 分配内存
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));  // 复制数据
    }

    // 析构函数
    ~Tensor4D() {
        delete[] data;  // 释放内存
    }

    // 禁止复制和移动
    Tensor4D(const Tensor4D &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 加法运算符支持广播
    Tensor4D &operator+=(const Tensor4D &others) {
        // 检查形状是否可以广播
        for (int i = 0; i < 4; ++i) {
            if (shape[i] != others.shape[i] && others.shape[i] != 1) {
                throw std::invalid_argument("Shapes are not broadcastable.");
            }
        }

        // 广播加法
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            size *= shape[i];  // 计算当前张量的大小
        }

        // 执行加法操作
        for (unsigned int i = 0; i < size; ++i) {
            unsigned int idx = i;
            unsigned int other_idx = 0;
            for (int j = 3; j >= 0; --j) {
                unsigned int dim_this = shape[j];
                unsigned int dim_other = others.shape[j];
                unsigned int stride_this = 1;
                unsigned int stride_other = 1;

                // 计算 stride
                for (int k = j + 1; k < 4; ++k) {
                    stride_this *= shape[k];
                    stride_other *= others.shape[k];
                }

                if (dim_other == 1) {
                    other_idx += idx / stride_this * stride_other;  // 如果维度为1，广播该维度
                } else {
                    other_idx += (idx / stride_this) % dim_other * stride_other;
                }

                idx %= stride_this;
            }

            // 执行加法
            data[i] += others.data[other_idx];
        }

        return *this;
    }
};

// ---- 测试代码 ----
int main() {
    {
        unsigned int shape[]{1, 2, 3, 4};
        int data[]{
            1,  2,  3,  4,
            5,  6,  7,  8,
            9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24
        };

        // 创建 Tensor4D 对象
        Tensor4D<int> t0(shape, data);
        Tensor4D<int> t1(shape, data);

        t0 += t1;  // 执行加法运算

        // 验证结果
        for (unsigned int i = 0; i < 24; ++i) {
            if (t0.data[i] != data[i] * 2) {
                std::cerr << "Test failed at index " << i << std::endl;
                return 1;
            }
        }
        std::cout << "Test passed!" << std::endl;
    }

    {
        unsigned int s0[]{1, 2, 3, 4};
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,
            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6
        };

        unsigned int s1[]{1, 2, 3, 1};
        float d1[]{
            6, 5, 4,
            3, 2, 1
        };

        Tensor4D<float> t0(s0, d0);
        Tensor4D<float> t1(s1, d1);

        t0 += t1;  // 执行加法运算

        // 验证结果
        for (unsigned int i = 0; i < 24; ++i) {
            if (t0.data[i] != 7.0f) {
                std::cerr << "Test failed at index " << i << std::endl;
                return 1;
            }
        }
        std::cout << "Test passed!" << std::endl;
    }

    return 0;
}
