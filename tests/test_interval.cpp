
#include "../src/interval.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

static int passed = 0;
static int failed = 0;

void check(bool condition, const char* name) {
    if (condition) {
        std::cout << "PASS: " << name << '\n';
        ++passed;
    } else {
        std::cout << "FAIL: " << name << '\n';
        ++failed;
    }
}

bool approx(double actual, double expected) {
    return std::fabs(actual - expected) < 1e-10;
}

bool bounds(const interval& value, double lower, double upper) {
    return approx(value.lower(), lower) && approx(value.upper(), upper);
}

int main() {
    check(bounds(interval(), 0, 0), "Default constructor");
    check(bounds(interval(4), 4, 4), "Single-value constructor");
    check(bounds(interval(9, -2), -2, 9), "Reversed bounds normalised");

    const interval a(2, 5);
    const interval b(3, 7);

    check(bounds(a + b, 5, 12), "Interval addition");
    check(bounds(a - b, -5, 2), "Interval subtraction");
    check(bounds(a * b, 6, 35), "Interval multiplication");
    check(bounds(a / interval(2, 4), 0.5, 2.5), "Interval division");
    check(bounds(a * interval(-2, -1), -10, -2), "Negative scalar bounds");
    check(bounds(a + 5.0, 7, 10), "Interval plus scalar");
    check(bounds(5.0 - a, 0, 3), "Scalar minus interval");

    interval changed(2, 5);
    changed += interval(1, 2);
    check(bounds(changed, 3, 7), "Compound addition");

    bool threw = false;
    try {
        (void)(a / interval(-1, 1));
    } catch (const std::domain_error&) {
        threw = true;
    }
    check(threw, "Division by interval containing zero rejected");

    std::istringstream input("[3, 1]");
    interval parsed;
    input >> parsed;
    check(!input.fail() && bounds(parsed, 1, 3), "Bracketed input parsing");

    std::ostringstream output;
    output << interval(1, 3);
    check(output.str() == "[1, 3]", "Stream output formatting");

    std::cout << "\n" << passed << " passed, "
              << failed << " failed.\n";

    return failed == 0 ? 0 : 1;
}
