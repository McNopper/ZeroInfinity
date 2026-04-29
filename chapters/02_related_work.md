# 2. Related Work

[← Previous: Introduction](01_introduction.md) | [Back to Contents](../README.md) | [Next: Interval Numbers →](03_interval_numbers.md)

---

This section situates the contribution within three relevant research strands: interval arithmetic, extended real numbers, and the classical theory of indeterminate forms.

## 2.1 Interval Arithmetic

Classical interval arithmetic, formalized by Moore [[6](08_references.md)], provides methods for computing with sets of real numbers represented as closed intervals. The fundamental motivation—controlling rounding error in numerical computation—differs from the focus of the present work on algebraic closure of indeterminate forms. However, the operations on interval numbers introduced here follow the same underlying principle: operations on intervals are defined by taking extrema over all possible combinations of operand endpoints.

Standard interval arithmetic does not address indeterminate forms directly; it avoids division by zero, for example, by requiring intervals to not contain zero. The present work extends this framework to actively address cases in which standard arithmetic fails.

## 2.2 Extended Real Numbers

The extended real line $\overline{\mathbb{R}} = \mathbb{R} \cup \{-\infty, +\infty\}$, originating in the work of Riemann and formalized by Hausdorff and others [[2, 3](08_references.md)], adjoins $\pm\infty$ to $\mathbb{R}$. While $\overline{\mathbb{R}}$ provides a topological completion, algebraic operations remain partially undefined: $0 \cdot \infty$, $\infty - \infty$, and similar expressions lack standard interpretations.

Measure-theoretic conventions [[2](08_references.md)] sometimes assign values to such forms in specific contexts (e.g., $0 \cdot \infty = 0$ in certain measure-theoretic constructions), but these are context-dependent and do not constitute a unified algebraic theory.

## 2.3 Indeterminate Forms

The classification of indeterminate forms [[1](08_references.md)] has been studied extensively in calculus and real analysis. The present work does not dispute the classical categorization; rather, it provides a unified algebraic framework for manipulating these forms once they are expressed as interval numbers.

## 2.4 Positioning of This Work

The novelty of the contribution lies in combining the operational rigor of interval arithmetic with the topological scope of the extended real line, yielding a formalism in which indeterminate forms are first-class algebraic objects. This unification appears, to the author's knowledge, not to have been treated as a self-contained framework in the existing literature.

---

[← Previous: Introduction](01_introduction.md) | [Back to Contents](../README.md) | [Next: Interval Numbers →](03_interval_numbers.md)
