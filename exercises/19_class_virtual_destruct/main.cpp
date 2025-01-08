#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态成员变量需要在类外进行初始化
    static int num_a;

    A() {
        ++num_a;
    }
    virtual ~A() {  // 添加虚析构函数以支持多态删除
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 静态成员变量需要在类外进行初始化
int A::num_a = 0;

struct B final : public A {
    // 静态成员变量需要在类外进行初始化
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

// 静态成员变量需要在类外进行初始化
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;

    // 初始状态下静态变量 num_a 和 num_b
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;

    // 删除后静态变量 num_a 和 num_b 应该回到 0
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;  // 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // 基类指针不能直接转换为派生类引用，需要显式转换
    B &bb = dynamic_cast<B&>(*ab);  // 使用 dynamic_cast 进行安全转换
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    delete ab;  // 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
