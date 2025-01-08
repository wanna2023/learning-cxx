#include "../exercise.h"

struct A {
    // Correctly initialize the static field outside the class
    static int num_a;

    A() {
        ++num_a;
    }

    virtual ~A() {  // Virtual destructor to ensure correct polymorphic behavior
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

// Define static field outside the class
int A::num_a = 0;

struct B final : public A {
    // Correctly initialize the static field outside the class
    static int num_b;

    B() {
        ++num_b;
    }

    ~B() {
        --num_b;
    }

    char name() const final override {
        return 'B';
    }
};

// Define static field outside the class
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "A::num_a should be 2 after creating one A and one B object");
    ASSERT(B::num_b == 1, "B::num_b should be 1 after creating one B object");
    ASSERT(a->name() == 'A', "a->name() should return 'A'");
    ASSERT(b->name() == 'B', "b->name() should return 'B'");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;  // Base class pointer can point to derived class
    ASSERT(A::num_a == 1, "A::num_a should be 1 after creating a B object via A*");
    ASSERT(B::num_b == 1, "B::num_b should be 1 after creating a B object via A*");
    ASSERT(ab->name() == 'B', "ab->name() should return 'B'");

    // Dynamic cast to ensure we can safely convert A* to B& if the object is actually of type B
    B &bb = dynamic_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "bb.name() should return 'B'");

    delete ab;  // Deleting via base class pointer should call the correct destructor
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
