#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    
    // 初始时 shared_ptr 计数为 3，因为 ptrs[0], ptrs[1], ptrs[2] 都持有 shared 的引用
    ASSERT(observer.use_count() == 3, "Initial use count of observer should be 3");

    ptrs[0].reset();  // ptrs[0] 不再持有 shared，引用计数减少到 2
    ASSERT(observer.use_count() == 2, "After resetting ptrs[0], use count should be 2");

    ptrs[1] = nullptr;  // ptrs[1] 也不再持有 shared，引用计数减少到 1
    ASSERT(observer.use_count() == 1, "After setting ptrs[1] to nullptr, use count should be 1");

    ptrs[2] = std::make_shared<int>(*shared);  // ptrs[2] 现在持有一个新的 shared_ptr 对象，不影响原来的 shared
    ASSERT(observer.use_count() == 2, "After assigning a new shared_ptr to ptrs[2], use count should be 2");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);  // std::move 转移所有权，shared_ptr 移动，引用计数恢复到 3
    ASSERT(observer.use_count() == 3, "After resetting ptrs with shared pointers, use count should be 3");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 3, "After moving ptrs, use count should remain 3");

    shared = observer.lock();  // 锁住 observer，返回 shared_ptr，引用计数不变
    ASSERT(observer.use_count() == 3, "After locking the observer, use count should remain 3");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;  // 重置所有 shared_ptr，引用计数变为 0
    ASSERT(observer.use_count() == 0, "After resetting all pointers, use count should be 0");

    shared = observer.lock();  // 再次尝试锁住，shared_ptr 为 nullptr
    ASSERT(observer.use_count() == 0, "After locking the observer after resetting, use count should still be 0");

    return 0;
}
