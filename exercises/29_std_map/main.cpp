#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

// key_exists 函数，检查给定的键是否存在于 map 中
template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // 使用 find 方法查找键，如果找不到返回 map.end()
    return map.find(key) != map.end();
}

// set 函数，插入或更新给定的键值对
template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // 使用 operator[] 插入或更新键值对
    map[key] = value;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    // 向 secrets map 中插入键值对
    set(secrets, "hello"s, "world"s);
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" should be in `secrets`");
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" should not be in `secrets`");

    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);

    // 验证插入的键值对
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    // 更新已有的键值对
    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}
