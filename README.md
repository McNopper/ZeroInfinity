# Interval Numbers: A Formal Algebraic Framework for Indeterminate Forms

*by Norbert Nopper*

## Overview

A scientific paper that represents the classical indeterminate forms of
analysis as first-class algebraic objects. The foundation rule

$$0 \cdot \infty \;=\; \Omega \;:=\; [0, \infty]_{\mathrm{in}},$$

with companion $-\Omega := [-\infty, 0]_{\mathrm{in}}$ for $0 \cdot (-\infty)$,
defines closed intervals in the extended real line $\overline{\mathbb{R}}$ as
*interval numbers*. On this basis the paper develops a complete arithmetic on
the set $\mathcal{I}$ — addition, subtraction, multiplication, division,
reciprocal, absolute value, and exponentiation — and proves that
$(\mathcal{I}, \cdot)$ is a *unital magma* with identity $[1,1]_{\mathrm{in}}$:
closed under multiplication, but neither associative (an explicit
counterexample is given) nor monoidal. The framework recovers classical real
arithmetic on degenerate intervals while assigning consistent algebraic
meaning to the seven classical indeterminate forms $0 \cdot \infty$,
$\infty - \infty$, $\tfrac{0}{0}$, $\tfrac{\infty}{\infty}$, $0^0$,
$1^\infty$, and $\infty^0$.

A C++ reference implementation with a Google Test suite (93 tests) is
provided as a conformance artefact.

## The paper

- 📄 **[paper.pdf](paper.pdf)** — typeset PDF (recommended for reading)
- 📝 **[paper.tex](paper.tex)** — LaTeX source

Rebuild with any modern LaTeX engine:

```sh
latexmk -pdf paper.tex
```

## Reference implementation

The C++ reference implementation lives in [`test/`](test/) and provides an
`IntervalNumber` class plus 93 Google Test unit tests verifying the
operations and identities stated in the paper.

```bash
cd test
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

The implementation is a conformance artefact; the mathematical claims of the
paper are stated and justified in the manuscript itself and do not depend on
it.

## Credits

The author gratefully acknowledges:

- Ingeborg Kettern, for analysis at the Fachhochschule Furtwangen
- Prof. Dr. Peter Fleischer, for algebra at the Fachhochschule Furtwangen
- Eric Lengyel, for insightful questions during the more recent development
  of this work
- AI assistants, for review, critique, and editorial support during the
  preparation of the manuscript

Personal acknowledgments to the author's parents, Monika Friedel Nopper and
Ernst Christian Nopper; his wife, Iris Karoline Nopper; his family and
friends; and his close colleagues.

## License

Code: MIT. Paper text and figures: CC BY 4.0. See [LICENSE](LICENSE).
