# Illustrations

This directory contains the figures used throughout the document, together with the script used to generate them.

## Figures

| File | Referenced in | Description |
|------|---------------|-------------|
| `fig_extended_real_intervals.png` | [Section 3.5](../chapters/03_interval_numbers.md#35-geometric-visualization) | Extended real line $\overline{\mathbb{R}}$ with the foundation intervals $[-\infty, 0]_{in}$ and $[0, \infty]_{in}$ |
| `fig_indeterminate_limits.png` | [Section 3.6](../chapters/03_interval_numbers.md#36-justification-for-rules-i-and-ii) | Three sequences $a_n \cdot b_n$ ($a_n \to 0$, $b_n \to \infty$) converging to different values within $[0, \infty]_{in}$ |
| `fig_interval_multiplication.png` | [Section 4.1](../chapters/04_operations.md#41-multiplication) | Geometric view of interval multiplication via the four endpoint products |

## Regenerating the Figures

The figures are generated programmatically using Python and matplotlib, ensuring publication-quality consistency (serif font, LaTeX math rendering, 300 DPI).

### Requirements

- Python 3.9 or later
- `matplotlib`
- `numpy`

Install with:

```bash
pip install matplotlib numpy
```

### Run

From the repository root:

```bash
python illustrations/generate_figures.py
```

Or from this directory:

```bash
python generate_figures.py
```

All `.png` files in this directory are overwritten on each run.
