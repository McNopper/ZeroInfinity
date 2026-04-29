# 4. Operations on Interval Numbers

[← Previous: Interval Numbers](03_interval_numbers.md) | [Back to Contents](../README.md) | [Next: Algebraic Structure →](05_algebraic_structure.md)

---

All operations follow standard interval arithmetic [[6](09_references.md)], with explicit treatment of indeterminate forms.

## 4.1 Multiplication

**Definition 4.1 (Interval Multiplication).** For interval numbers $I = [x_0, x_1]_{in}$ and $J = [y_0, y_1]_{in}$, let $P_{ij} := x_i \cdot y_j$ for $i, j \in \{0, 1\}$. Define the **candidate set**

$$\mathcal{C}(I, J) := \bigcup_{i,j \in \{0,1\}} \mathcal{V}(x_i \cdot y_j) \;\subseteq\; \overline{\mathbb{R}},$$

where the *value map* $\mathcal{V}: \overline{\mathbb{R}} \cup \{0 \cdot \infty,\ 0 \cdot (-\infty)\} \to \mathcal{P}(\overline{\mathbb{R}})$ is defined by

$$
\mathcal{V}(p) := \begin{cases}
\{p\}, & p \in \overline{\mathbb{R}} \text{ (a defined product)}, \\
\{0, \infty\}, & p = 0 \cdot \infty \text{ (Rule I endpoints)}, \\
\{-\infty, 0\}, & p = 0 \cdot (-\infty) \text{ (Rule II endpoints)}.
\end{cases}
$$

The product is then

$$I \cdot J := \big[\min \mathcal{C}(I, J),\ \max \mathcal{C}(I, J)\big]_{in}.$$

In particular, if no $P_{ij}$ is an indeterminate form, the definition reduces to the classical interval-arithmetic formula

$$I \cdot J = \big[\min(x_0 y_0, x_0 y_1, x_1 y_0, x_1 y_1),\ \max(x_0 y_0, x_0 y_1, x_1 y_0, x_1 y_1)\big]_{in}.$$

**Scalar multiplication.** For $r \in \overline{\mathbb{R}}$ identified with the point interval $[r, r]_{in}$, Definition 4.1 specializes to:

$$
r \cdot [x_0, x_1]_{in} =
\begin{cases}
[r x_0, r x_1]_{in}, & r > 0, \\
[r x_1, r x_0]_{in}, & r < 0, \\
[0, 0]_{in}, & r = 0 \text{ and } 0 \notin\{-\infty, \infty\} \cap\{x_0, x_1\}, \\
[-\infty, 0]_{in} \text{ or } [0, \infty]_{in}, & r = 0 \text{ and } x_0 = -\infty \text{ or } x_1 = \infty \text{ (via Rules I/II)}.
\end{cases}
$$

**Geometric interpretation.** The four endpoint products correspond to the corners of the rectangle $[x_0, x_1] \times [y_0, y_1]$ in the $xy$-plane:

![Interval multiplication](../illustrations/fig_interval_multiplication.png)

*Figure 4.1: Geometric view of interval multiplication. The product $[x_0, x_1]_{in} \cdot [y_0, y_1]_{in}$ is the closed interval bounded by the minimum and maximum of the four corner products. Example: $[-1, 2]_{in} \cdot [-3, 1]_{in} = [-6, 3]_{in}$.*

**Examples.**
- $(-1) \cdot [0, \infty]_{in} = [-\infty, 0]_{in}$ (validates the consistency between Rule I and Rule II).
- $2 \cdot [1, 3]_{in} = [2, 6]_{in}$.

## 4.2 Addition

**Definition 4.2 (Interval Addition).**

$$[x_0, x_1]_{in} + [y_0, y_1]_{in} := [x_0 + y_0,\ x_1 + y_1]_{in}.$$

**Indeterminate form.** $\infty + (-\infty)$ and $(-\infty) + \infty$ both yield $[-\infty, \infty]_{in}$.

**Example.** $[0, \infty]_{in} + 5 = [5, \infty]_{in}$.

## 4.3 Subtraction

**Definition 4.3 (Interval Subtraction).**

$$[x_0, x_1]_{in} - [y_0, y_1]_{in} := [x_0 - y_1,\ x_1 - y_0]_{in}.$$

**Indeterminate form.** $\infty - \infty$ and $(-\infty) - (-\infty)$ both yield $[-\infty, \infty]_{in}$.

