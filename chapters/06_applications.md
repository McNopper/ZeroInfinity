# 6. Applications and Examples

[← Previous: Algebraic Structure](05_algebraic_structure.md) | [Back to Contents](../README.md) | [Next: Conclusion →](07_conclusion.md)

---

This section demonstrates the consistency and utility of the framework through worked examples.

## 6.1 Algebraic Consistency

**Claim.** $\;0 \cdot \infty = -1 \cdot (0 \cdot (-\infty)).$

*Derivation.*

| Step | Operation or Rule |
|------|-------------------|
| $-1 \cdot (0 \cdot (-\infty))$ | apply [Rule II](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) |
| $-1 \cdot [-\infty, 0]_{in}$ | scalar multiplication ([Definition 4.1](04_operations.md#41-multiplication)) |
| $[-1 \cdot 0,\ -1 \cdot (-\infty)]_{in}$ | operations in $\overline{\mathbb{R}}$ |
| $[0, \infty]_{in}$ | apply [Rule I](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) |
| $0 \cdot \infty$ | $\square$ |

The interval-number framework therefore validates the intuitive algebraic identity, a result not attainable with naive limit analysis.

## 6.2 Combined Operations

**Example 6.1.** $\;\lvert \tfrac{0}{0} \rvert + \infty = \infty.$

*Derivation.*

- $\frac{0}{0} = [-\infty, \infty]_{in}$ ([Definition 4.5](04_operations.md#45-division));
- $\lvert [-\infty, \infty] \rvert_{in} = [0, \infty]_{in}$ ([Definition 4.6](04_operations.md#46-absolute-value));
- $[0, \infty]_{in} + \infty = [0 + \infty,\ \infty + \infty]_{in} = [\infty, \infty]_{in} = \infty$. $\quad\square$

**Example 6.2.** $\;\tfrac{\infty}{\infty} + \infty = \infty.$

*Derivation.*

- $\frac{\infty}{\infty} = [0, \infty]_{in}$ (see [Section 6.3](#63-classical-indeterminate-forms-and-their-interval-representations));
- $[0, \infty]_{in} + \infty = [\infty, \infty]_{in} = \infty$. $\quad\square$

## 6.3 Classical Indeterminate Forms and Their Interval Representations

The following table summarizes the principal indeterminate forms together with their interval-number representations and limit-based justifications.

| Form | Interval | Justification |
|------|----------|---------------|
| $0 \cdot \infty$ | $[0, \infty]_{in}$ | [Rule I](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) |
| $0 \cdot (-\infty)$ | $[-\infty, 0]_{in}$ | [Rule II](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) |
| $\dfrac{0}{0}$ | $[-\infty, \infty]_{in}$ | $\lim_{x \to 0^{+}}\tfrac{x}{x^2} = +\infty$ vs.\ $\lim_{x \to 0^{-}}\tfrac{x}{x^2} = -\infty$; parametric $a_n = c/n,\ b_n = 1/n$ gives $a_n/b_n = c$ for any $c \in \mathbb{R}$ |
| $\infty - \infty$ | $[-\infty, \infty]_{in}$ | $\lim(n - n^2) = -\infty$ vs.\ $\lim(n^2 - n) = \infty$ |
| $\dfrac{\infty}{\infty}$ | $[0, \infty]_{in}$ | $\lim\tfrac{n}{n^2} = 0$ vs.\ $\lim\tfrac{n^2}{n} = \infty$ |
| $0^0$ | $[0, \infty]_{in}$ | three-sequence argument ([Section 4.7](04_operations.md#47-exponentiation)) |
| $1^\infty$ | $[0, \infty]_{in}$ | $(1 - \tfrac{1}{\sqrt{n}})^{n^2} \to 0$, $(1 + \tfrac{1}{n})^{n^2} \to \infty$ |
| $\infty^0$ | $[0, \infty]_{in}$ | $n^{-1/\ln\ln n} \to 0$, $n^{\,1/\ln\ln n} \to \infty$ |

These representations are consistent with the definitions in [Section 4](04_operations.md): for each form, evaluating it via the relevant Section-4 rule reproduces the listed interval. A global soundness theorem covering all composite expressions is not claimed; non-associativity of multiplication ([Section 5.2](05_algebraic_structure.md#52-failure-of-associativity)) and convex-hull approximation in the reciprocal ([Section 4.4](04_operations.md#44-reciprocal)) preclude such a claim in full generality.

## 6.4 Worked Limits Justifying Selected Intervals

For $\dfrac{0}{0} = [-\infty, \infty]_{in}$:

$$\lim_{x \to 0^{+}}\frac{x}{x^{2}} = +\infty, \qquad \lim_{x \to 0^{-}}\frac{x}{x^{2}} = -\infty.$$

For any finite $c \in \mathbb{R}$, the parametric sequences $a_n = c/n$, $b_n = 1/n$ satisfy $a_n/b_n = c$ for all $n$, demonstrating that every value of $\mathbb{R}$ is attainable.

For $1^\infty = [0, \infty]_{in}$:

$$\lim_{n \to \infty}\Big(1 - \tfrac{1}{\sqrt{n}}\Big)^{n^2} = 0, \qquad \lim_{n \to \infty}\Big(1 + \tfrac{1}{n}\Big)^{n^2} = \infty.$$

For $\infty^0 = [0, \infty]_{in}$:

$$\lim_{n \to \infty} n^{-\,1/\ln\ln n} = 0, \qquad \lim_{n \to \infty} n^{\,1/\ln\ln n} = \infty.$$

---

[← Previous: Algebraic Structure](05_algebraic_structure.md) | [Back to Contents](../README.md) | [Next: Conclusion →](07_conclusion.md)
