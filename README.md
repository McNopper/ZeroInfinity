# Interval Numbers: A Rigorous Treatment of Indeterminate Forms

**Author:** Norbert Nopper

---

## Abstract

The expressions $0 \cdot \infty$ and $0 \cdot (-\infty)$ are classical indeterminate forms that resist standard algebraic manipulation, even under extended real arithmetic. This work introduces **interval numbers**, a formal framework for representing indeterminate forms as closed intervals in the extended real line $\overline{\mathbb{R}}$. We define $[x_0, x_1]_{in}$ as a mathematical object whose endpoints span the limits realizable by directional limit sequences associated with each indeterminate form, enabling algebraic operations on forms previously considered undefined. We establish that interval-number operations follow standard interval arithmetic rules and that the algebraic structure constitutes a **unital magma** under multiplication: closed and equipped with a two-sided identity $[1,1]_{in}$, but not associative. Formal operations (multiplication, addition, subtraction, division, absolute value, and exponentiation) are presented and their consistency is illustrated through explicit examples. A C++ reference implementation with a comprehensive unit-test suite is provided alongside the paper as a working artefact.

**Keywords:** indeterminate forms, interval arithmetic, extended real numbers, algebraic structure, interval algebra

---

## Contents

1. [Introduction](chapters/01_introduction.md)
2. [Related Work](chapters/02_related_work.md)
3. [Interval Numbers: Formal Definition](chapters/03_interval_numbers.md)
4. [Operations on Interval Numbers](chapters/04_operations.md)
5. [Algebraic Structure](chapters/05_algebraic_structure.md)
6. [Applications and Examples](chapters/06_applications.md)
7. [Conclusion and Future Work](chapters/07_conclusion.md)
8. [References](chapters/08_references.md)

A C++ reference implementation accompanies the paper; see [Reference Implementation](#reference-implementation) below.

---

## Repository Structure

```
ZeroInfinity/
├── README.md                  Entry point (this file)
├── chapters/                  Individual chapter sources
│   ├── 01_introduction.md
│   ├── 02_related_work.md
│   ├── 03_interval_numbers.md
│   ├── 04_operations.md
│   ├── 05_algebraic_structure.md
│   ├── 06_applications.md
│   ├── 07_conclusion.md
│   └── 08_references.md
├── illustrations/             Figures and figure-generation script
│   ├── README.md
│   ├── generate_figures.py
│   ├── fig_extended_real_intervals.png
│   ├── fig_indeterminate_limits.png
│   ├── fig_interval_multiplication.png
│   ├── fig_reciprocal_zero_spanning.png
│   ├── fig_non_associativity.png
│   └── fig_algebraic_hierarchy.png
├── test/                      C++ reference implementation and unit tests
│   ├── CMakeLists.txt
│   └── src/
│       ├── IntervalNumber.hpp
│       └── main.cpp
└── LICENSE
```

---

## Reference Implementation

A C++ reference implementation accompanies the theoretical framework, demonstrating computational viability. It is provided as supporting evidence; the mathematical claims of the paper are stated and justified in the chapters and do not depend on this implementation.

### Overview

The implementation resides in the [`test/`](test/) directory and provides:

- **Core data structure.** A class `IntervalNumber` ([`test/src/IntervalNumber.hpp`](test/src/IntervalNumber.hpp)) using `double` for endpoint storage, with normalization to ensure $x_0 \le x_1$ and propagation of `NaN` semantics.
- **Arithmetic operations.** All operations defined in [Section 4](chapters/04_operations.md) with explicit handling of extended-real limits, including the indeterminate forms $0 \cdot \infty$, $\infty - \infty$, and related cases.
- **Unit tests.** A test suite ([`test/src/main.cpp`](test/src/main.cpp)) employing the Google Test framework, validating mathematical properties, edge cases, and the behavior of native IEEE-754 floating-point limits used as a baseline.

### Build Instructions

The project uses CMake (version 3.14 or higher).

```bash
cd test
mkdir build && cd build
cmake ..
cmake --build .
```

Google Test is fetched automatically via CMake's `FetchContent` module; no manual installation is required.

### Running the Tests

```bash
# Debug build (default)
./Debug/interval_test.exe

# Release build
cmake --build . --config Release
./Release/interval_test.exe
```

On non-Windows platforms, the executable is produced without the `.exe` suffix.

### Verification: Mapping Mathematical Claims to Tests

The 89 unit tests in [`test/src/main.cpp`](test/src/main.cpp) verify that the reference implementation conforms to the formal definitions of [Chapter 4](chapters/04_operations.md) and to the stated examples and edge cases. Selected correspondences:

| Claim | Reference | Test name(s) |
|-------|-----------|--------------|
| Rule I: $0 \cdot \infty = [0, \infty]_{in}$ | [§3.4](chapters/03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) | `RuleI_ZeroTimesInfinity` |
| Rule II: $0 \cdot (-\infty) = [-\infty, 0]_{in}$ | [§3.4](chapters/03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) | `RuleII_ZeroTimesNegativeInfinity` |
| Central thesis identity $0 \cdot \infty = -1 \cdot (0 \cdot (-\infty))$ | [§6.1](chapters/06_applications.md#61-algebraic-consistency) | `Thesis01`, `Thesis02` |
| Non-associativity of multiplication | [Proposition 5.2](chapters/05_algebraic_structure.md#52-failure-of-associativity) | `MultiplicationNotAssociative` |
| Combined-operation examples | [§6.2](chapters/06_applications.md#62-combined-operations) | `ReadmeExample01`, `ReadmeExample02` |
| $\tfrac{0}{0} = [-\infty, \infty]_{in}$ | [§4.5](chapters/04_operations.md#45-division) | `DivisionByZeroIndeterminateForm` |
| $\tfrac{\infty}{\infty} = [0, \infty]_{in}$ | [§4.5](chapters/04_operations.md#45-division) | `DivisionInfinityByInfinity` |
| $0^0 = 1^\infty = \infty^0 = [0, \infty]_{in}$ | [§4.7](chapters/04_operations.md#47-exponentiation) | `Power_IndeterminateForm_0_pow_0`, `Power_IndeterminateForm_1_pow_Infinity`, `Power_IndeterminateForm_Infinity_pow_0` |

All 89 tests pass under the build instructions above. Test names not appearing in this table cover normalization invariants, arithmetic identities on point intervals, IEEE-754 baseline comparisons, and regression tests for reciprocal/division/abs/pow on edge cases.

### Scope and Future Refinements

The reference implementation is intended as a proof of computational viability rather than a production library. Possible extensions include:

- **Arbitrary precision arithmetic** (e.g., via `mpfr` or `boost::multiprecision`) to eliminate floating-point artifacts.
- **Symbolic representation** to preserve exact algebraic identities through interval operations.
- **Language bindings** (Python, Julia) for use in scientific computing workflows.
- **Formal verification** of operation correctness using a proof assistant such as Coq or Lean.

---

## Acknowledgments

The author gratefully acknowledges:

- 👩‍🏫 Ingeborg Kettern, for analysis at the Fachhochschule Furtwangen
- 👨‍🏫 Prof. Dr. Peter Fleischer, for algebra at the Fachhochschule Furtwangen
- 👨‍💻 Eric Lengyel, for insightful questions during the more recent development of this work
- 🤖 AI assistants, for review, critique, and editorial support during the preparation of the manuscript

### Personal Acknowledgments

The author gratefully acknowledges:

- his parents, Monika Friedel Nopper and Ernst Christian Nopper
- his wife, Iris Karoline Nopper
- and the wider family

---

## License

This work is distributed under the terms of the [MIT License](LICENSE).
