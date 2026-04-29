# 4. Operations on Interval Numbers

[← Previous: Interval Numbers](03_interval_numbers.md) | [Back to Contents](../README.md) | [Next: Algebraic Structure →](05_algebraic_structure.md)

---

All operations follow standard interval arithmetic [[6](08_references.md)], with explicit treatment of indeterminate forms.

## 4.1 Multiplication

**Definition 4.1 (Interval Multiplication).** For interval numbers $`I = [x_0, x_1]_{in}`$ and $`J = [y_0, y_1]_{in}`$, let $`P_{ij} := x_i \cdot y_j`$ for $`i, j \in \lbrace 0, 1\rbrace`$. Define the **candidate set**

$$\mathcal{C}(I, J) := \bigcup_{i,j \in \lbrace 0,1\rbrace } \mathcal{V}(x_i \cdot y_j) \;\subseteq\; \overline{\mathbb{R}},$$

where the *value map* $\mathcal{V}$ is defined symmetrically on each ordered pair of factors:

$$
\mathcal{V}(p) := \begin{cases}
\lbrace p\rbrace, & p \in \overline{\mathbb{R}} \text{ (a defined product)}, \\
\lbrace 0, \infty\rbrace, & p \in \lbrace \,0 \cdot \infty,\ \infty \cdot 0\,\rbrace\text{ (Rule I endpoints)}, \\
\lbrace -\infty, 0\rbrace, & p \in \lbrace \,0 \cdot (-\infty),\ (-\infty) \cdot 0\,\rbrace\text{ (Rule II endpoints)}.
\end{cases}
$$

Multiplication of finite reals with $\pm\infty$ commutes in $\overline{\mathbb{R}}$, so the only ordered pairs requiring symmetric extension are those involving the indeterminate factor $0$.

The product is then

$$I \cdot J := [\min \mathcal{C}(I, J),\ \max \mathcal{C}(I, J)]_{in}.$$

In particular, if no $`P_{ij}`$ is an indeterminate form, the definition reduces to the classical interval-arithmetic formula

$$I \cdot J = [\min(x_0 y_0, x_0 y_1, x_1 y_0, x_1 y_1),\ \max(x_0 y_0, x_0 y_1, x_1 y_0, x_1 y_1)]_{in}.$$

**Scalar multiplication.** For finite $r \in \mathbb{R}$ identified with the point interval $`[r, r]_{in}`$, Definition 4.1 specializes to:

$$
r \cdot [x_0, x_1]_{in} =
\begin{cases}
[r x_0,\ r x_1]_{in}, & r > 0, \\
[r x_1,\ r x_0]_{in}, & r < 0, \\
[0, 0]_{in}, & r = 0,\ x_0 > -\infty,\ x_1 < +\infty, \\
[-\infty, 0]_{in}, & r = 0,\ x_0 = -\infty,\ x_1 < +\infty, \\
[0, \infty]_{in}, & r = 0,\ x_0 > -\infty,\ x_1 = +\infty, \\
[-\infty, \infty]_{in}, & r = 0,\ x_0 = -\infty,\ x_1 = +\infty.
\end{cases}
$$

The four $`r = 0`$ subcases follow from $`\mathcal{V}`$ applied to the candidate products $`0 \cdot x_0`$ and $`0 \cdot x_1`$. For *infinite* scalars $`r \in \lbrace -\infty, +\infty\rbrace`$ (which may produce indeterminate corner products $`r \cdot 0`$ when $`0 \in [x_0, x_1]`$), no closed-form simplification is asserted; the result is obtained directly from the candidate-set rule of Definition 4.1, e.g.

$$+\infty \cdot [0, 1]_{in} \;=\; [\min\lbrace 0, +\infty\rbrace,\ \max\lbrace 0, +\infty\rbrace ]_{in} \;=\; [0, +\infty]_{in}.$$

