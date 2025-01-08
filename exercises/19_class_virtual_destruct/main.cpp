#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态字段需要在类外初始化
    static int num_a;

    A() {
        ++num_a;  // 创建 A 类对象时，num_a 加 1
    }
    virtual ~A() { // 虚析构函数，确保多态删除
        --num_a;  // 销毁 A 类对象时，num_a 减 1
    }

    virtual char name() const {
        return 'A';
    }
};

// 静态字段的初始化
int A::num_a = 0;

struct B final : public A {
    // 静态字段需要在类外初始化
    static int num_b;

    B() {
        ++num_b;  // 创建 B 类对象时，num_b 加 1
    }
    ~B() {
        --num_b;  // 销毁 B 类对象时，num_b 减 1
    }

    char name() const final {
        return 'B';
    }
};

// 静态字段的初始化
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A; // 创建 A 类对象
    auto b = new B; // 创建 B 类对象
    ASSERT(A::num_a == 1, "A::num_a 应该是 1"); // A::num_a 应该是 1
    ASSERT(B::num_b == 1, "B::num_b 应该是 1"); // B::num_b 应该是 1
    ASSERT(a->name() == 'A', "a->name() 应该是 'A'"); // a 的名字应该是 'A'
    ASSERT(b->name() == 'B', "b->name() 应该是 'B'"); // b 的名字应该是 'B'

    delete a; // 删除 A 类对象
    delete b; // 删除 B 类对象
    ASSERT(A::num_a == 0, "所有 A 类对象都已销毁"); // A::num_a 应该是 0
    ASSERT(B::num_b == 0, "所有 B 类对象都已销毁"); // B::num_b 应该是 0

    A *ab = new B; // 创建 B 类对象，但通过 A 类指针访问
    ASSERT(A::num_a == 1, "A::num_a 应该是 1"); // A::num_a 应该是 1
    ASSERT(B::num_b == 1, "B::num_b 应该是 1"); // B::num_b 应该是 1
    ASSERT(ab->name() == 'B', "ab->name() 应该是 'B'"); // ab 的名字应该是 'B'

    // 基类指针不能随意转换为派生类指针，因此我们用 dynamic_cast
    B &bb = dynamic_cast<B&>(*ab); // 使用 dynamic_cast 安全转换
    ASSERT(bb.name() == 'B', "bb->name() 应该是 'B'"); // bb 的名字应该是 'B'

    // 删除通过基类指针指向的派生类对象，确保调用了虚析构函数
    delete ab; // 删除通过 A 类指针指向的 B 类对象
    ASSERT(A::num_a == 0, "所有 A 类对象都已销毁"); // A::num_a 应该是 0
    ASSERT(B::num_b == 0, "所有 B 类对象都已销毁"); // B::num_b 应该是 0

    return 0;
}
