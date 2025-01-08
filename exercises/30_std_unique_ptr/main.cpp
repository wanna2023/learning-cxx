#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;

// reset 函数，每次调用返回一个新的 Resource
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');  // 如果已有资源，记录 'r'
    return std::make_unique<Resource>();  // 返回一个新的 Resource
}

// drop 函数，将资源丢弃并返回 nullptr
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');  // 如果已有资源，记录 'd'
    return nullptr;  // 丢弃资源
}

// forward 函数，返回传入的资源
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');  // 如果已有资源，记录 'f'
    return ptr;  // 返回传入的资源
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    // 第一个测试用例
    drop(forward(reset(nullptr)));  // 创建一个新资源，记录 'r'，然后丢弃资源，记录 'd'
    problems[0] = std::move(RECORDS);  // 保存 RECORDS

    // 第二个测试用例
    forward(drop(reset(forward(forward(reset(nullptr))))));  // 嵌套调用，资源生命周期较复杂
    problems[1] = std::move(RECORDS);  // 保存 RECORDS

    // 第三个测试用例
    drop(drop(reset(drop(reset(reset(nullptr))))));  // 更复杂的资源丢弃和重置
    problems[2] = std::move(RECORDS);  // 保存 RECORDS

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},  // 第一个问题：记录顺序是 'r' 和 'd'
        {"ffffdd", "rffdd"},  // 第二个问题：根据资源生命周期推断，记录顺序（注意这个依赖平台和对象析构的顺序）
        {"fdffff", "fddff", ""},  // 第三个问题：根据资源管理和丢弃顺序推断记录
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
