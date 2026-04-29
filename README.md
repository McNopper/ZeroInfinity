# Interval Numbers: A Formal Algebraic Framework for Indeterminate Forms

**Author:** Norbert Nopper

---

## Abstract

The expressions $0 \cdot \infty$ and $0 \cdot (-\infty)$ are classical indeterminate forms that resist standard algebraic manipulation, even under extended real arithmetic. This work introduces **interval numbers**, a formal algebraic framework that represents indeterminate forms as closed intervals in the extended real line $\overline{\mathbb{R}}$. The interval $[x_0, x_1]_{in}$ is treated as a first-class algebraic object whose endpoints are *assigned by formal rules motivated by directional limit witnesses* rather than derived as a complete classification of all admissible limits. Operations are defined by interval-arithmetic-style hulls, extended by an explicit value map $\mathcal{V}$ that handles indeterminate endpoint products, and (for exponentiation) by an image-set hull on a stated admissible domain. The main proven result is that $(\mathcal{I}, \cdot)$ is a **unital magma** with identity $[1,1]_{in}$ — closed under multiplication, but neither associative (an explicit counterexample is given) nor monoidal. Addition, subtraction, multiplication, reciprocal, division, and absolute value are total on $\mathcal{I}$; exponentiation is partial on a precisely stated admissible domain. Worked examples and parametric limit witnesses for each classical indeterminate form (including $0\cdot\infty$, $\infty-\infty$, $0/0$, $\infty/\infty$, $0^0$, $1^\infty$, $\infty^0$) illustrate consistency with the chosen rules; no global optimality or tightness theorem is claimed. A C++ reference implementation with an accompanying unit-test suite is provided as a conformance artefact.

**Keywords:** indeterminate forms, interval arithmetic, extended real numbers, algebraic structure, interval algebra

---

## Contents

1. [Introduction](chapters/01_introduction.md)
2. [Related Work](chapters/02_related_work.md)
3. [Interval Numbers: Formal Definition](chapters/03_interval_numbers.md)
4. [Operations on Interval Numbers](chapters/04_operations.md)
5. [Algebraic Structure](chapters/05_algebraic_structure.md)
6. [Worked Examples and Classical Forms](chapters/06_applications.md)
7. [Conclusion and Future Work](chapters/07_conclusion.md)
8. [References](chapters/08_references.md)

A C++ reference implementation accompanies the paper; see [`test/README.md`](test/README.md) for build instructions, the test suite, and a mapping of mathematical claims to verification tests.

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
│   ├── README.md
│   ├── CMakeLists.txt
│   └── src/
│       ├── IntervalNumber.hpp
│       └── main.cpp
└── LICENSE
```

---

## Acknowledgments

The author gratefully acknowledges:

- Ingeborg Kettern, for analysis at the Fachhochschule Furtwangen
- Prof. Dr. Peter Fleischer, for algebra at the Fachhochschule Furtwangen
- Eric Lengyel, for insightful questions during the more recent development of this work
- 🤖 AI assistants, for review, critique, and editorial support during the preparation of the manuscript

### Personal Acknowledgments

The author gratefully acknowledges:

- his parents, Monika Friedel Nopper and Ernst Christian Nopper
- his wife, Iris Karoline Nopper
- and my family and friends
