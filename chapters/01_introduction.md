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

Standard limit analysis confirms the difficulty. Two sequences both fitting the symbolic form $0 \cdot \infty$ produce different limits:

$$a_n = \tfrac{1}{n},\ b_n = n^2 \quad \Rightarrow \quad a_n b_n = n \to \infty,$$

$$a_n = \tfrac{1}{n^2},\ b_n = n \quad \Rightarrow \quad a_n b_n = \tfrac{1}{n} \to 0.$$

A single real-valued limit cannot capture both behaviours, yet both arise from the same symbolic form. This motivates a representation in which $0 \cdot \infty$ stands for the *range* of attainable limit values rather than a single number.

## 1.3 Proposed Resolution

This work proposes a resolution by introducing **interval numbers** as formal mathematical objects. Rather than treating $`0 \cdot \infty`$ as undefined, it is represented as $`[0, \infty]_{in}`$—an interval whose endpoints span the limits realizable by directional sequences $`a_n \cdot b_n`$ with $`a_n \to 0^{+}`$ and $`b_n \to +\infty`$ (see [Section 3.4](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) for the precise convention). This approach makes the basic arithmetic operations (addition, subtraction, multiplication, reciprocal, division, absolute value) total on $`\mathcal{I}`$, and provides an exponentiation operation defined on a precisely stated admissible domain ([Section 4.7](04_operations.md#47-exponentiation)).

## 1.4 Contributions

The main contributions of this work are:

1. A formal definition of **interval numbers** as a mathematical structure for representing indeterminate forms.
2. A complete specification of the basic arithmetic operations (total on $\mathcal{I}$) and an exponentiation operation on a stated admissible domain, all following the interval-arithmetic principle of taking hulls of attainable values, extended by an explicit value map for indeterminate endpoint products.
3. A proof that interval numbers form a unital magma under multiplication, with a concrete counterexample demonstrating non-associativity.
4. Demonstration of internal consistency through limit-based justifications of interval bounds.
5. A functional C++ reference implementation accompanied by a unit test suite.

**Scope and main results.** To distinguish what is *proven* from what is *assigned by convention* or *illustrated by example*, this paper takes the following positions:

- **Definitions and conventions** ([Sections 3](03_interval_numbers.md) and [4](04_operations.md)): the foundation rules I and II ([Section 3.4](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms)), the value maps $\mathcal{V}$ and $\mathcal{V}^{\wedge}$ ([Sections 4.1](04_operations.md#41-multiplication) and [4.7](04_operations.md#47-exponentiation)), and the convex-hull convention for the reciprocal of a zero-spanning interval ([Section 4.4](04_operations.md#44-reciprocal)) are formal choices, not derivations.
- **Proven results**: closure of $(\mathcal{I}, \cdot)$ and existence of the two-sided identity $`[1,1]_{in}`$ ([Theorem 5.1](05_algebraic_structure.md#51-closure-under-multiplication)); failure of associativity ([Proposition 5.2](05_algebraic_structure.md#52-failure-of-associativity)).
- **Example-based limit witnesses** ([Sections 3.6](03_interval_numbers.md#36-justification-for-rules-i-and-ii) and [6.3–6.4](06_applications.md#63-classical-indeterminate-forms-and-their-interval-representations)): explicit and parametric directional sequences exhibiting representative endpoint and interior values for each foundation rule and classical indeterminate form.
- **Implementation conformance**: the C++ reference implementation matches the stated definitions on the cases exercised by the unit tests ([`test/README.md`](../test/README.md)); it is a conformance artefact, not independent evidence for the mathematical claims.
- **Not claimed**: a global soundness or optimality (tightness) theorem covering all composite expressions; full distributivity; closure of exponentiation outside its admissible domain.

## 1.5 Organization

The remainder of the document is organized as follows. [Section 2](02_related_work.md) reviews related work in interval arithmetic, extended reals, and indeterminate forms. [Section 3](03_interval_numbers.md) establishes the formal definition and foundation rules. [Section 4](04_operations.md) defines the algebraic operations. [Section 5](05_algebraic_structure.md) discusses the algebraic structure. [Section 6](06_applications.md) presents worked examples. [Section 7](07_conclusion.md) concludes with future research directions. A reference C++ implementation accompanies the paper and is documented in [`test/README.md`](../test/README.md).

---

[← Back to Contents](../README.md) | [Next: Related Work →](02_related_work.md)
