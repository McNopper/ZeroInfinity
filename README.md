# Interval Numbers: A Formal Algebraic Framework for Indeterminate Forms

**Author:** Norbert Nopper

## Overview

This repository contains a scientific paper that introduces *interval
numbers* as a formal algebraic framework for the classical
indeterminate forms of analysis. The central postulate is the
foundation rule

$$0 \cdot \infty \;=\; \Omega \;:=\; [0, \infty]_{in},$$

with companion $-\Omega := [-\infty, 0]_{in}$ for $0 \cdot (-\infty)$.
On the basis of these rules the paper develops a complete arithmetic
on the set of interval numbers $\mathcal{I}$ — addition, subtraction,
multiplication, division, reciprocal, absolute value, and
exponentiation — and proves that $(\mathcal{I}, \cdot)$ is a unital
magma with identity $[1, 1]_{in}$: closed under multiplication, but
neither associative nor monoidal. The framework recovers the classical
real arithmetic on degenerate intervals while assigning consistent
algebraic meaning to the seven classical indeterminate forms
$0 \cdot \infty$, $\infty - \infty$, $\tfrac{0}{0}$,
$\tfrac{\infty}{\infty}$, $0^0$, $1^\infty$, and $\infty^0$.

## The Paper

The full manuscript, including all definitions, theorems, proofs,
figures, and references, is provided as:

- **[paper.pdf](paper.pdf)** — typeset PDF (recommended for reading).
- **[paper.tex](paper.tex)** — LaTeX source.

To rebuild the PDF from source, run any modern LaTeX engine on
`paper.tex` (e.g. `tectonic paper.tex`). The figures referenced by the
LaTeX source live in [`figures/`](figures/) and can be regenerated
with `python figures/generate_figures.py`.

## Reference Implementation

A C++ reference implementation accompanying the paper is available in
[`test/`](test/). It provides a `IntervalNumber` class and a suite of
93 Google Test unit tests that verify the operations and identities
stated in the paper. Build with CMake 3.14+:

```bash
cd test
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

The implementation is a conformance artefact; the mathematical claims
of the paper are stated and justified in the manuscript itself and do
not depend on it.

## License

See [LICENSE](LICENSE).
