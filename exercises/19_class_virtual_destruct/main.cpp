#include "../exercise.h"

struct A {
    static int num_a;

    A() {
        ++num_a;
    }

    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

int A::num_a = 0;

struct B final : public A {
    static int num_b;

    B() {
        ++num_b;
    }

    ~B() {
        --num_b;
    }

    char name() const override {
        return 'B';
    }
};

int B::num_b = 0;

int main(int argc, char **argv) {
    {
        auto a = new A;
        auto b = new B;
        ASSERT(A::num_a == 1, "A::num_a should be 1 after creating one A object");
        ASSERT(B::num_b == 1, "B::num_b should be 1 after creating one B object");
        ASSERT(a->name() == 'A', "a->name() should return 'A'");
        ASSERT(b->name() == 'B', "b->name() should return 'B'");

        delete a;
        delete b;
        ASSERT(A::num_a == 0, "A::num_a should be 0 after deleting the A object");
        ASSERT(B::num_b == 0, "B::num_b should be 0 after deleting the B object");
    }

    {
        A *ab = new B;
        ASSERT(A::num_a == 1, "A::num_a should be 1 after creating one B object via A*");
        ASSERT(B::num_b == 1, "B::num_b should be 1 after creating one B object via A*");
        ASSERT(ab->name() == 'B', "ab->name() should return 'B' when B is actually created");

        B &bb = dynamic_cast<B&>(*ab);
        ASSERT(bb.name() == 'B', "bb.name() should return 'B'");

        delete ab;
        ASSERT(A::num_a == 0, "A::num_a should be 0 after deleting the B object via A*");
        ASSERT(B::num_b == 0, "B::num_b should be 0 after deleting the B object via A*");
    }

    return 0;
}