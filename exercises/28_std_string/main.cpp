#include "../exercise.h"
#include <string>
#include <type_traits>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;  // hello 是 std::string 类型
    auto world = "world";   // world 是 const char* 类型
    
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    
    // 判断 hello 的类型，应该是 std::string
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    
    // 判断 world 的类型，应该是 const char*
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    
    // 将 `hello + ", " + world + '!'` 结果拼接成正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    
    return 0;
}
