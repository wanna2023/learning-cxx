#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>

class Resource {
public:
    Resource() { std::cout << "Resource created." << std::endl; }
    ~Resource() { std::cout << "Resource destroyed." << std::endl; }

    void record(const std::string& operation) {
        std::cout << "Recorded operation: " << operation << std::endl;
        RECORDS.push_back(operation);
    }

    static std::vector<std::string> RECORDS;
};

std::vector<std::string> Resource::RECORDS;

Resource* reset(Resource* resource) {
    if (resource) {
        delete resource;
    }
    return new Resource();
}

Resource* forward(Resource* resource) {
    resource->record("f");
    return resource;
}

Resource* drop(Resource* resource) {
    resource->record("d");
    delete resource;
    return nullptr;
}

int main() {
    // 1. Problem 0: drop(forward(reset(nullptr))) -> 'fd'
    drop(forward(reset(nullptr)));
    std::vector<std::string> problems[3];
    problems[0] = std::move(Resource::RECORDS); // Capture results of problem 0

    // 2. Problem 1: forward(drop(reset(forward(forward(reset(nullptr)))))) -> 'fdfd'
    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(Resource::RECORDS); // Capture results of problem 1

    // 3. Problem 2: drop(drop(reset(drop(reset(reset(nullptr)))))) -> 'fddf'
    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(Resource::RECORDS); // Capture results of problem 2

    // 预期答案
    std::vector<const char*> answers[] = {
        {"fd"},                           // Expected answer for problem 0
        {"fdfd"},                         // Expected answer for problem 1
        {"fddf"}                          // Expected answer for problem 2
    };

    // ---- 不要修改以下代码 ----
    for (auto i = 0; i < 3; ++i) {
        assert(problems[i].size() == std::size(answers[i]) && "wrong size"); // 检查问题的结果大小是否一致
        for (auto j = 0; j < problems[i].size(); ++j) {
            assert(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0 && "wrong location"); // 检查具体结果是否一致
        }
    }

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
