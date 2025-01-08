#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);  // 创建一个 shared_ptr, 引用计数 = 1
    std::shared_ptr<int> ptrs[]{shared, shared, shared};  // ptrs[0], ptrs[1], ptrs[2] 都指向 shared

    std::weak_ptr<int> observer = shared;  // 创建一个 weak_ptr 观察 shared
    ASSERT(observer.use_count() == 3, "");  // 第一个 ASSERT

    ptrs[0].reset();  // ptrs[0] 释放资源，shared 仍然有 2 个引用（ptrs[1], ptrs[2]）
    ASSERT(observer.use_count() == 2, "");  // 第二个 ASSERT

    ptrs[1] = nullptr;  // ptrs[1] 变为 nullptr，剩下 1 个引用（ptrs[2]）
    ASSERT(observer.use_count() == 1, "");  // 第三个 ASSERT

    ptrs[2] = std::make_shared<int>(*shared);  // ptrs[2] 指向一个新分配的内存，shared 仍然有 1 个引用
    ASSERT(observer.use_count() == 1, "");  // 第四个 ASSERT

    ptrs[0] = shared;  // ptrs[0] 重新指向 shared，引用计数变为 2
    ptrs[1] = shared;  // ptrs[1] 也指向 shared，引用计数变为 3
    ptrs[2] = std::move(shared);  // shared 被转移给 ptrs[2]，引用计数变为 2（ptrs[0], ptrs[1]）
    ASSERT(observer.use_count() == 2, "");  // 第五个 ASSERT

    std::ignore = std::move(ptrs[0]);  // ptrs[0] 被移动，引用计数不变，仍然是 2
    ptrs[1] = std::move(ptrs[1]);  // ptrs[1] 被移动，引用计数不变，仍然是 2
    ptrs[1] = std::move(ptrs[2]);  // ptrs[2] 被转移给 ptrs[1]，引用计数不变，仍然是 2
    ASSERT(observer.use_count() == 2, "");  // 第六个 ASSERT

    shared = observer.lock();  // 通过 weak_ptr 转换为 shared_ptr，引用计数变为 3
    ASSERT(observer.use_count() == 3, "");  // 第七个 ASSERT

    shared = nullptr;  // shared 被设为 nullptr，引用计数变为 2（ptrs[0], ptrs[1]）
    for (auto &ptr : ptrs) ptr = nullptr;  // ptrs 中的指针都被置为 nullptr，引用计数变为 0
    ASSERT(observer.use_count() == 0, "");  // 第八个 ASSERT

    shared = observer.lock();  // 重新通过 weak_ptr 获取 shared_ptr，引用计数变为 1
    ASSERT(observer.use_count() == 1, "");  // 第九个 ASSERT

    return 0;
}
