#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10); // shared 的引用计数 = 1
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // ptrs[0], ptrs[1], ptrs[2] 都指向 shared
    // 此时引用计数为 3（shared, ptrs[0], ptrs[1], ptrs[2]）
    
    std::weak_ptr<int> observer = shared;  // weak_ptr 观察 shared，引用计数不变，仍为 3
    ASSERT(observer.use_count() == 3, "use_count 应该是 3");

    ptrs[0].reset();  // ptrs[0] 不再指向 shared，引用计数变为 2
    ASSERT(observer.use_count() == 2, "use_count 应该是 2");

    ptrs[1] = nullptr;  // ptrs[1] 不再指向 shared，引用计数变为 1
    ASSERT(observer.use_count() == 1, "use_count 应该是 1");

    ptrs[2] = std::make_shared<int>(*shared);  // ptrs[2] 现在指向一个新的对象，引用计数仍然是 1
    ASSERT(observer.use_count() == 1, "use_count 应该是 1");

    ptrs[0] = shared;  // ptrs[0] 重新指向 shared，引用计数增加到 2
    ptrs[1] = shared;  // ptrs[1] 重新指向 shared，引用计数增加到 3
    ptrs[2] = std::move(shared);  // shared 被移动到 ptrs[2]，引用计数增加到 3（但原 shared 指针为空）
    ASSERT(observer.use_count() == 3, "use_count 应该是 3");

    std::ignore = std::move(ptrs[0]);  // ptrs[0] 通过 move 操作不再指向 shared，引用计数减为 2
    ptrs[1] = std::move(ptrs[1]);  // ptrs[1] 通过 move 操作不再指向 shared，引用计数减为 1
    ptrs[1] = std::move(ptrs[2]);  // ptrs[1] 现在指向 shared，引用计数增加为 2
    ASSERT(observer.use_count() == 2, "use_count 应该是 2");

    shared = observer.lock();  // 通过 observer.lock() 恢复 shared，并增加引用计数到 3
    ASSERT(observer.use_count() == 3, "use_count 应该是 3");

    shared = nullptr;  // shared 置空，引用计数减少到 2
    for (auto &ptr : ptrs) ptr = nullptr;  // ptrs 中的所有指针都置空，引用计数减少到 0
    ASSERT(observer.use_count() == 0, "use_count 应该是 0");

    shared = observer.lock();  // 再次通过 observer.lock() 尝试获取 shared，此时为 nullptr
    ASSERT(observer.use_count() == 0, "use_count 应该是 0");

    return 0;
}
