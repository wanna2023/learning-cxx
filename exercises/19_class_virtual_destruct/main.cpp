#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态字段需要在类外初始化
    static int num_a;

    A() {
        ++num_a;
    }
    virtual ~A() { // 虚析构函数，确保多态删除
        --num_a;
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
        ++num_b;
    }
    ~B() {
        --num_b;
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
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B; // 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // 基类指针不能随意转换为派生类指针，因此我们用 dynamic_cast
    B &bb = dynamic_cast<B&>(*ab); // 使用 dynamic_cast 安全转换
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // 删除通过基类指针指向的派生类对象，确保调用了虚析构函数
    delete ab; 
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
