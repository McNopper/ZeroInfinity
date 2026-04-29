"""
Generates scientific publication-quality figures for the ZeroInfinity paper.

Run from the repository root or from the illustrations/ directory:
    python generate_figures.py

Produces:
    - fig_extended_real_intervals.png  : Extended real line with key intervals
    - fig_indeterminate_limits.png     : Limit convergence visualization for 0*infty
    - fig_interval_multiplication.png  : Geometric view of interval multiplication
"""

import os

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import FancyArrowPatch, Rectangle


# Publication-quality matplotlib settings
plt.rcParams.update({
    "font.family": "serif",
    "font.serif": ["Computer Modern Roman", "Times New Roman", "DejaVu Serif"],
    "font.size": 11,
    "axes.labelsize": 11,
    "axes.titlesize": 12,
    "legend.fontsize": 10,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
    "mathtext.fontset": "cm",
    "axes.linewidth": 0.8,
    "lines.linewidth": 1.5,
    "savefig.dpi": 300,
    "savefig.bbox": "tight",
    "savefig.pad_inches": 0.1,
})

OUTPUT_DIR = os.path.dirname(os.path.abspath(__file__))


def figure_extended_real_intervals():
    """Figure 1: Extended real line with the two foundation intervals."""
    fig, ax = plt.subplots(figsize=(7.0, 2.2))

    x_min, x_max = -1.0, 1.0
    y_axis = 0.0

    # Main extended real line
    ax.annotate(
        "", xy=(x_max + 0.05, y_axis), xytext=(x_min - 0.05, y_axis),
        arrowprops=dict(arrowstyle="->", color="black", lw=1.0),
    )

    # Interval [-infinity, 0] (left) - shown with thick blue segment
    ax.plot([x_min, 0.0], [y_axis, y_axis], color="#1f4e79", lw=4.5,
            solid_capstyle="butt", label=r"$[-\infty,\,0]_{in}$")

    # Interval [0, infinity] (right) - shown with thick green segment
    ax.plot([0.0, x_max], [y_axis, y_axis], color="#2e7d32", lw=4.5,
            solid_capstyle="butt", label=r"$[0,\,\infty]_{in}$")

    # Tick marks at -infty, 0, +infty
    for x, label in [(x_min, r"$-\infty$"), (0.0, r"$0$"), (x_max, r"$\infty$")]:
        ax.plot([x, x], [y_axis - 0.06, y_axis + 0.06], color="black", lw=1.0)
        ax.annotate(label, xy=(x, y_axis - 0.10), ha="center", va="top", fontsize=12)

    # Interval labels (above the line)
    ax.annotate(
        r"$[-\infty,\,0]_{in}$",
        xy=(-0.5, y_axis + 0.12), ha="center", va="bottom",
        color="#1f4e79", fontsize=12,
    )
    ax.annotate(
        r"$[0,\,\infty]_{in}$",
        xy=(0.5, y_axis + 0.12), ha="center", va="bottom",
        color="#2e7d32", fontsize=12,
    )

    # Title above the figure
    ax.annotate(
        r"Foundation intervals in $\overline{\mathbb{R}}$",
        xy=(0.0, y_axis + 0.32), ha="center", va="bottom",
        fontsize=12, fontweight="bold",
    )

    ax.set_xlim(x_min - 0.15, x_max + 0.15)
    ax.set_ylim(-0.30, 0.45)
    ax.set_axis_off()

    out = os.path.join(OUTPUT_DIR, "fig_extended_real_intervals.png")
    plt.savefig(out)
    plt.close(fig)
    print(f"Saved: {out}")


