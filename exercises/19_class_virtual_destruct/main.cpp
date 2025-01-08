#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态字段需要在类外初始化
    static int num_a;

    A() {
        ++num_a;  // 创建 A 类对象时，num_a 加 1
    }
    virtual ~A() {
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
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 1, "A::num_a 应该是 1");
    ASSERT(B::num_b == 1, "B::num_b 应该是 1");
    ASSERT(a->name() == 'A', "a->name() 应该是 'A'");
    ASSERT(b->name() == 'B', "b->name() 应该是 'B'");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "每个 A 类对象已经销毁");
    ASSERT(B::num_b == 0, "每个 B 类对象已经销毁");

    A *ab = new B; // 创建 B 类对象，但通过 A 类指针访问
    ASSERT(A::num_a == 1, "A::num_a 应该是 1");
    ASSERT(B::num_b == 1, "B::num_b 应该是 1");
    ASSERT(ab->name() == 'B', "ab->name() 应该是 'B'");

    // 使用 dynamic_cast 安全地将 A 类型指针转换为 B 类型引用
    B &bb = dynamic_cast<B&>(*ab); // 通过引用转换
    ASSERT(bb.name() == 'B', "bb->name() 应该是 'B'");

    delete ab; // 删除通过 A 类指针指向的 B 类对象
    ASSERT(A::num_a == 0, "每个 A 类对象已经销毁");
    ASSERT(B::num_b == 0, "每个 B 类对象已经销毁");

    return 0;
}
