#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    // `observer` 观察 `shared`，初始引用计数为 3
    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 3, "Initial reference count should be 3");

    ptrs[0].reset();  // `ptrs[0]` 变为 nullptr，引用计数减少为 2
    ASSERT(observer.use_count() == 2, "After reset ptrs[0], use_count should be 2");

    ptrs[1] = nullptr;  // `ptrs[1]` 变为 nullptr，引用计数减少为 1
    ASSERT(observer.use_count() == 1, "After null ptrs[1], use_count should be 1");

    ptrs[2] = std::make_shared<int>(*shared);  // `ptrs[2]` 被重置为新的 `shared_ptr`，引用计数仍然为 1
    ASSERT(observer.use_count() == 1, "After creating new shared_ptr in ptrs[2], use_count should be 1");

    // 将 `ptrs[0]` 和 `ptrs[1]` 重新指向 `shared`，并且 `ptrs[2]` 通过 std::move 迁移所有权
    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);  // 现在 `shared` 被移动到 `ptrs[2]`，引用计数仍然为 3
    ASSERT(observer.use_count() == 3, "After moving shared to ptrs[2], use_count should be 3");

    // 移动 `ptrs[0]` 和 `ptrs[1]`，但是它们都不再持有原对象
    std::ignore = std::move(ptrs[0]);  // 移动操作不会影响 `ptrs[0]`
    ptrs[1] = std::move(ptrs[1]);      // 移动操作不会影响 `ptrs[1]`
    ptrs[1] = std::move(ptrs[2]);      // `ptrs[1]` 接管了 `ptrs[2]` 所有权，引用计数应为 1
    ASSERT(observer.use_count() == 1, "After moving all ptrs, use_count should be 1");

    // `observer.lock()` 应该返回一个有效的 `shared_ptr`
    shared = observer.lock();  // 返回一个有效的 `shared_ptr`，引用计数增加到 2
    ASSERT(observer.use_count() == 2, "After locking observer, use_count should be 2");

    // 重置所有指针，引用计数应降为 0
    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;  // 所有 `shared_ptr` 变为 nullptr
    ASSERT(observer.use_count() == 0, "After resetting all pointers, use_count should be 0");

    // 此时 `observer.lock()` 返回一个空指针
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "After locking observer when object is no longer available, use_count should be 0");

    return 0;
}
