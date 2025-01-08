#include <iostream>
#include <memory>
#include <cassert>

int main() {
    // 创建一个 shared_ptr，指向整数 10
    auto shared = std::make_shared<int>(10);

    // 创建一个包含三个 shared_ptr 的数组，全部指向同一个对象
    std::shared_ptr<int> ptrs[]{shared, shared, shared};
    
    // 创建一个 weak_ptr，它观察 shared 所指向的对象
    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 3, "use_count should be 3");

    // 重置 ptrs[0]，减少引用计数
    ptrs[0].reset();
    ASSERT(observer.use_count() == 2, "use_count should be 2");

    // 重置 ptrs[1]，减少引用计数
    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 1, "use_count should be 1");

    // ptrs[2] 现在指向一个新的 shared_ptr，指向一个相同值的对象
    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "use_count should still be 1");

    // 重新给 ptrs[0] 和 ptrs[1] 赋值为 shared
    ptrs[0] = shared;
    ptrs[1] = shared;

    // 将 shared 转移到 ptrs[2]，并设置 ptrs[2] 为 nullptr
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, "use_count should be 3");

    // 使用 move 操作重置 ptrs 中的元素
    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 3, "use_count should still be 3");

    // 通过 weak_ptr 重新获得 shared_ptr，引用计数增加
    shared = observer.lock();
    ASSERT(observer.use_count() == 4, "use_count should be 4");

    // 将 shared 和 ptrs 中的元素全部重置
    shared = nullptr;
    for (auto &ptr : ptrs) {
        ptr = nullptr;
    }
    ASSERT(observer.use_count() == 1, "use_count should be 1");

    // 再次通过 observer.lock() 获得 shared_ptr，引用计数增加
    shared = observer.lock();
    ASSERT(observer.use_count() == 2, "use_count should be 2");

    return 0;
}