def figure_indeterminate_limits():
    """Figure 2: Sequences a_n * b_n with a_n -> 0, b_n -> infinity converging to
    different limits, justifying [0, infinity]_{in} for 0 * infinity.
    """
    fig, ax = plt.subplots(figsize=(7.0, 4.2))

    n = np.arange(1, 50)

    # Three sequences a_n * b_n with a_n -> 0 and b_n -> infinity
    seq_to_zero = (1.0 / (n ** 2)) * n  # = 1/n -> 0
    seq_to_one = (1.0 / n) * n          # = 1 -> 1
    seq_to_inf = (1.0 / n) * (n ** 2)   # = n -> infinity

    ax.plot(n, seq_to_zero, marker="o", markersize=3.5, color="#1f4e79",
            label=r"$a_n=1/n^2,\ b_n=n\;\;\Rightarrow\;\; a_n b_n \to 0$")
    ax.plot(n, seq_to_one, marker="s", markersize=3.5, color="#b8860b",
            label=r"$a_n=1/n,\ b_n=n\;\;\Rightarrow\;\; a_n b_n \to 1$")
    ax.plot(n, seq_to_inf, marker="^", markersize=3.5, color="#2e7d32",
            label=r"$a_n=1/n,\ b_n=n^2\;\;\Rightarrow\;\; a_n b_n \to \infty$")

    ax.set_yscale("log")
    ax.set_xlabel(r"$n$")
    ax.set_ylabel(r"$a_n \cdot b_n$ (log scale)")
    ax.set_title(
        r"Limits of $a_n \cdot b_n$ with $a_n \to 0$ and $b_n \to \infty$"
        "\n"
        r"all values lie in $[0,\,\infty]_{in}$",
        fontsize=11,
    )
    ax.grid(True, which="both", linestyle=":", linewidth=0.5, alpha=0.7)
    ax.legend(loc="center right", framealpha=0.95)

    out = os.path.join(OUTPUT_DIR, "fig_indeterminate_limits.png")
    plt.savefig(out)
    plt.close(fig)
    print(f"Saved: {out}")


def figure_interval_multiplication():
    """Figure 3: Geometric view of interval multiplication.
    Shows that [x0, x1] * [y0, y1] is the interval [min, max] over the four endpoint
    products, illustrated with an example.
    """
    fig, ax = plt.subplots(figsize=(6.5, 5.0))

    # Example: [-1, 2] * [-3, 1]
    x0, x1 = -1.0, 2.0
    y0, y1 = -3.0, 1.0

    products = {
        r"$x_0 y_0$": (x0, y0, x0 * y0),
        r"$x_0 y_1$": (x0, y1, x0 * y1),
        r"$x_1 y_0$": (x1, y0, x1 * y0),
        r"$x_1 y_1$": (x1, y1, x1 * y1),
    }

    # Plot rectangle representing [x0, x1] x [y0, y1]
    rect = Rectangle((x0, y0), x1 - x0, y1 - y0, linewidth=1.5,
                     edgecolor="#444444", facecolor="#e0e0e0", alpha=0.6)
    ax.add_patch(rect)

    # Mark the 4 corners and label with their products
    z_min = min(p[2] for p in products.values())
    z_max = max(p[2] for p in products.values())

    for label, (px, py, pz) in products.items():
        if pz == z_min:
            color = "#1f4e79"
        elif pz == z_max:
            color = "#2e7d32"
        else:
            color = "#777777"
        ax.plot(px, py, "o", color=color, markersize=8, zorder=5)
        ax.annotate(
            f"{label}\n$={pz:g}$",
            xy=(px, py),
            xytext=(px + 0.2, py + 0.25),
            fontsize=10,
            color=color,
        )

    # Axes through origin
    ax.axhline(0, color="black", lw=0.5)
    ax.axvline(0, color="black", lw=0.5)

    ax.set_xlim(x0 - 1.0, x1 + 1.5)
    ax.set_ylim(y0 - 1.0, y1 + 1.5)
    ax.set_xlabel(r"$x \in [x_0,\,x_1]$")
    ax.set_ylabel(r"$y \in [y_0,\,y_1]$")
    ax.set_title(
        r"Interval multiplication $[x_0,x_1]_{in} \cdot [y_0,y_1]_{in}$"
        "\n"
        r"min/max over the four endpoint products"
        f"\n(example: [{x0:g},{x1:g}] · [{y0:g},{y1:g}] = "
        f"[{z_min:g},{z_max:g}])",
        fontsize=11,
    )
    ax.set_aspect("equal", adjustable="box")
    ax.grid(True, linestyle=":", linewidth=0.5, alpha=0.7)

    out = os.path.join(OUTPUT_DIR, "fig_interval_multiplication.png")
    plt.savefig(out)
    plt.close(fig)
    print(f"Saved: {out}")


if __name__ == "__main__":
    figure_extended_real_intervals()
    figure_indeterminate_limits()
    figure_interval_multiplication()
