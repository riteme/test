//
// Copyright 2016 riteme
//
// NOTE:
// std::complex<T> is another utility for this one
// See <complex>
//
// See test_Vector.cpp for details
// Also the docstrings in this file
//

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cmath>

//////////////////////
// Float comparison //
//////////////////////

#ifndef EPSILON

/**
 * Specified float comparison missing
 */
#define EPSILON 0.000001

#endif  // IFNDEF EPSILON

/**
 * Determine whether two floats are the same
 * @param  a First one
 * @param  b Second one
 * @return   true for equality, false otherwise
 */
template <typename TFloat>
inline bool almost_equal(const TFloat &a, const TFloat &b) {
    return fabs(a - b) < EPSILON;
}

////////////
// Vector //
////////////

#ifndef VECTOR_FLOAT

/**
 * Specified float type for vector
 */
#define VECTOR_FLOAT double

#endif  // IFNDEF VECTOR_FLOAT

template <typename TFloat>
struct VectorBase {
    typedef TFloat FloatType;

    VectorBase() : x(0.0), y(0.0) {}
    VectorBase(const TFloat &_x, const TFloat &_y) : x(_x), y(_y) {}
    VectorBase(const VectorBase &lhs) : x(lhs.x), y(lhs.y) {}
    VectorBase(VectorBase &&rhs) : x(rhs.x), y(rhs.y) {}

    VectorBase &operator=(const VectorBase &lhs) {
        x = lhs.x;
        y = lhs.y;

        return *this;
    }

    VectorBase &operator=(VectorBase &&rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    /**
     * Determine another vector equals to this one
     */
    bool operator==(const VectorBase &lhs) const {
        return almost_equal(x, lhs.x) && almost_equal(y, lhs.y);
    }

    /**
     * Determine another vector does not equal to this one
     */
    bool operator!=(const VectorBase &lhs) const {
        return !((*this) == lhs);
    }

    /**
     * Sum two vectors up
     */
    VectorBase operator+(const VectorBase &b) const {
        return VectorBase(x + b.x, y + b.y);
    }

    /**
     * A subtract B
     */
    VectorBase operator-(const VectorBase &b) const {
        return VectorBase(x - b.x, y - b.y);
    }

    /**
     * Multiply with a constant value
     */
    VectorBase operator*(const TFloat &b) const {
        return VectorBase(x * b, y * b);
    }

    /**
     * Add a vertor to itself
     */
    VectorBase &operator+=(const VectorBase &lhs) {
        x += lhs.x;
        y += lhs.y;

        return *this;
    }

    /**
     * Subtract a vector to itself
     */
    VectorBase &operator-=(const VectorBase &lhs) {
        x -= lhs.x;
        y -= lhs.y;

        return *this;
    }

    /**
     * Multiply with a constant value
     */
    VectorBase &operator*=(const TFloat &lhs) {
        x *= lhs;
        y *= lhs;

        return *this;
    }

    TFloat x, y;
};  // struct Vector

/**
 * Vector dot multiply
 * @param  a First vector
 * @param  b Second vector
 * @return   a dot b
 */
template <typename TVector>
inline auto dot(const TVector &a, const TVector &b) ->
    typename TVector::FloatType {
    return a.x * b.x + a.y * b.y;
}

/**
 * Vector cross multiply
 * @param  a First vector
 * @param  b Second vector
 * @return   a cross b
 */
template <typename TVector>
inline auto cross(const TVector &a, const TVector &b) ->
    typename TVector::FloatType {
    return a.x * b.y - a.y * b.x;
}

/**
 * Compute the length of a vector
 * @param  a The vector
 * @return   The length of the vector
 */
template <typename TVector>
inline auto length(const TVector &a) -> typename TVector::FloatType {
    return sqrt(a.x * a.x + a.y * a.y);
}

/**
 * Compute the normalized form of a vector
 * @param  a The vector
 * @return   Keep the direction but the length turned to one
 */
template <typename TVector>
inline auto normalize(const TVector &a) -> TVector {
    return a * (1.0 / length(a));
}

//////////////
// Typedefs //
//////////////

typedef VectorBase<float> VectorF;
typedef VectorBase<double> VectorD;
typedef VectorBase<long double> VectorLD;
typedef VectorBase<VECTOR_FLOAT> Vector;

#endif
