# 3. Interval Numbers: Formal Definition

[← Previous: Related Work](02_related_work.md) | [Back to Contents](../README.md) | [Next: Operations →](04_operations.md)

---

This section first fixes the arithmetic of the extended real line, then introduces interval numbers as formal mathematical objects, and finally states the foundation rules that govern indeterminate forms.

## 3.1 Preliminaries: Arithmetic in $\overline{\mathbb{R}}$

Let $\overline{\mathbb{R}} := \mathbb{R} \cup \{-\infty, +\infty\}$ denote the extended real line, equipped with the order extension $-\infty \le r \le +\infty$ for all $r \in \mathbb{R}$.

The standard operations on $\overline{\mathbb{R}}$ adopted in this work are summarized below.

**Defined operations.** For $r \in \mathbb{R}$ and $s \in \{-\infty, +\infty\}$:

| Operation | Result | Conditions |
|-----------|--------|------------|
| $r + s$ | $s$ | any $r \in \mathbb{R}$, $s \in \{-\infty, +\infty\}$ |
| $\infty + \infty$ | $\infty$ | |
| $(-\infty) + (-\infty)$ | $-\infty$ | |
| $r \cdot \infty$ | $\infty$ | $r > 0$ |
| $r \cdot \infty$ | $-\infty$ | $r < 0$ |
| $r \cdot (-\infty)$ | $-\infty$ | $r > 0$ |
| $r \cdot (-\infty)$ | $\infty$ | $r < 0$ |
| $\infty \cdot \infty$ | $\infty$ | |
| $\infty \cdot (-\infty)$ | $-\infty$ | |
| $r / \infty$ | $0$ | any $r \in \mathbb{R}$ |
| $r / (-\infty)$ | $0$ | any $r \in \mathbb{R}$ |

**Indeterminate forms.** The following expressions are *not* assigned a value in $\overline{\mathbb{R}}$ and are the object of study of this work:

$$0 \cdot \infty,\quad 0 \cdot (-\infty),\quad \infty + (-\infty),\quad \infty - \infty,\quad \tfrac{0}{0},\quad \tfrac{\infty}{\infty},\quad 0^{0},\quad 1^{\infty},\quad \infty^{0}.$$

In the standard treatment, computations encountering any of these forms are undefined. The interval-number framework provides a uniform algebraic interpretation.

## 3.2 Definition of an Interval Number

**Definition 3.1 (Interval Number).** Let $\overline{\mathbb{R}} = \mathbb{R} \cup \{-\infty, +\infty\}$ denote the extended real line equipped with the standard ordering. An **interval number** is a closed interval in $\overline{\mathbb{R}}$:

$$[x_0, x_1]_{in} := \{ x \in \overline{\mathbb{R}} \mid x_0 \le x \le x_1 \},$$

where $x_0, x_1 \in \overline{\mathbb{R}}$ and $x_0 \le x_1$.

**Notation.** Throughout this work, $\infty$ denotes $+\infty$; negative infinity is written explicitly as $-\infty$. Let $\mathcal{I}$ denote the set of all interval numbers.

## 3.3 Point Intervals

**Definition 3.2 (Point Interval).** A point interval is an interval number of the form $[r, r]_{in} = \{r\}$, which is identified with the element $r \in \overline{\mathbb{R}}$.

This identification provides a natural embedding $\overline{\mathbb{R}} \hookrightarrow \mathcal{I}$, $r \mapsto [r, r]_{in}$.

## 3.4 Foundation Rules for Indeterminate Forms

The central concept is that indeterminate forms correspond to intervals of possible limiting values. The two fundamental rules are:

**Rule I.** The indeterminate form $0 \cdot \infty$ is represented as

$$0 \cdot \infty = [0, \infty]_{in}.$$

**Rule II.** The indeterminate form $0 \cdot (-\infty)$ is represented as

$$0 \cdot (-\infty) = [-\infty, 0]_{in}.$$

These rules encode the principle that expressions of the form $a_n \cdot b_n$ with $\lim_n a_n = 0$ and $\lim_n b_n \in \{-\infty, \infty\}$ may converge to any value within the specified interval, depending on the relative rates at which $a_n$ approaches zero and $b_n$ approaches infinity.

## 3.5 Geometric Visualization

The two foundation intervals partition the extended real line through the origin:

![Foundation intervals on the extended real line](../illustrations/fig_extended_real_intervals.png)

*Figure 3.1: The extended real line $\overline{\mathbb{R}}$ with the two foundation intervals $[-\infty, 0]_{in}$ (blue) and $[0, \infty]_{in}$ (green), corresponding to Rules II and I, respectively.*

## 3.6 Justification for Rules I and II

The interval representations of Rules I and II are justified by exhibiting explicit sequences whose products realize different limit values within the intervals.

**For $0 \cdot \infty$:**
- Sequence A: $a_n = \frac{1}{n^2}$, $b_n = n$. Then $a_n \cdot b_n = \frac{1}{n} \to 0$.
- Sequence B: $a_n = \frac{1}{n}$, $b_n = n$. Then $a_n \cdot b_n = 1$ for all $n$.
- Sequence C: $a_n = \frac{1}{n}$, $b_n = n^2$. Then $a_n \cdot b_n = n \to \infty$.

All resulting limits lie in $[0, \infty]_{in}$.

![Sequence convergence](../illustrations/fig_indeterminate_limits.png)

*Figure 3.2: Three sequences $a_n \cdot b_n$ with $a_n \to 0$ and $b_n \to \infty$, converging to $0$, $1$, and $\infty$, respectively (log-scaled vertical axis). All limit values lie within $[0, \infty]_{in}$, consistent with Rule I.*

**For $0 \cdot (-\infty)$:**
- Sequence A: $a_n = \frac{1}{n}$, $b_n = -n$. Then $a_n \cdot b_n = -1$ for all $n$.
- Sequence B: $a_n = \frac{1}{n}$, $b_n = -n^2$. Then $a_n \cdot b_n = -n \to -\infty$.

All resulting limits lie in $[-\infty, 0]_{in}$.

---

[← Previous: Related Work](02_related_work.md) | [Back to Contents](../README.md) | [Next: Operations →](04_operations.md)
