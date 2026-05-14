"""
Generates scientific publication-quality figures for the ZeroInfinity paper.

Run from the repository root or from the figures/ directory:
    python generate_figures.py

Produces:
    - fig_extended_real_intervals.png  : Extended real line with key intervals
    - fig_indeterminate_limits.png     : Limit convergence visualization for 0*infty
    - fig_interval_multiplication.png  : Geometric view of interval multiplication
    - fig_reciprocal_zero_spanning.png : True reciprocal vs convex-hull approximation
    - fig_non_associativity.png        : Bracketing trees for the non-associativity counterexample
    - fig_algebraic_hierarchy.png      : Hasse-style hierarchy of algebraic structures
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


def figure_reciprocal_zero_spanning():
    """Figure 4.2: Reciprocal of an interval strictly containing zero.
    Top axis shows the divisor J = [y0, y1] with y0 < 0 < y1.
    Middle axis shows the exact reciprocal as two unbounded branches.
    Bottom axis shows the convex-hull approximation [-infty, infty] used by the
    framework to retain closure within \\mathcal{I}.
    """
    fig, ax = plt.subplots(figsize=(7.5, 3.8))

    y0, y1 = -2.0, 4.0
    inv_y0, inv_y1 = 1.0 / y0, 1.0 / y1  # = -0.5, 0.25
    x_min, x_max = -3.0, 5.0

    levels = {"divisor": 1.6, "true": 0.6, "hull": -0.4}

    # Helper: draw a bare horizontal axis at the given y
    def axis_line(y, label):
        ax.annotate(
            "", xy=(x_max + 0.1, y), xytext=(x_min - 0.1, y),
            arrowprops=dict(arrowstyle="->", color="black", lw=0.8),
        )
        ax.annotate(label, xy=(x_min - 0.4, y), ha="right", va="center", fontsize=10)

    # Divisor J = [y0, y1]
    axis_line(levels["divisor"], r"$J$")
    ax.plot([y0, y1], [levels["divisor"]] * 2, color="#444444", lw=4.5,
            solid_capstyle="butt")
    for x, lbl in [(y0, r"$y_0=-2$"), (0.0, r"$0$"), (y1, r"$y_1=4$")]:
        ax.plot([x, x], [levels["divisor"] - 0.06, levels["divisor"] + 0.06],
                color="black", lw=1.0)
        ax.annotate(lbl, xy=(x, levels["divisor"] - 0.10),
                    ha="center", va="top", fontsize=9)

    # True reciprocal: (-infty, 1/y0] U [1/y1, +infty)
    axis_line(levels["true"], r"$1/J$ exact")
    ax.plot([x_min, inv_y0], [levels["true"]] * 2, color="#1f4e79", lw=4.5,
            solid_capstyle="butt")
    ax.plot([inv_y1, x_max], [levels["true"]] * 2, color="#2e7d32", lw=4.5,
            solid_capstyle="butt")
    # arrow caps indicating unbounded extent
    ax.annotate("", xy=(x_min - 0.3, levels["true"]), xytext=(x_min, levels["true"]),
                arrowprops=dict(arrowstyle="->", color="#1f4e79", lw=1.5))
    ax.annotate("", xy=(x_max + 0.3, levels["true"]), xytext=(x_max, levels["true"]),
                arrowprops=dict(arrowstyle="->", color="#2e7d32", lw=1.5))
    for x, lbl in [(inv_y0, r"$1/y_0 = -\frac{1}{2}$"),
                   (inv_y1, r"$1/y_1 = \frac{1}{4}$")]:
        ax.plot([x, x], [levels["true"] - 0.06, levels["true"] + 0.06],
                color="black", lw=1.0)
        ax.annotate(lbl, xy=(x, levels["true"] - 0.10),
                    ha="center", va="top", fontsize=9)
    ax.annotate(r"$(-\infty,\,1/y_0]$", xy=((x_min + inv_y0) / 2, levels["true"] + 0.12),
                ha="center", va="bottom", color="#1f4e79", fontsize=9)
    ax.annotate(r"$[1/y_1,\,+\infty)$", xy=((inv_y1 + x_max) / 2, levels["true"] + 0.12),
                ha="center", va="bottom", color="#2e7d32", fontsize=9)

    # Convex hull: [-infty, +infty]
    axis_line(levels["hull"], r"$1/J$ hull")
    ax.plot([x_min, x_max], [levels["hull"]] * 2, color="#b8860b", lw=4.5,
            solid_capstyle="butt")
    ax.annotate("", xy=(x_min - 0.3, levels["hull"]), xytext=(x_min, levels["hull"]),
                arrowprops=dict(arrowstyle="->", color="#b8860b", lw=1.5))
    ax.annotate("", xy=(x_max + 0.3, levels["hull"]), xytext=(x_max, levels["hull"]),
                arrowprops=dict(arrowstyle="->", color="#b8860b", lw=1.5))
    ax.annotate(r"$[-\infty,\,+\infty]_{in}$ (convex hull, closure-preserving)",
                xy=((x_min + x_max) / 2, levels["hull"] + 0.12),
                ha="center", va="bottom", color="#b8860b", fontsize=9)

    ax.set_xlim(x_min - 1.4, x_max + 0.5)
    ax.set_ylim(-0.95, 2.25)
    ax.set_axis_off()

    ax.annotate(
        r"Reciprocal of a zero-spanning interval $J = [y_0,\,y_1]_{in}$, $y_0<0<y_1$",
        xy=(0.5, 0.98), xycoords="axes fraction",
        ha="center", va="top", fontsize=12, fontweight="bold",
    )

    out = os.path.join(OUTPUT_DIR, "fig_reciprocal_zero_spanning.png")
    plt.savefig(out)
    plt.close(fig)
    print(f"Saved: {out}")


def figure_non_associativity():
    """Figure 5.1: Two bracketing trees for the counterexample
    a = -1, b = 0, c = -infty showing
    (a*b)*c = [-infty, 0]_{in}  vs  a*(b*c) = [0, infty]_{in}.
    """
    fig, (ax_left, ax_right) = plt.subplots(1, 2, figsize=(8.5, 4.2))

    def draw_tree(ax, title, top_label, left_pair, right_leaf, mid_label, result, result_color, leaf_labels):
        ax.set_xlim(-1, 5)
        ax.set_ylim(-0.5, 4.5)
        ax.set_axis_off()
        ax.set_title(title, fontsize=11, fontweight="bold")

        # Layout coordinates
        root = (2.0, 3.6)
        mid = left_pair["mid"]      # internal node (sub-product)
        leaf_a = left_pair["a"]
        leaf_b = left_pair["b"]
        leaf_c = right_leaf

        # Edges
        for parent, child in [(root, mid), (root, leaf_c),
                              (mid, leaf_a), (mid, leaf_b)]:
            ax.plot([parent[0], child[0]], [parent[1], child[1]],
                    color="#444444", lw=1.0)

        # Node boxes
        def box(xy, text, color="#222222", fc="#ffffff"):
            ax.annotate(
                text, xy=xy, ha="center", va="center", fontsize=11,
                color=color,
                bbox=dict(boxstyle="round,pad=0.25", fc=fc, ec=color, lw=1.0),
            )

        box(root, top_label)
        box(mid, mid_label, color="#1f4e79", fc="#eaf2fa")
        box(leaf_a, leaf_labels["inner_left"])
        box(leaf_b, leaf_labels["inner_right"])
        box(leaf_c, leaf_labels["outer"])

        ax.annotate(
            result, xy=(2.0, -0.1), ha="center", va="center", fontsize=12,
            color=result_color, fontweight="bold",
            bbox=dict(boxstyle="round,pad=0.35", fc="#ffffff",
                      ec=result_color, lw=1.2),
        )

    draw_tree(
        ax_left,
        title=r"Left bracketing $(a \cdot b) \cdot c$",
        top_label=r"$\cdot$",
        left_pair={"mid": (0.8, 2.2), "a": (0.0, 0.9), "b": (1.6, 0.9)},
        right_leaf=(3.6, 0.9),
        mid_label=r"$a \cdot b = 0$",
        result=r"$0 \cdot (-\infty) = [-\infty,\,0]_{in}$",
        result_color="#1f4e79",
        leaf_labels={"inner_left": r"$a = -1$",
                     "inner_right": r"$b = 0$",
                     "outer": r"$c = -\infty$"},
    )

    draw_tree(
        ax_right,
        title=r"Right bracketing $a \cdot (b \cdot c)$",
        top_label=r"$\cdot$",
        left_pair={"mid": (3.2, 2.2), "a": (2.4, 0.9), "b": (4.0, 0.9)},
        right_leaf=(0.4, 0.9),
        mid_label=r"$b \cdot c = [-\infty,\,0]_{in}$",
        result=r"$-1 \cdot [-\infty,\,0]_{in} = [0,\,\infty]_{in}$",
        result_color="#2e7d32",
        leaf_labels={"inner_left": r"$b = 0$",
                     "inner_right": r"$c = -\infty$",
                     "outer": r"$a = -1$"},
    )

    fig.suptitle(
        r"Non-associativity of multiplication on $\mathcal{I}$: "
        r"$(a \cdot b) \cdot c \neq a \cdot (b \cdot c)$",
        fontsize=12, fontweight="bold",
    )
    fig.tight_layout(rect=[0, 0, 1, 0.94])

    out = os.path.join(OUTPUT_DIR, "fig_non_associativity.png")
    plt.savefig(out)
    plt.close(fig)
    print(f"Saved: {out}")


def figure_algebraic_hierarchy():
    """Figure 5.2: Hasse-style hierarchy of algebraic structures with one binary
    operation, marking the position of (\\mathcal{I}, \\cdot, [1,1]_{in})
    as a unital magma (closure + identity, but no associativity).
    """
    fig, ax = plt.subplots(figsize=(7.0, 5.2))

    # Each node: (label, x, y, axioms-text, highlighted?)
    nodes = {
        "magma":         (r"Magma",         0.0, 0.0, "closure", False),
        "unital_magma":  (r"Unital magma",  -1.4, 1.2, "+ identity", True),
        "semigroup":     (r"Semigroup",     1.4, 1.2, "+ associativity", False),
        "monoid":        (r"Monoid",        0.0, 2.4, "+ identity\n+ associativity", False),
        "group":         (r"Group",         0.0, 3.6, "+ inverses", False),
    }

    edges = [
        ("magma", "unital_magma"),
        ("magma", "semigroup"),
        ("unital_magma", "monoid"),
        ("semigroup", "monoid"),
        ("monoid", "group"),
    ]

    for src, dst in edges:
        x0, y0 = nodes[src][1], nodes[src][2]
        x1, y1 = nodes[dst][1], nodes[dst][2]
        ax.plot([x0, x1], [y0, y1], color="#888888", lw=1.0, zorder=1)

    for key, (label, x, y, axioms, highlight) in nodes.items():
        if highlight:
            fc, ec, fontw = "#fff7d6", "#b8860b", "bold"
        else:
            fc, ec, fontw = "#ffffff", "#444444", "normal"
        ax.annotate(
            f"{label}\n" + r"$\mathit{" + axioms.replace(' ', r'\;').replace('\n', r'\;\;') + r"}$",
            xy=(x, y), ha="center", va="center", fontsize=10, fontweight=fontw,
            bbox=dict(boxstyle="round,pad=0.4", fc=fc, ec=ec, lw=1.3), zorder=3,
        )

    # Annotation pointing at unital magma
    ax.annotate(
        r"$(\mathcal{I},\,\cdot,\,[1,1]_{in})$"
        "\n"
        r"closure: yes, identity: yes, associativity: no",
        xy=(-1.4, 1.2), xytext=(-3.2, 2.0),
        ha="center", va="center", fontsize=10, color="#b8860b",
        arrowprops=dict(arrowstyle="->", color="#b8860b", lw=1.0),
        bbox=dict(boxstyle="round,pad=0.3", fc="#fff7d6", ec="#b8860b", lw=1.0),
    )

    ax.set_xlim(-4.0, 3.5)
    ax.set_ylim(-0.7, 4.3)
    ax.set_axis_off()
    ax.set_title(
        r"Algebraic structures with one binary operation"
        "\n"
        r"(arrows denote ``adds an axiom'' — strictly stronger structure)",
        fontsize=11, fontweight="bold",
    )

    out = os.path.join(OUTPUT_DIR, "fig_algebraic_hierarchy.png")
    plt.savefig(out)
    plt.close(fig)
    print(f"Saved: {out}")


if __name__ == "__main__":
    figure_extended_real_intervals()
    figure_indeterminate_limits()
    figure_interval_multiplication()
    figure_reciprocal_zero_spanning()
    figure_non_associativity()
    figure_algebraic_hierarchy()