**Geometric interpretation.** The four endpoint products correspond to the corners of the rectangle $`[x_0, x_1] \times [y_0, y_1]`$ in the $xy$-plane:

![Interval multiplication](../illustrations/fig_interval_multiplication.png)

*Figure 4.1: Geometric view of interval multiplication. The product $`[x_0, x_1]_{in} \cdot [y_0, y_1]_{in}`$ is the closed interval bounded by the minimum and maximum of the four corner products. Example: $`[-1, 2]_{in} \cdot [-3, 1]_{in} = [-6, 3]_{in}`$.*

**Examples.**
- $`(-1) \cdot [0, \infty]_{in} = [-\infty, 0]_{in}`$ (validates the consistency between Rule I and Rule II).
- $`2 \cdot [1, 3]_{in} = [2, 6]_{in}`$.

## 4.2 Addition

**Definition 4.2 (Interval Addition).** For interval numbers $`I = [x_0, x_1]_{in}`$ and $`J = [y_0, y_1]_{in}`$, define the candidate set

$$\mathcal{C}_{+}(I, J) := \mathcal{V}_{+}(x_0 + y_0) \cup \mathcal{V}_{+}(x_1 + y_1) \;\subseteq\; \overline{\mathbb{R}},$$

where the additive value map $`\mathcal{V}_{+}: \overline{\mathbb{R}} \cup \lbrace \infty + (-\infty),\ (-\infty) + \infty\rbrace\to \mathcal{P}(\overline{\mathbb{R}})`$ is

$$
\mathcal{V}_{+}(s) := \begin{cases}
\lbrace s\rbrace, & s \in \overline{\mathbb{R}} \text{ (a defined sum)}, \\
\lbrace -\infty, \infty\rbrace, & s \in \lbrace \infty + (-\infty),\ (-\infty) + \infty\rbrace.
\end{cases}
$$

Then

$$I + J := [\min \mathcal{C}_{+}(I, J),\ \max \mathcal{C}_{+}(I, J)]_{in}.$$

When neither endpoint sum is indeterminate this reduces to $`[x_0 + y_0,\ x_1 + y_1]_{in}`$.

**Example.** $`[0, \infty]_{in} + 5 = [5, \infty]_{in}`$. $`[0, \infty]_{in} + [-\infty, 0]_{in} = [-\infty, \infty]_{in}`$.

## 4.3 Subtraction

**Definition 4.3 (Interval Subtraction).** With the analogous value map $`\mathcal{V}_{-}`$ that sends $\infty - \infty$ and $(-\infty) - (-\infty)$ to $\lbrace -\infty, \infty\rbrace$ and every defined difference to a singleton,

$$\mathcal{C}_{-}(I, J) := \mathcal{V}_{-}(x_0 - y_1) \cup \mathcal{V}_{-}(x_1 - y_0),$$

and

$$I - J := [\min \mathcal{C}_{-}(I, J),\ \max \mathcal{C}_{-}(I, J)]_{in}.$$

When no indeterminate form arises this reduces to $`[x_0 - y_1,\ x_1 - y_0]_{in}`$.

**Example.** $`[1, 5]_{in} - [2, 3]_{in} = [-2, 3]_{in}`$.

## 4.4 Reciprocal

**Definition 4.4 (Reciprocal).** Reciprocation is defined on all of $\mathcal{I}$ by the following case analysis on the divisor $`J = [y_0, y_1]_{in}`$:

$$
\frac{1}{J} :=
\begin{cases}
[-\infty, \infty]_{in}, & y_0 = y_1 = 0, \\
[\tfrac{1}{y_1},\ \tfrac{1}{y_0}]_{in}, & y_0 > 0 \text{ or } y_1 < 0, \\
[\tfrac{1}{y_1},\ +\infty]_{in}, & y_0 = 0,\; y_1 > 0, \\
[-\infty,\ \tfrac{1}{y_0}]_{in}, & y_0 < 0,\; y_1 = 0, \\
[-\infty, \infty]_{in}, & y_0 < 0 < y_1.
\end{cases}
$$

