#include <iostream>
#include <cassert>
using namespace std;

class A {
public:
    virtual char virtual_name() { return 'A'; }
    char direct_name() { return 'A'; }
};

class B : public A {
public:
    virtual char virtual_name() override { return 'B'; }
    char direct_name() { return 'B'; }
};

class C : public B {
public:
    virtual char virtual_name() final { return 'C'; }
    char direct_name() { return 'C'; }
};

class D : public C {
public:
    char direct_name() { return 'D'; }
};

int main() {
    A a;
    B b;
    C c;
    D d;

    // 1. 测试直接调用对象的虚函数和直接函数
    assert(a.virtual_name() == 'A');  // A 的虚函数返回 'A'
    assert(b.virtual_name() == 'B');  // B 的虚函数返回 'B'
    assert(c.virtual_name() == 'C');  // C 的虚函数返回 'C'
    assert(d.virtual_name() == 'C');  // D 由于 C 中的 virtual_name 是 final，返回 'C'

    assert(a.direct_name() == 'A');  // A 的直接函数返回 'A'
    assert(b.direct_name() == 'B');  // B 的直接函数返回 'B'
    assert(c.direct_name() == 'C');  // C 的直接函数返回 'C'
    assert(d.direct_name() == 'D');  // D 的直接函数返回 'D'

    // 2. 测试通过基类引用调用派生类对象的虚函数和直接函数
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    assert(rab.virtual_name() == 'B');  // rab 指向 B，调用 B 的虚函数返回 'B'
    assert(rbc.virtual_name() == 'C');  // rbc 指向 C，调用 C 的虚函数返回 'C'
    assert(rcd.virtual_name() == 'C');  // rcd 指向 D，调用 C 的虚函数返回 'C'

    assert(rab.direct_name() == 'B');  // rab 指向 B，调用 B 的直接函数返回 'B'
    assert(rbc.direct_name() == 'C');  // rbc 指向 C，调用 C 的直接函数返回 'C'
    assert(rcd.direct_name() == 'D');  // rcd 指向 D，调用 D 的直接函数返回 'D'

    // 3. 测试通过基类引用调用不同派生类对象的虚函数和直接函数
    A &rac = c;
    B &rbd = d;

    assert(rac.virtual_name() == 'C');  // rac 指向 C，调用 C 的虚函数返回 'C'
    assert(rbd.virtual_name() == 'C');  // rbd 指向 D，调用 C 的虚函数返回 'C'

    assert(rac.direct_name() == 'C');  // rac 指向 C，调用 C 的直接函数返回 'C'
    assert(rbd.direct_name() == 'D');  // rbd 指向 D，调用 D 的直接函数返回 'D'

    A &rad = d;

    assert(rad.virtual_name() == 'C');  // rad 指向 D，调用 C 的虚函数返回 'C'
    assert(rad.direct_name() == 'D');  // rad 指向 D，调用 D 的直接函数返回 'D'

    cout << "All assertions passed!" << endl;
    return 0;
}
