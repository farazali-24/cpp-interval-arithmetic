
# C++ Interval Arithmetic

## Project Overview

This project implements an interval arithmetic library in C++14 for performing mathematical operations on numerical ranges rather than individual values.

The program uses a custom `interval` class to represent lower and upper bounds, supporting arithmetic operations, operator overloading, input/output handling and exception management.

A demonstration program is included to test the functionality of the class using different interval values and input conditions.

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
- Demonstration of arithmetic operations and edge cases

## Project Structure

```text
cpp-interval-arithmetic/
├── src/
│   ├── main.cpp
│   ├── interval.cpp
│   └── interval.h
├── README.md
├── .gitignore
└── LICENSE
```

## How It Works

### 1. Interval Representation

The `interval` class represents a range of numerical values using two private variables:

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

The class implements the four standard arithmetic operations.

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

Operator overloading allows intervals to be used with familiar mathematical syntax.

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

The program supports several input formats:

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

The program executes a series of demonstrations before allowing the user to enter an interval interactively.

## Testing

The demonstration program covers:

1. Default, single-value, two-value and copy constructors
2. Copy assignment and dynamic array creation
3. Interval bound normalisation
4. Arithmetic operations
5. Compound assignment operators
6. Arithmetic with scalar values
7. Stream input and output
8. Division-by-zero exception handling
9. Invalid input handling

These examples demonstrate the main functionality and boundary conditions of the implementation.

## Limitations

- The implementation uses standard double-precision floating-point arithmetic.
- Outward rounding is not implemented, so mathematically rigorous interval enclosure is not guaranteed.
- Operations involving non-finite values are not comprehensively validated.
- The demonstration program illustrates behaviour but is not a comprehensive automated unit-test suite.

## Skills Demonstrated

- Object-oriented programming in C++
- Class design and encapsulation
- Constructors, destructors and copy semantics
- Operator overloading
- Numerical programming
- Exception handling
- Stream input/output operations
- Modular software development
- Software testing and debugging