The conventions $1/(0^{+}) = +\infty$ and $1/(0^{-}) = -\infty$ follow from one-sided real limits; the assignment for $`J = [0, 0]_{in}`$ is by convention, since neither sign of approach is privileged for a point interval at zero.

When $`y_0 < 0 < y_1`$, the exact reciprocal is the union of two unbounded branches $`[-\infty, 1/y_0]_{in} \cup [1/y_1, +\infty]_{in}`$, which is not a single interval. The framework returns its convex hull $`[-\infty, \infty]_{in}`$, retaining closure within $`\mathcal{I}`$ at the cost of tightness.

![Reciprocal of a zero-spanning interval](../illustrations/fig_reciprocal_zero_spanning.png)

*Figure 4.2: Reciprocal of a zero-spanning interval $`J = [y_0, y_1]_{in}`$ with $`y_0 < 0 < y_1`$ (example $`J = [-2, 4]_{in}`$). The exact reciprocal consists of two unbounded branches $`(-\infty, 1/y_0]`$ and $`[1/y_1, +\infty)`$ separated by a gap; the framework replaces this non-convex set with its convex hull $`[-\infty, +\infty]_{in}`$ to preserve closure within $`\mathcal{I}`$.*

## 4.5 Division

**Definition 4.5 (Interval Division).** Division is defined on all of $\mathcal{I} \times \mathcal{I}$ by

$$I \div J := I \cdot \frac{1}{J},$$

