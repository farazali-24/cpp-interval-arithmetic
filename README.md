
# C++ Interval Arithmetic

## Project Overview

This project implements an interval arithmetic library in C++14 for performing mathematical operations on numerical ranges rather than individual values.

The program uses a custom `interval` class to represent lower and upper bounds, supporting arithmetic operations, operator overloading, input/output handling and exception management.

A demonstration program and separate automated test suite are included to verify the functionality of the implementation.

## Features

- Interval creation using default, single-value and two-value constructors
- Automatic normalisation of interval bounds
- Addition, subtraction, multiplication and division
- Arithmetic between intervals and scalar values
- Operator overloading for standard arithmetic operations
- Compound assignment operators (`+=`, `-=`, `*=`, `/=`)
- Custom stream input and output operators
- Exception handling for division by zero
- Support for multiple interval input formats
- Automated tests for arithmetic operations and boundary conditions

## Project Structure

```text
cpp-interval-arithmetic/
├── src/
│   ├── main.cpp
│   ├── interval.cpp
│   └── interval.h
├── tests/
│   └── test_interval.cpp
├── README.md
├── .gitignore
└── LICENSE
```

The `src/` directory contains the interval arithmetic implementation and demonstration program.

The `tests/` directory contains automated checks for mathematical operations, constructors, input/output and exception handling.

## How It Works

### 1. Interval Representation

The `interval` class represents a numerical range using two private variables:

- `min` — lower bound
- `max` — upper bound

The class automatically normalises bounds if they are provided in reverse order.

For example:

```cpp
interval a(2.0, 5.0);
interval b(10.0, -2.0);
```

The second interval is automatically normalised to `[-2, 10]`.

### 2. Arithmetic Operations

The class implements four standard arithmetic operations.

**Addition**

```text
[2, 5] + [3, 7] = [5, 12]
```

**Subtraction**

```text
[2, 5] - [3, 7] = [-5, 2]
```

**Multiplication**

```text
[2, 5] * [3, 7] = [6, 35]
```

**Division**

```text
[2, 5] / [2, 4] = [0.5, 2.5]
```

Division by an interval containing zero raises a `std::domain_error` exception.

### 3. Operator Overloading

Operator overloading allows intervals to be manipulated using familiar mathematical syntax.

```cpp
interval a(2.0, 5.0);
interval b(3.0, 7.0);

interval sum = a + b;
interval difference = a - b;
interval product = a * b;
interval quotient = a / b;
```

The class also supports arithmetic with scalar values.

```cpp
interval result = a + 5.0;
interval another = 5.0 + a;
```

### 4. Input and Output

Custom stream operators support different interval input formats:

```text
[1.2, 3.4]
{1.2, 3.4}
(1.2, 3.4)
1.2 3.4
```

Output is displayed in the format:

```text
[lower, upper]
```

## Building and Running

The project uses C++14 and can be compiled using a compatible C++ compiler.

### Compile

From the repository root:

```bash
g++ -std=c++14 src/main.cpp src/interval.cpp -o interval_arithmetic
```

### Run

On Linux or macOS:

```bash
./interval_arithmetic
```

On Windows:

```powershell
.\interval_arithmetic.exe
```

The program demonstrates interval construction, arithmetic operations, operator overloading, exception handling and interactive input.

## Testing

The project includes a separate automated test suite containing 14 checks.

### Running the Tests

Compile the test program from the repository root:

```bash
g++ -std=c++14 tests/test_interval.cpp src/interval.cpp -o test_interval
```

Run on Windows:

```powershell
.\test_interval.exe
```

Run on Linux or macOS:

```bash
./test_interval
```

### Test Coverage

The automated tests cover:

1. Default and single-value constructors
2. Automatic interval bound normalisation
3. Addition, subtraction, multiplication and division
4. Arithmetic involving negative values
5. Arithmetic between intervals and scalars
6. Compound assignment operators
7. Division-by-zero exception handling
8. Bracketed interval input parsing
9. Stream output formatting

### Expected Test Output

When all tests pass, the program displays:

```text
14 passed, 0 failed.
```

Each test prints `PASS` or `FAIL` along with its description.

The test executable returns a non-zero exit code if any check fails.

## Limitations

- The implementation uses standard double-precision floating-point arithmetic.
- Outward rounding is not implemented, so mathematically rigorous interval enclosure is not guaranteed.
- Operations involving non-finite values are not comprehensively validated.
- The automated tests cover selected operations and edge cases but do not provide exhaustive verification.

## Skills Demonstrated

- Object-oriented programming in C++
- Class design and encapsulation
- Constructors, destructors and copy semantics
- Operator overloading
- Numerical programming and interval arithmetic
- Exception handling
- Stream input/output operations
- Modular software development
- Automated software testing and debugging
