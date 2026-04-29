# 7. Implementation

[← Previous: Applications](06_applications.md) | [Back to Contents](../README.md) | [Next: Conclusion →](08_conclusion.md)

---

A C++ reference implementation accompanies the theoretical framework, demonstrating computational viability.

## 7.1 Overview

The implementation resides in the [`test/`](../test/) directory and provides:

- **Core data structure.** A class `IntervalNumber` ([`test/src/IntervalNumber.hpp`](../test/src/IntervalNumber.hpp)) using `double` for endpoint storage, with normalization to ensure $x_0 \le x_1$ and propagation of `NaN` semantics.
- **Arithmetic operations.** All operations defined in [Section 4](04_operations.md) with explicit handling of extended-real limits, including the indeterminate forms $0 \cdot \infty$, $\infty - \infty$, and related cases.
- **Unit tests.** A comprehensive test suite ([`test/src/main.cpp`](../test/src/main.cpp)) employing the Google Test framework, validating mathematical properties, edge cases, and the behavior of native IEEE-754 floating-point limits used as a baseline.

## 7.2 Build Instructions

The project uses CMake (version 3.14 or higher).

```bash
cd test
mkdir build && cd build
cmake ..
cmake --build .
```

Google Test is fetched automatically via CMake's `FetchContent` module; no manual installation is required.

## 7.3 Running the Tests

```bash
# Debug build (default)
./Debug/interval_test.exe

# Release build
cmake --build . --config Release
./Release/interval_test.exe
```

On non-Windows platforms, the executable is produced without the `.exe` suffix.

## 7.4 Verification: Mapping Mathematical Claims to Tests

The 77 unit tests in [`test/src/main.cpp`](../test/src/main.cpp) provide computational evidence for each formal claim of the framework. Selected correspondences:

| Claim | Reference | Test name(s) |
|-------|-----------|--------------|
| Rule I: $0 \cdot \infty = [0, \infty]_{in}$ | [§3.4](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) | `RuleI_ZeroTimesInfinity` |
| Rule II: $0 \cdot (-\infty) = [-\infty, 0]_{in}$ | [§3.4](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) | `RuleII_ZeroTimesNegativeInfinity` |
| Central thesis identity $0 \cdot \infty = -1 \cdot (0 \cdot (-\infty))$ | [§6.1](06_applications.md#61-algebraic-consistency) | `Thesis01`, `Thesis02` |
| Non-associativity of multiplication | [Proposition 5.2](05_algebraic_structure.md#52-failure-of-associativity) | `MultiplicationNotAssociative` |
| Combined-operation examples | [§6.2](06_applications.md#62-combined-operations) | `ReadmeExample01`, `ReadmeExample02` |
| $\tfrac{0}{0} = [-\infty, \infty]_{in}$ | [§4.5](04_operations.md#45-division) | `DivisionByZeroIndeterminateForm` |
| $\tfrac{\infty}{\infty} = [0, \infty]_{in}$ | [§4.5](04_operations.md#45-division) | `DivisionInfinityByInfinity` |
| $0^0 = 1^\infty = \infty^0 = [0, \infty]_{in}$ | [§4.7](04_operations.md#47-exponentiation) | `Power_IndeterminateForm_0_pow_0`, `Power_IndeterminateForm_1_pow_Infinity`, `Power_IndeterminateForm_Infinity_pow_0` |

All 77 tests pass under the build instructions of [§7.2](#72-build-instructions). Test names not appearing in this table cover normalization invariants, arithmetic identities on point intervals, and IEEE-754 baseline comparisons.

## 7.5 Scope and Future Refinements

The reference implementation is intended as a proof of computational viability rather than a production library. Possible extensions include:

- **Arbitrary precision arithmetic** (e.g., via `mpfr` or `boost::multiprecision`) to eliminate floating-point artifacts.
- **Symbolic representation** to preserve exact algebraic identities through interval operations.
- **Language bindings** (Python, Julia) for use in scientific computing workflows.
- **Formal verification** of operation correctness using a proof assistant such as Coq or Lean.

---

[← Previous: Applications](06_applications.md) | [Back to Contents](../README.md) | [Next: Conclusion →](08_conclusion.md)