**Example.** $[1, 5]_{in} - [2, 3]_{in} = [1 - 3,\ 5 - 2]_{in} = [-2, 3]_{in}$.

## 4.4 Reciprocal

**Definition 4.4 (Reciprocal).** For an interval number $J = [y_0, y_1]_{in}$ that does not strictly contain zero (i.e., $y_0 \ge 0$ or $y_1 \le 0$), define

$$\frac{1}{J} := \left[\frac{1}{y_1},\ \frac{1}{y_0}\right]_{in},$$

with the conventions $\tfrac{1}{0^+} = +\infty$ when $y_0 = 0 \le y_1$ and $\tfrac{1}{0^-} = -\infty$ when $y_0 \le y_1 = 0$.

**Zero strictly interior to $J$.** If $y_0 < 0 < y_1$, the reciprocal is the union $[-\infty, 1/y_0]_{in} \cup [1/y_1, \infty]_{in}$, which is not a single interval. The framework returns $[-\infty, \infty]_{in}$ in this case, retaining closure within $\mathcal{I}$ at the cost of tightness.

## 4.5 Division

**Definition 4.5 (Interval Division).** For $I, J \in \mathcal{I}$:

$$I \div J := I \cdot \frac{1}{J},$$

evaluated using [Definition 4.1](#41-multiplication).

**Special case $\tfrac{0}{0}$.** $[0, 0]_{in} \div [0, 0]_{in}$ is assigned $[-\infty, \infty]_{in}$ by convention, justified by $\lim_{n \to 0^+} \tfrac{n}{n^2} = +\infty$ and $\lim_{n \to 0^-} \tfrac{n}{n^2} = -\infty$.

**Indeterminate form $\tfrac{\infty}{\infty}$.** Through [Definition 4.1](#41-multiplication) applied to a reciprocal containing $\infty$ or $-\infty$ as an endpoint, the form $\tfrac{\infty}{\infty}$ evaluates to $[0, \infty]_{in}$.

## 4.6 Absolute Value

**Definition 4.6 (Absolute Value).** For $[x_0, x_1]_{in}$ with $x_0 \le x_1$:

- If $x_0 \cdot x_1 \ge 0$ (the interval does not properly contain zero):

$$\big|[x_0, x_1]\big|_{in} := \big[\min(|x_0|, |x_1|),\ \max(|x_0|, |x_1|)\big]_{in}.$$

- If $x_0 \cdot x_1 < 0$ (the interval contains zero):

$$\big|[x_0, x_1]\big|_{in} := \big[0,\ \max(|x_0|, |x_1|)\big]_{in}.$$

**Example.** $\big|[-5, 3]\big|_{in} = [0, 5]_{in}$.

## 4.7 Exponentiation

**Definition 4.7 (Power).** For interval base $I = [x_0, x_1]_{in}$ and interval exponent $E = [y_0, y_1]_{in}$:

$$I^E := \big[\min(x_0^{y_0}, x_0^{y_1}, x_1^{y_0}, x_1^{y_1}),\ \max(x_0^{y_0}, x_0^{y_1}, x_1^{y_0}, x_1^{y_1})\big]_{in}.$$

For a scalar exponent $n$, treat $n$ as the point interval $[n, n]_{in}$.

**Indeterminate forms involving exponents:**
- $0^0 = [0, \infty]_{in}$
- $1^\infty = [0, \infty]_{in}$
- $\infty^0 = [0, \infty]_{in}$

**Justification of $0^0 = [0, \infty]_{in}$:**
- Sequence A: $a_n = \tfrac{1}{n}$, $b_n = \tfrac{1}{\sqrt{\ln n}}$, then $a_n^{b_n} \to 0$.
- Sequence B: $a_n = \tfrac{1}{n}$, $b_n = \tfrac{1}{\ln n}$, then $a_n^{b_n} \to e^{-1}$.
- Sequence C: $a_n = \tfrac{1}{n}$, $b_n = -\tfrac{1}{\sqrt{\ln n}}$, then $a_n^{b_n} \to \infty$.

**Special considerations:**
- For even integer exponents on intervals containing zero, the result includes $0$.
- For negative exponents on bases containing zero, the result extends to $\pm\infty$.
- Interval-to-interval power requires evaluation at all combinations of base and exponent endpoints to determine the resulting range.

---

[← Previous: Interval Numbers](03_interval_numbers.md) | [Back to Contents](../README.md) | [Next: Algebraic Structure →](05_algebraic_structure.md)
