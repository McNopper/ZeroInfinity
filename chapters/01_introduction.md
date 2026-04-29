# 1. Introduction

[← Back to Contents](../README.md) | [Next: Related Work →](02_related_work.md)

---

The treatment of indeterminate forms represents a foundational challenge in mathematical analysis. Within the classical extended real number system $\overline{\mathbb{R}}$, certain expressions—such as $0 \cdot \infty$, $\infty - \infty$, and $\frac{0}{0}$—cannot be assigned definite values. In standard practice, such expressions are left undefined or handled through case-by-case limit analysis. However, this approach lacks generality: different sequences approaching an indeterminate form may exhibit different limiting behavior, yet no unified algebraic framework exists for treating them.

## 1.1 Motivating Example

Consider the intuitive observation that if $x = -1 \cdot (-x)$ holds in standard arithmetic, one might expect the following identity to remain valid under appropriate extensions:

$$0 \cdot \infty = -1 \cdot (0 \cdot (-\infty)).$$

A naive algebraic manipulation under the associative law yields:

$$-1 \cdot (0 \cdot (-\infty)) = (-1 \cdot 0) \cdot (-\infty) = 0 \cdot (-\infty),$$

which provides no new information. The fundamental obstacle is that indeterminate forms do not admit standard algebraic treatment.

## 1.2 Limit-Based Investigation

Standard limit analysis confirms the difficulty. Consider the limits:

$$\lim_{n\to\infty}\sqrt[n]{n} = 1, \qquad \lim_{n\to\infty}\frac{1}{n} = 0.$$

Assuming associativity is permitted:

$$\lim_{n\to\infty}\left(-\sqrt[n]{n}\right) \cdot \lim_{n\to\infty}\frac{1}{n} = \lim_{n\to\infty}\left(-\frac{\sqrt[n]{n}}{n}\right) = 0,$$

which still does not produce the expected behavior of $0 \cdot \infty$.

## 1.3 Proposed Resolution

This work proposes a resolution by introducing **interval numbers** as formal mathematical objects. Rather than treating $0 \cdot \infty$ as undefined, it is represented as $[0, \infty]_{in}$—an interval containing all possible values that limiting sequences of the form $a_n \cdot b_n$ (with $a_n \to 0$ and $b_n \to \infty$) can approach. This approach achieves algebraic closure: operations on indeterminate forms yield well-defined results within the extended interval framework.

## 1.4 Contributions

The main contributions of this work are:

1. A formal definition of **interval numbers** as a mathematical structure for representing indeterminate forms.
2. A complete specification of arithmetic operations on interval numbers, following standard interval arithmetic conventions.
3. A proof sketch that interval numbers form a Magma under multiplication, establishing a non-trivial algebraic structure.
4. Demonstration of internal consistency through limit-based justifications of interval bounds.
5. A functional C++ reference implementation accompanied by a unit test suite.

## 1.5 Organization

The remainder of the document is organized as follows. [Section 2](02_related_work.md) reviews related work in interval arithmetic, extended reals, and indeterminate forms. [Section 3](03_interval_numbers.md) establishes the formal definition and foundation rules. [Section 4](04_operations.md) defines the algebraic operations. [Section 5](05_algebraic_structure.md) discusses the algebraic structure. [Section 6](06_applications.md) presents worked examples. [Section 7](07_implementation.md) describes the implementation. [Section 8](08_conclusion.md) concludes with future research directions.

---

[← Back to Contents](../README.md) | [Next: Related Work →](02_related_work.md)
