#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>

int main() {
    // 第一部分：std::vector<int> 示例
    std::vector<int> vec{1, 2, 3, 4, 5};
    
    // ASSERT 1: size 应为 5
    assert(vec.size() == 5 && "Fill in the correct value.");
    
    // ASSERT 2: sizeof(vec) 返回向量对象的大小，通常为 24 字节（具体平台相关）
    assert(sizeof(vec) == 24 && "Fill in the correct value.");
    
    // ASSERT 3: 使用 std::memcmp 对比 vector 内部数据与 ans 数组
    int ans[]{1, 2, 3, 4, 5};
    assert(std::memcmp(vec.data(), ans, sizeof(ans)) == 0 && "Fill in the correct values.");
    
    // 第二部分：std::vector<double> 示例
    std::vector<double> vec2{1, 2, 3, 4, 5};
    
    // ASSERT 1: size 应为 5
    assert(vec2.size() == 5 && "Fill in the correct value.");
    
    // ASSERT 2: sizeof(vec2) 应为 24 字节（具体平台相关）
    assert(sizeof(vec2) == 24 && "Fill in the correct value.");
    
    // ASSERT 3: 使用 std::memcmp 对比 vec2 内部数据与 ans 数组
    double ans2[]{1, 2, 3, 4, 5};
    assert(std::memcmp(vec2.data(), ans2, sizeof(ans2)) == 0 && "Fill in the correct values.");
    
    // 添加元素：push_back 和 pop_back 测试
    vec2.push_back(6);
    assert(vec2.size() == 6 && "Fill in the correct value.");
    assert(sizeof(vec2) == 24 && "Fill in the correct value.");
    vec2.pop_back();
    assert(vec2.size() == 5 && "Fill in the correct value.");
    assert(sizeof(vec2) == 24 && "Fill in the correct value.");
    
    // 修改元素
    vec2[4] = 6;
    assert(vec2[0] == 1 && "Fill in the correct value.");
    assert(vec2[1] == 2 && "Fill in the correct value.");
    assert(vec2[2] == 3 && "Fill in the correct value.");
    assert(vec2[3] == 4 && "Fill in the correct value.");
    assert(vec2[4] == 6 && "Fill in the correct value.");
    
    // 使用 insert 和 erase 方法
    vec2.insert(vec2.begin() + 1, 1.5);
    assert((vec2 == std::vector<double>{1, 1.5, 2, 3, 4, 6}) && "Make this assertion pass.");
    vec2.erase(vec2.begin() + 1);
    assert((vec2 == std::vector<double>{1, 2, 3, 4, 6}) && "Make this assertion pass.");
    
    // 使用 shrink_to_fit 和 clear 方法
    vec2.shrink_to_fit();
    assert(vec2.capacity() == 5 && "Fill in the correct value.");
    vec2.clear();
    assert(vec2.empty() && "`vec2` is empty now.");
    assert(vec2.size() == 0 && "Fill in the correct value.");
    assert(vec2.capacity() == 5 && "Fill in the correct value.");
    
    // 第三部分：std::vector<char> 示例
    std::vector<char> vec3(48, 'z');
    
    // ASSERT 1: 第一个元素应为 'z'
    assert(vec3[0] == 'z' && "Make this assertion pass.");
    
    // ASSERT 2: 最后一个元素应为 'z'
    assert(vec3[47] == 'z' && "Make this assertion pass.");
    
    // ASSERT 3: size 应为 48
    assert(vec3.size() == 48 && "Make this assertion pass.");
    
    // ASSERT 4: sizeof(vec3) 返回向量对象的大小
    assert(sizeof(vec3) == 24 && "Fill in the correct value.");
    
    // 调整容量
    auto capacity = vec3.capacity();
    vec3.resize(16);
    assert(vec3.size() == 16 && "Fill in the correct value.");
    assert(vec3.capacity() == capacity && "Fill in the correct value.");
    
    // 调整容量并推入更多元素
    vec3.reserve(256);
    assert(vec3.size() == 16 && "Fill in the correct value.");
    assert(vec3.capacity() == 256 && "Fill in the correct value.");
    
    // 向 vec3 添加字符
    vec3.push_back('a');
    vec3.push_back('b');
    vec3.push_back('c');
    vec3.push_back('d');
    assert(vec3.size() == 20 && "Fill in the correct value.");
    assert(vec3.capacity() == 256 && "Fill in the correct value.");
    assert(vec3[15] == 'z' && "Fill in the correct value.");
    assert(vec3[16] == 'a' && "Fill in the correct value.");
    assert(vec3[17] == 'b' && "Fill in the correct value.");
    assert(vec3[18] == 'c' && "Fill in the correct value.");
    assert(vec3[19] == 'd' && "Fill in the correct value.");
    
    return 0;
}
