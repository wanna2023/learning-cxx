#include "../exercise.h"

// 枚举类型，ColorEnum 和 Color 有相同的枚举值
enum ColorEnum : unsigned char {
    COLOR_RED = 31,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
};

// 有作用域的枚举类型，提供类型安全
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

// 使用 static_cast 完成类型转换
ColorEnum convert_by_pun(Color c) {
    return static_cast<ColorEnum>(static_cast<int>(c));
}

int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}
