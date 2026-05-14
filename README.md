# Interval Numbers: A Formal Algebraic Framework for Indeterminate Forms

**Author:** Norbert Nopper

## Paper

The full scientific paper is provided as a single LaTeX-typeset PDF:

- **[paper.pdf](paper.pdf)** — the complete manuscript.
- **[paper.tex](paper.tex)** — LaTeX source.

### Foundation Rule (Rule I)

$$0 \cdot \infty = \Omega := [0, \infty]_{in}$$

Within the interval-number framework, the indeterminate form
$0 \cdot \infty$ is identified with the foundation interval
$\Omega := [0, \infty]_{in}$, with companion $-\Omega := [-\infty, 0]_{in}$
for $0 \cdot (-\infty)$ (Rule II). The paper develops this framework
into a formal algebraic theory in which the basic arithmetic operations
are total on the set of interval numbers $\mathcal{I}$, and proves that
$(\mathcal{I}, \cdot)$ is a unital magma with identity $[1, 1]_{in}$ —
closed under multiplication, but neither associative nor monoidal.

## Repository Structure

```
ZeroInfinity/
├── README.md                  Entry point (this file)
├── LICENSE
├── paper.tex                  LaTeX source of the paper
├── paper.pdf                  Typeset PDF of the paper
├── illustrations/Figures and figure-generation script
│   ├── generate_figures.py
│   ├── fig_extended_real_intervals.png
│   ├── fig_indeterminate_limits.png
│   ├── fig_interval_multiplication.png
│   ├── fig_reciprocal_zero_spanning.png
│   ├── fig_non_associativity.png
│   └── fig_algebraic_hierarchy.png
└── test/                      C++ reference implementation and unit tests
    ├── CMakeLists.txt
    └── src/
        ├── IntervalNumber.hpp
        └── main.cpp
```

## Building the Paper

The PDF in `paper.pdf` is committed for convenience and can be rebuilt
from `paper.tex` with any modern LaTeX engine. Tectonic is recommended
because it auto-fetches all required packages:

```bash
tectonic paper.tex
```

Alternatively, with a full TeX Live or MiKTeX installation:

```bash
pdflatex paper.tex
pdflatex paper.tex   # rerun to resolve cross-references
```

## Regenerating the Figures

The figures in `figures/` are generated programmatically with
Python and matplotlib (publication-quality serif font, LaTeX math
rendering, 300 DPI).

Requirements:

- Python 3.9 or later
- `matplotlib` (tested with 3.10.8)
- `numpy` (tested with 2.4.1)

Install and run:

```bash
pip install "matplotlib==3.10.8" "numpy==2.4.1"
python figures/generate_figures.py
```

All `.png` files in `figures/` are overwritten on each run.

## C++ Reference Implementation

A C++ reference implementation accompanies the paper as a conformance
artefact. It is provided as supporting evidence; the mathematical
claims of the paper are stated and justified in the manuscript and do
not depend on the implementation.

- **Core data structure:** the class `IntervalNumber`
  ([`test/src/IntervalNumber.hpp`](test/src/IntervalNumber.hpp))
  uses `double` for endpoint storage, normalizes endpoints to ensure
  $x_0 \le x_1$, and propagates `NaN` semantics.
- **Arithmetic operations:** all operations defined in the paper with
  explicit handling of extended-real limits, including the
  indeterminate forms $0 \cdot \infty$, $\infty - \infty$, and related
  cases.
- **Unit tests:** a suite of 93 tests
  ([`test/src/main.cpp`](test/src/main.cpp)) using Google Test,
  validating mathematical properties, edge cases, and IEEE-754
  baseline behaviour.

### Build Instructions

CMake 3.14 or later is required. Google Test is fetched automatically
via CMake's `FetchContent` module.

```bash
cd test
cmake -S . -B build
cmake --build build --config Release
```

### Running the Tests

The location of the test executable depends on the CMake generator:

```bash
# Single-config generators (Ninja, Unix Makefiles)
./build/interval_test          # add .exe on Windows

# Multi-config generators (Visual Studio, Xcode)
./build/Release/interval_test.exe
./build/Debug/interval_test.exe
```

Alternatively, run the suite via CTest from the build directory:

```bash
ctest --test-dir build --output-on-failure -C Release
```

### Mapping of Mathematical Claims to Tests

| Claim | Test name(s) |
|-------|--------------|
| Rule I: $0 \cdot \infty = [0, \infty]_{in}$ | `RuleI_ZeroTimesInfinity` |
| Rule II: $0 \cdot (-\infty) = [-\infty, 0]_{in}$ | `RuleII_ZeroTimesNegativeInfinity` |
| Central thesis identity $0 \cdot \infty = -1 \cdot (0 \cdot (-\infty))$ | `Thesis01`, `Thesis02` |
| Non-associativity of multiplication | `MultiplicationNotAssociative` |
| Combined-operation examples | `ReadmeExample01`, `ReadmeExample02` |
| $\frac{0}{0} = [-\infty, \infty]_{in}$ | `DivisionByZeroIndeterminateForm` |
| $\frac{\infty}{\infty} = [0, \infty]_{in}$ | `DivisionInfinityByInfinity` |
| $0^0 = 1^\infty = \infty^0 = [0, \infty]_{in}$ | `Power_IndeterminateForm_0_pow_0`, `Power_IndeterminateForm_1_pow_Infinity`, `Power_IndeterminateForm_Infinity_pow_0` |

All 93 tests pass under the build instructions above. The remaining
tests cover normalization invariants, arithmetic identities on point
intervals, IEEE-754 baseline comparisons, and regression tests for
reciprocal/division/abs/pow on edge cases.

## Acknowledgments

The author gratefully acknowledges:

- Ingeborg Kettern, for analysis at the Fachhochschule Furtwangen
- Prof. Dr. Peter Fleischer, for algebra at the Fachhochschule Furtwangen
- Eric Lengyel, for insightful questions during the more recent
  development of this work
- AI assistants, for review, critique, and editorial support during
  the preparation of the manuscript

### Personal Acknowledgments

The author gratefully acknowledges his parents, Monika Friedel Nopper
and Ernst Christian Nopper; his wife, Iris Karoline Nopper; his family
and friends; and his close colleagues.

## License

See [LICENSE](LICENSE).
