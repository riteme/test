#include <cassert>
#include <typeinfo>

#include "Vector.hpp"

int main() {
    assert(almost_equal(5.0, 5.00000));
    assert(!almost_equal(233.0, 233.0 + 2 * EPSILON));
    assert(!almost_equal(233.0 + 2 * EPSILON, 233.0));

    Vector a(1.0, 2.0);
    Vector b = Vector(1.0, 2.0);
    Vector c = { 1.0, 2.0 };
    Vector d{ 2.0, 3.0 };
    VectorBase<double> e{ 1.233, 2.233 };

    assert(typeid(d) == typeid(e));
    assert(a == b);
    assert(a != e);

    assert(a + Vector(1.0, 1.0) == Vector(2.0, 3.0));
    assert(a - Vector(1.0, 1.0) == Vector(0.0, 1.0));
    assert(a * 2.0 == Vector(2.0, 4.0));

    a += Vector(1.0, 1.0);
    assert(a == Vector(2.0, 3.0));
    a -= Vector(1.0, 1.0);
    assert(a == Vector(1.0, 2.0));
    a *= 2.0;
    assert(a == Vector(2.0, 4.0));

    assert(almost_equal(dot(c, b), 5.0));
    assert(almost_equal(cross(c, b), 0.0));
    assert(almost_equal(length(Vector(3.0, 4.0)), 5.0));
    assert(normalize(Vector(3.0, 3.0)) == normalize(Vector(1.0, 1.0)));

    return 0;
}  // function main
