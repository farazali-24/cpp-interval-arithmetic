/*
 * Interval Arithmetic — class implementation
 */

#include "interval.h"

#include <algorithm>   // std::min, std::max
#include <cmath>       // std::isfinite
#include <iostream>    // streams
#include <limits>      // quiet_NaN
#include <stdexcept>   // std::domain_error

namespace {
    inline bool contains_zero(double a, double b) noexcept {
        // Interval contains 0 if endpoints are on different sides or one is 0.
        return (a <= 0.0 && b >= 0.0);
    }

    inline void set_fail(std::istream& is) {
        is.setstate(std::ios::failbit);
    }
}

void interval::normalise() noexcept {
    if (min > max) std::swap(min, max);
}

interval::interval() noexcept : min(0.0), max(0.0) {}

interval::interval(double v) noexcept : min(v), max(v) {}

interval::interval(double vmin, double vmax) noexcept : min(vmin), max(vmax) {
    normalise();
}

interval::interval(const interval& other) noexcept : min(other.min), max(other.max) {}

interval& interval::operator=(const interval& other) noexcept {
    if (this != &other) {
        min = other.min;
        max = other.max;
    }
    return *this;
}

interval::~interval() noexcept = default;

double interval::lower() const noexcept { return min; }
double interval::upper() const noexcept { return max; }

interval interval::operator+(const interval& rhs) const noexcept {
    // cmin = amin + bmin, cmax = amax + bmax
    return interval(min + rhs.min, max + rhs.max);
}

interval interval::operator-(const interval& rhs) const noexcept {
    // As given in the brief: cmin = amin - bmax, cmax = amax - bmin
    return interval(min - rhs.max, max - rhs.min);
}

interval interval::operator*(const interval& rhs) const noexcept {
    // Take min/max of the 4 endpoint products
    const double p1 = min * rhs.min;
    const double p2 = min * rhs.max;
    const double p3 = max * rhs.min;
    const double p4 = max * rhs.max;

    const double cmin = std::min(std::min(p1, p2), std::min(p3, p4));
    const double cmax = std::max(std::max(p1, p2), std::max(p3, p4));
    return interval(cmin, cmax);
}

interval interval::operator/(const interval& rhs) const {
    // Robustness: division by an interval that contains 0 is undefined.
    // We throw and let the caller decide how to report to the user.
    if (contains_zero(rhs.min, rhs.max)) {
        throw std::domain_error("interval division undefined: divisor interval contains 0");
    }

    // Multiply by reciprocal interval [1/rhs.max, 1/rhs.min] (then normalise)
    const double r1 = 1.0 / rhs.min;
    const double r2 = 1.0 / rhs.max;
    interval recip(r1, r2); // normalises internally
    return (*this) * recip;
}

interval& interval::operator+=(const interval& rhs) noexcept {
    *this = *this + rhs;
    return *this;
}

interval& interval::operator-=(const interval& rhs) noexcept {
    *this = *this - rhs;
    return *this;
}

interval& interval::operator*=(const interval& rhs) noexcept {
    *this = *this * rhs;
    return *this;
}

interval& interval::operator/=(const interval& rhs) {
    *this = *this / rhs;
    return *this;
}

// --- interval op scalar (right-hand scalar) ---
interval interval::operator+(double rhs) const noexcept {
    return interval(min + rhs, max + rhs);
}

interval interval::operator-(double rhs) const noexcept {
    return interval(min - rhs, max - rhs);
}

interval interval::operator*(double rhs) const noexcept {
    // If rhs is negative the endpoints flip; constructor normalises.
    return interval(min * rhs, max * rhs);
}

interval interval::operator/(double rhs) const {
    if (rhs == 0.0) {
        throw std::domain_error("interval division by scalar undefined: divisor is 0");
    }
    return interval(min / rhs, max / rhs); // normalises if rhs < 0
}

interval& interval::operator+=(double rhs) noexcept { return (*this += interval(rhs)); }
interval& interval::operator-=(double rhs) noexcept { return (*this -= interval(rhs)); }
interval& interval::operator*=(double rhs) noexcept { return (*this *= interval(rhs)); }
interval& interval::operator/=(double rhs)         { return (*this /= interval(rhs)); }

// --- scalar op interval (left-hand scalar) ---
interval operator+(double lhs, const interval& rhs) noexcept {
    return rhs + lhs;
}

interval operator-(double lhs, const interval& rhs) noexcept {
    // lhs - [a,b] = [lhs-b, lhs-a]
    return interval(lhs - rhs.max, lhs - rhs.min);
}

interval operator*(double lhs, const interval& rhs) noexcept {
    return rhs * lhs;
}

interval operator/(double lhs, const interval& rhs) {
    if (contains_zero(rhs.min, rhs.max)) {
        throw std::domain_error("scalar/interval division undefined: divisor interval contains 0");
    }
    // lhs / [a,b] = lhs * [1/b, 1/a]
    interval recip(1.0 / rhs.min, 1.0 / rhs.max);
    return interval(lhs) * recip;
}

// --- Stream output ---
// Format: [min, max]
std::ostream& operator<<(std::ostream& os, const interval& x) {
    os << '[' << x.min << ", " << x.max << ']';
    return os;
}

// --- Stream input ---
// Accepts any of these forms (spaces optional):
//  1) [min,max] or {min,max} or (min,max)
//  2) min max
//  3) min, max
// On failure sets failbit.
std::istream& operator>>(std::istream& is, interval& x) {
    // Consume leading whitespace
    is >> std::ws;
    if (!is) return is;

    int c = is.peek();
    bool bracketed = false;
    char open = '\0';
    char close = '\0';

    if (c == '[' || c == '{' || c == '(') {
        bracketed = true;
        is.get(open);
        close = (open == '[') ? ']' : (open == '{' ? '}' : ')');
        is >> std::ws;
    }

    double a = 0.0, b = 0.0;
    if (!(is >> a)) {
        set_fail(is);
        return is;
    }

    is >> std::ws;

    // Optional comma between values
    if (is.peek() == ',') {
        is.get();
        is >> std::ws;
    }

    if (!(is >> b)) {
        set_fail(is);
        return is;
    }

    is >> std::ws;

    if (bracketed) {
        if (is.peek() != close) {
            set_fail(is);
            return is;
        }
        is.get(); // consume closing bracket
    }

    // Assign (private members changed via friend)
    x.min = a;
    x.max = b;
    x.normalise();
    return is;
}
