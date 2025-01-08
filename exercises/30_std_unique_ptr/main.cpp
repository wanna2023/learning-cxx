#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// Global record container to hold the results of destructed Resource objects.
std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    // Record a single character into the _records string.
    void record(char record) {
        _records.push_back(record);
    }

    // Destructor: add _records to the global RECORDS vector.
    ~Resource() {
        RECORDS.push_back(_records);
    }
};

// Alias for the unique pointer type to Resource.
using Unique = std::unique_ptr<Resource>;

// Function to reset the resource, record 'r' and return a new Resource.
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}

// Function to drop the resource, record 'd' and return nullptr.
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}

// Function to forward the resource, record 'f' and return the original ptr.
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    // Problem 0: drop(forward(reset(nullptr))) -> 'fd'
    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    // Problem 1: forward(drop(reset(forward(forward(reset(nullptr)))))) -> Analyze sequence of operations
    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    // Problem 2: drop(drop(reset(drop(reset(reset(nullptr)))))) -> Analyze sequence of operations
    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- Don't modify the code below ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: Analyze the resource lifecycle and fill the expected results for problems[1]
        {"fdfd", "", "", "", "", "", "", ""},
        {"fddf", "", "", "", "", "", "", ""},
    };

    // ---- Don't modify the code below ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
