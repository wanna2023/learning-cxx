#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 直接在类内初始化静态字段
    static int num_a;

    A() {
        ++num_a;
    }

    virtual ~A() {  // 虚析构函数确保删除时会调用正确的析构函数
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// 静态成员初始化
int A::num_a = 0;

struct B final : public A {
    // 直接在类内初始化静态字段
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

// 静态成员初始化
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;

    // 通过构造函数，A::num_a 应该为 2（一次在 A 构造，一次在 B 构造），B::num_b 应该为 1
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;  // 删除 A 对象，num_a 应该减 1
    delete b;  // 删除 B 对象，num_b 应该减 1
    ASSERT(A::num_a == 1, "Every A was destroyed");  // 这里的断言是检查 A::num_a 是否为 1
    ASSERT(B::num_b == 0, "Every B was destroyed");  // 这里的断言是检查 B::num_b 是否为 0

    A *ab = new B;  // 基类指针指向派生类对象
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");  // A::num_a 应该为 2
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");  // B::num_b 应该为 1
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");  // 多态，应该调用 B::name()

    delete ab;  // 删除 B 对象，A::num_a 和 B::num_b 应该各减 1
    ASSERT(A::num_a == 1, "Every A was destroyed");  // A::num_a 应该是 1
    ASSERT(B::num_b == 0, "Every B was destroyed");  // B::num_b 应该是 0

    return 0;
}