evaluated using [Definition 4.1](#41-multiplication) and [Definition 4.4](#44-reciprocal). The case analysis of the reciprocal makes division a total operation on $\mathcal{I}$.

**Indeterminate form $`\tfrac{0}{0}`$.** With $`I = J = [0, 0]_{in}`$, Definition 4.4 gives $`1/J = [-\infty, \infty]_{in}`$, and then $`[0, 0]_{in} \cdot [-\infty, \infty]_{in} = [-\infty, \infty]_{in}`$ via Rules I and II in Definition 4.1.

This is consistent with the one-sided limit witnesses

$$\lim_{x \to 0^{+}} \frac{x}{x^{2}} = +\infty, \qquad \lim_{x \to 0^{-}} \frac{x}{x^{2}} = -\infty,$$

and the parametric witness $`a_n = c/n`$, $`b_n = 1/n`$ giving $`a_n / b_n = c`$ for any $`c \in \mathbb{R}`$.

**Indeterminate form $`\tfrac{\infty}{\infty}`$.** With $`I = J = [\infty, \infty]_{in}`$, Definition 4.4 gives $`1/J = [0, 0]_{in}`$, and then $`[\infty, \infty]_{in} \cdot [0, 0]_{in} = [0, \infty]_{in}`$ via Rule I in Definition 4.1.

## 4.6 Absolute Value

**Definition 4.6 (Absolute Value).** Absolute value is defined by order rather than by endpoint multiplication, so that no indeterminate product is required:

$$
\lvert [x_0, x_1]_{in} \rvert :=
\begin{cases}
[x_0,\ x_1]_{in}, & 0 \le x_0, \\
[-x_1,\ -x_0]_{in}, & x_1 \le 0, \\
[0,\ \max(-x_0,\ x_1)]_{in}, & x_0 < 0 < x_1.
\end{cases}
$$

Negation of $\pm\infty$ is interpreted in $\overline{\mathbb{R}}$ in the standard way.

**Examples.** $`\lvert [-5, 3]_{in} \rvert = [0, 5]_{in}`$. $`\lvert [-\infty, 0]_{in} \rvert = [0, \infty]_{in}`$. $`\lvert [0, \infty]_{in} \rvert = [0, \infty]_{in}`$.

## 4.7 Exponentiation

**Definition 4.7 (Power).** Let $`I = [x_0, x_1]_{in}`$ and $`E = [y_0, y_1]_{in}`$. The **admissible domain** of exponentiation is

$$\mathrm{dom}(\,\cdot^{\,\cdot}) := \lbrace (I, E) \in \mathcal{I} \times \mathcal{I} \;:\; (x_0 > 0)\ \text{or}\ (x_0 \ge 0\ \text{and}\ y_0 \ge 0)\ \text{or}\ (E = \lbrace n\rbrace,\ n \in \mathbb{Z}_{\ge 0})\ \text{or}\ (E = \lbrace n\rbrace,\ n \in \mathbb{Z}_{<0}\ \text{and}\ 0 \notin I)\rbrace.$$

That is, exponentiation is admitted when (i) the base interval is strictly positive, or (ii) the base interval is non-negative and the exponent interval is non-negative (so no $0^{y}$ with $y < 0$ arises), or (iii) the exponent is a single non-negative integer (so negative bases are handled by integer powers and zero bases give $0^{n} = 0$ for $n \ge 1$ and $0^{0}$ via $\mathcal{V}^{\wedge}$), or (iv) the exponent is a single negative integer and $0 \notin I$ (so $0^{n}$ with $n < 0$ does not arise).

On the admissible domain, exponentiation is defined as the closed interval hull of the image set:

$$I^{E} := [\inf \mathcal{S}(I, E),\ \sup \mathcal{S}(I, E)]_{in},$$

where

$$\mathcal{S}(I, E) := \bigcup_{x \in I,\ y \in E} \mathcal{V}^{\wedge}(x^{y}) \;\subseteq\; \overline{\mathbb{R}},$$

and $\mathcal{V}^{\wedge}$ extends the real-valued map by handling the three indeterminate-form points:

$$
\mathcal{V}^{\wedge}(b^{e}) := \begin{cases}
\lbrace 0, \infty\rbrace, & (b, e) \in \lbrace (0,0),\ (1, \pm\infty),\ (\pm\infty, 0)\rbrace, \\
\lbrace b^{e}\rbrace, & b^{e} \text{ is defined in } \overline{\mathbb{R}}.
\end{cases}
$$

The admissible domain is chosen precisely so that every pair $(x, y) \in I \times E$ falls into one of the two cases above; in particular, points $0^{y}$ with $y < 0$ are excluded by the domain restriction (i)–(iv). If $(I, E) \notin \mathrm{dom}(\,\cdot^{\,\cdot})$ the operation is mathematically undefined; the reference implementation handles many — but not necessarily all — non-admissible inputs by NaN propagation and should not be relied upon to reject every non-admissible input outside the cases exercised by the unit tests.

**Reduction to corner formulas.** On regions where $`x \mapsto x^y`$ and $`y \mapsto x^y`$ are jointly monotonic, the supremum and infimum of $`\mathcal{S}(I, E)`$ are attained at corners $`(x_i, y_j)`$ and Definition 4.7 reduces to a four-corner endpoint formula. This is *not* the case in general; in particular, for a point positive-integer exponent $`E = \lbrace n\rbrace`$ with $`n \in \mathbb{Z}_{>0}`$ and a base interval crossing zero, $`x \mapsto x^n`$ attains its minimum $`0`$ in the interior:

$$
[x_0, x_1]_{in}^{\lbrace n\rbrace } =
\begin{cases}
[x_0^{n},\ x_1^{n}]_{in}, & 0 \le x_0\ \text{or}\ n\ \text{odd}, \\
[x_1^{n},\ x_0^{n}]_{in}, & x_1 \le 0\ \text{and}\ n\ \text{even}, \\
[0,\ \max(x_0^{n},\ x_1^{n})]_{in}, & x_0 < 0 < x_1\ \text{and}\ n\ \text{even},
\end{cases}
\qquad (n \in \mathbb{Z}_{>0}).
$$

The case $`n = 0`$ is *not* covered by the formula above: if $`I`$ contains an indeterminate base for the exponent $`0`$ — that is, if $`0 \in I`$ (giving the corner $`0^0`$) or if $`\pm\infty \in I`$ (giving the corners $`(\pm\infty)^{0}`$) — then $`\mathcal{V}^{\wedge}`$ contributes $`\lbrace 0, \infty\rbrace`$ at that point and $`I^{\lbrace 0\rbrace } = [0, \infty]_{in}`$; otherwise every point of $`I`$ is finite and nonzero, $`b^{0} = 1`$ pointwise, and $`I^{\lbrace 0\rbrace } = [1, 1]_{in}`$. The case $`n \in \mathbb{Z}_{<0}`$ is admissible only when $`0 \notin I`$ (case (iv) above); on that region $`x \mapsto x^n`$ is monotone and the result is

$$[x_0, x_1]_{in}^{\lbrace n\rbrace } \;=\; [\min(x_0^n, x_1^n),\ \max(x_0^n, x_1^n)]_{in}, \qquad (n \in \mathbb{Z}_{<0},\ 0 \notin I).$$

For strictly positive finite base intervals $I \subseteq (0, +\infty)$, write $x^{y} = \exp(y \log x)$. The image $y \log x$ over $\log I \times E$ is determined by the standard interval-product hull on these finite quantities, and applying the increasing map $\exp$ yields the corresponding hull for $x^{y}$. The only indeterminate closure point that can arise in this case is $1^{\pm\infty}$ (when $1 \in I$ and $\pm\infty \in E$), which is supplemented via $\mathcal{V}^{\wedge}$; the extended-base indeterminate point $(\pm\infty)^{0}$ does not arise here and is handled by the general image-set definition above.

**Indeterminate forms.**

$$0^{0} = 1^{\infty} = \infty^{0} = [0, \infty]_{in}.$$

Each of these arises as $`\mathcal{V}^{\wedge}`$ applied to the corresponding indeterminate-form point. The signed variants admitted by Definition 4.7 — namely $`1^{-\infty}`$ and $`(-\infty)^{0}`$ — are also indeterminate and receive the same hull $`[0, \infty]_{in}`$ by formal assignment via $`\mathcal{V}^{\wedge}`$. For $`1^{-\infty}`$, the parametric sequence $`a_n = 1 + (\ln c)/n,\ b_n = -n`$ gives $`a_n^{b_n} \to c^{-1}`$, attaining every $`c^{-1} \in (0, \infty)`$ as $`c`$ varies, so $`[0, \infty]_{in}`$ is a genuine limit hull. For $`(-\infty)^{0}`$, no analogous real-valued limit-witness argument is claimed: non-integer real exponents of negative bases are not real-valued, so $`(-\infty)^{0} = [0, \infty]_{in}`$ is a *formal convention* of the value map $`\mathcal{V}^{\wedge}`$ adopted for symmetry with $`(+\infty)^{0}`$ and to keep the admissible domain closed under sign reflection of the base.

**Justification of $`0^{0} = [0, \infty]_{in}`$:**
- Sequence A: $`a_n = 1/n`$, $`b_n = 1/\sqrt{\ln n}`$, then $`a_n^{b_n} \to 0`$.
- Sequence B: $`a_n = 1/n`$, $`b_n = 1/\ln n`$, then $`a_n^{b_n} \to e^{-1}`$.
- Sequence C: $`a_n = 1/n`$, $`b_n = -1/\sqrt{\ln n}`$, then $`a_n^{b_n} \to \infty`$.
- For any $`c > 0`$, the parametric witness $`a_n = 1/n`$, $`b_n = -\ln c / \ln n`$ gives $`a_n^{b_n} = c`$ for all $`n \ge 2`$, so every value of $`(0, \infty)`$ is attained.

---

[← Previous: Interval Numbers](03_interval_numbers.md) | [Back to Contents](../README.md) | [Next: Algebraic Structure →](05_algebraic_structure.md)
