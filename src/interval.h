/*
 * Interval Arithmetic — class interface
 * Provides a numerical interval type and arithmetic operators.
 */

#ifndef INTERVAL_H
#define INTERVAL_H

#include <iosfwd>   // forward declarations for streams

class interval {
private:
    // Private interval endpoints
    double min;
    double max;

    // Ensure class invariant min <= max
    void normalise() noexcept;

public:
    // --- Constructors / Rule of 3 ---
    interval() noexcept;                         // default -> [0,0]
    explicit interval(double v) noexcept;         // single-value -> [v,v]
    interval(double vmin, double vmax) noexcept;  // two-value -> normalised
    interval(const interval& other) noexcept;     // copy
    interval& operator=(const interval& other) noexcept;
    ~interval() noexcept;

    // --- Read access (required: values can be read by all) ---
    double lower() const noexcept;
    double upper() const noexcept;

    // --- Core interval arithmetic (interval op interval) ---
    interval operator+(const interval& rhs) const noexcept;
    interval operator-(const interval& rhs) const noexcept;
    interval operator*(const interval& rhs) const noexcept;

    // Division may fail if rhs contains 0 -> throws std::domain_error
    interval operator/(const interval& rhs) const;

    // --- Compound assignment operators ---
    interval& operator+=(const interval& rhs) noexcept;
    interval& operator-=(const interval& rhs) noexcept;
    interval& operator*=(const interval& rhs) noexcept;
    interval& operator/=(const interval& rhs);

    // --- Mixing with scalars (interval op double) ---
    interval operator+(double rhs) const noexcept;
    interval operator-(double rhs) const noexcept;
    interval operator*(double rhs) const noexcept;
    interval operator/(double rhs) const;

    interval& operator+=(double rhs) noexcept;
    interval& operator-=(double rhs) noexcept;
    interval& operator*=(double rhs) noexcept;
    interval& operator/=(double rhs);

    // --- Friends (needed for stream ops and scalar on the left-hand side) ---
    friend interval operator+(double lhs, const interval& rhs) noexcept;
    friend interval operator-(double lhs, const interval& rhs) noexcept;
    friend interval operator*(double lhs, const interval& rhs) noexcept;
    friend interval operator/(double lhs, const interval& rhs);

    friend std::ostream& operator<<(std::ostream& os, const interval& x);
    friend std::istream& operator>>(std::istream& is, interval& x);
};

#endif // INTERVAL_H
