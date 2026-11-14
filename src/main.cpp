/*
 * Interval Arithmetic — demonstration and testing program
 * Build with a C++14-compatible compiler.
 */

#include "interval.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

static void banner(const std::string& title) {
    std::cout << "\n==== " << title << " ====\n";
}

static void show(const char* label, const interval& x) {
    std::cout << label << " = " << x << "  (lower=" << x.lower() << ", upper=" << x.upper() << ")\n";
}

int main() {
    try {
        banner("Baseline requirements: constructors, copy, assignment, new[]/delete[]");

        interval x;                 // standard initialisation
        interval y(3.0, 3.1);        // two-value constructor
        interval z(7.0);             // single-value constructor
        interval a(x);               // copy constructor
        a = y;                       // assignment operator

        // Dynamic array creation/deletion must be safe
        interval* intptr = new interval[4];
        delete[] intptr;

        show("x", x);
        show("y", y);
        show("z", z);
        show("a", a);

        banner("Normalisation / robustness for input ordering (min > max)");
        interval swapped(10.0, -2.0);   // should auto-normalise to [-2,10]
        show("swapped", swapped);

        banner("Interval arithmetic: +, -, *, / (interval with interval)");
        interval sum = y + z;
        interval diff = y - z;
        interval prod = y * z;
        interval quot = y / z;

        show("y + z", sum);
        show("y - z", diff);
        show("y * z", prod);
        show("y / z", quot);

        banner("Compound assignment operators (+=, -=, *=, /=)");
        interval p(x);
        p += y;
        show("p += y", p);
        p -= interval(1.0, 2.0);
        show("p -= [1,2]", p);
        p *= interval(-1.0, 0.5);
        show("p *= [-1,0.5]", p);
        p /= interval(2.0, 4.0);
        show("p /= [2,4]", p);

        banner("Mixing with scalars: interval + float and float + interval");
        double f = 5.0;
        interval g = y + f;   // interval + float
        interval h = f + y;   // float + interval (requires non-member overload)

        show("y + 5", g);
        show("5 + y", h);

        banner("Stream I/O: operator<< and operator>>");
        std::cout << "Printing interval y: " << y << "\n";

        // Demonstrate parsing multiple supported formats
        {
            std::istringstream iss1("[ -3.5,  2.25 ]");
            interval t1;
            iss1 >> t1;
            show("Parsed from \"[ -3.5,  2.25 ]\"", t1);
        }
        {
            std::istringstream iss2("10  12");
            interval t2;
            iss2 >> t2;
            show("Parsed from \"10 12\"", t2);
        }
        {
            std::istringstream iss3("{9, -1}");
            interval t3;
            iss3 >> t3; // should normalise to [-1,9]
            show("Parsed from \"{9,-1}\"", t3);
        }

        banner("Failure mode: division by an interval containing 0 (should be handled)");
        interval nearZero(-1.0, 1.0);
        show("nearZero", nearZero);

        try {
            interval bad = y / nearZero;
            show("y / nearZero", bad); // should not reach
        } catch (const std::domain_error& e) {
            std::cout << "Handled error safely: " << e.what() << "\n";
            std::cout << "User guidance: choose a divisor interval that does NOT include 0.\n";
        }

        banner("Interactive input (optional)");
        std::cout << "Enter an interval as [min,max] or \"min max\" (e.g., [1.2, 3.4]): ";
        interval user;
        if (std::cin >> user) {
            std::cout << "You entered: " << user << "\n";
            std::cout << "Example: user + 1 = " << (user + 1.0) << "\n";
        } else {
            std::cout << "Input was not recognised (stream failbit set).\n";
        }

        banner("Done");
        return 0;

    } catch (const std::exception& e) {
        // Any unexpected error should still terminate gracefully.
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}
