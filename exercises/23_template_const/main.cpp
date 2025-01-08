#include <cstring>
#include <iostream>  // 添加这行用于错误输出，方便调试

// 断言宏，如果条件不成立则打印错误并终止程序
#define ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: " << message << std::endl; \
        std::exit(1); \
    }

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];  // 存储张量的每个维度的大小
    T *data;                // 存储张量的数据

    // 构造函数，初始化张量数据
    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // 填充 shape 数组并计算 size
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }

        data = new T[size];  // 为数据分配内存
        std::memset(data, 0, size * sizeof(T));  // 初始化数据为 0
    }

    // 析构函数，释放内存
    ~Tensor() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    // 支持下标访问运算符，提供访问数据的方式
    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    // 根据 indices 计算在 data 中的线性索引
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1;

        // 从后向前计算线性索引
        for (unsigned int i = N; i-- > 0;) {
            ASSERT(indices[i] < shape[i], "Invalid index");
            index += indices[i] * stride;
            stride *= shape[i];  // 计算当前维度的步长
        }

        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
