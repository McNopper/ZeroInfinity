# Interval Numbers: A Rigorous Treatment of Indeterminate Forms

**Author:** Norbert Nopper

---

## Abstract

The expressions $0 \cdot \infty$ and $0 \cdot (-\infty)$ are classical indeterminate forms that resist standard algebraic manipulation, even under extended real arithmetic. This work introduces **interval numbers**, a formal framework for representing indeterminate forms as closed intervals in the extended real line $\overline{\mathbb{R}}$. We define $[x_0, x_1]_{in}$ as a mathematical object that encapsulates all possible limiting values of indeterminate expressions, enabling algebraic operations on forms previously considered undefined. We establish that interval number operations follow standard interval arithmetic rules and demonstrate that the algebraic structure constitutes at least a Magma under multiplication. Formal operations (multiplication, addition, subtraction, division, absolute value, and exponentiation) are presented and their consistency is validated through explicit examples. A C++ reference implementation with a comprehensive unit test suite is provided as evidence of computational viability.

**Keywords:** indeterminate forms, interval arithmetic, extended real numbers, algebraic structure, interval algebra

---

## Contents

1. [Introduction](chapters/01_introduction.md)
2. [Related Work](chapters/02_related_work.md)
3. [Interval Numbers: Formal Definition](chapters/03_interval_numbers.md)
4. [Operations on Interval Numbers](chapters/04_operations.md)
5. [Algebraic Structure](chapters/05_algebraic_structure.md)
6. [Applications and Examples](chapters/06_applications.md)
7. [Implementation](chapters/07_implementation.md)
8. [Conclusion and Future Work](chapters/08_conclusion.md)
9. [References](chapters/09_references.md)

---

## Note on Rendering

The mathematical formulas use LaTeX notation compatible with [MathJax](https://www.mathjax.org/).
For optimal rendering, view this document in:

- GitHub's web interface (built-in MathJax support),
- [Visual Studio Code](https://code.visualstudio.com/) with a Markdown + Math preview extension,
- or any Markdown renderer with MathJax support.

Figures are regenerated from a Python script in [`illustrations/`](illustrations/README.md).

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
│   ├── 07_implementation.md
│   ├── 08_conclusion.md
│   └── 09_references.md
├── illustrations/             Figures and figure-generation script
│   ├── README.md
│   ├── generate_figures.py
│   ├── fig_extended_real_intervals.png
│   ├── fig_indeterminate_limits.png
│   └── fig_interval_multiplication.png
├── test/                      C++ reference implementation and unit tests
│   ├── README.md
│   ├── CMakeLists.txt
│   └── src/
│       ├── IntervalNumber.hpp
│       └── main.cpp
└── LICENSE
```

---

## Acknowledgments

The author gratefully acknowledges Eric Lengyel for insightful initial questions, family and colleagues for careful review and patience, and Ingeborg Kettern for foundational motivation rooted in classical analysis and inspiration through the legacy of Carl Friedrich Gauß.

---

## License

This work is distributed under the terms of the [MIT License](LICENSE).
