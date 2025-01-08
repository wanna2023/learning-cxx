#include "../exercise.h"
#include <numeric>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    
    // 计算张量的元素数量
    int size = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>());
    
    // 计算每个元素的字节大小
    int byte_size = size * sizeof(DataType);  // `sizeof(DataType)` 获取 float 类型的字节大小

    // 验证计算结果
    ASSERT(byte_size == 602112, "4x1x3x224x224 = 602112");

    return 0;
}
