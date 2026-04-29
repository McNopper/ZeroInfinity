# 2. Related Work

[← Previous: Introduction](01_introduction.md) | [Back to Contents](../README.md) | [Next: Interval Numbers →](03_interval_numbers.md)

---

This section situates the contribution within three relevant research strands: interval arithmetic, extended real numbers, and the classical theory of indeterminate forms.

## 2.1 Interval Arithmetic

Classical interval arithmetic, formalized by Moore [[6](08_references.md)] and surveyed in modern references [[7, 8](08_references.md)] including the IEEE 1788-2015 standard [[9](08_references.md)], provides methods for computing with sets of real numbers represented as closed intervals. The fundamental motivation—controlling rounding error in numerical computation—differs from the focus of the present work on algebraic closure of indeterminate forms. However, the operations on interval numbers introduced here follow the same underlying principle: for the basic arithmetic operations, the definitions take hulls of attainable endpoint values; for exponentiation, a full image-set hull is required ([Section 4.7](04_operations.md#47-exponentiation)) because endpoint-only formulas fail when the base interval crosses zero with an even-integer exponent.

Standard interval arithmetic does not address indeterminate forms directly; it avoids division by zero, for example, by requiring intervals to not contain zero. The present work extends this framework to actively address cases in which standard arithmetic fails.

Several extensions of classical interval arithmetic relax this restriction. *Kaucher (modal) interval arithmetic* [[10](08_references.md)] admits improper intervals $[a, b]$ with $a > b$ and yields a group structure under addition; *generalized / extended interval arithmetic* [[11](08_references.md)] allows division by zero-containing intervals via unbounded or split results; the algebraic construction of *wheels* [[12](08_references.md)] adds a totalized reciprocal at the cost of weakening the field axioms, and the related construction of *meadows* [[13](08_references.md)] provides a totalized inverse in a field-like setting. The present framework differs from these in two respects: (i) it works on the *extended* real line $\overline{\mathbb{R}}$ rather than $\mathbb{R}$, so $\pm\infty$ are first-class endpoints; and (ii) its primary aim is the algebraic representation of classical indeterminate forms, not the totalization of division per se.

## 2.2 Extended Real Numbers

The extended real line $\overline{\mathbb{R}} = \mathbb{R} \cup \lbrace -\infty, +\infty\rbrace$, originating in the work of Riemann and formalized by Hausdorff and others [[2, 3](08_references.md)], adjoins $\pm\infty$ to $\mathbb{R}$. While $\overline{\mathbb{R}}$ provides a topological completion, algebraic operations remain partially undefined: $0 \cdot \infty$, $\infty - \infty$, and similar expressions lack standard interpretations.

Measure-theoretic conventions [[2](08_references.md)] sometimes assign values to such forms in specific contexts (e.g., $0 \cdot \infty = 0$ in certain measure-theoretic constructions), but these are context-dependent and do not constitute a unified algebraic theory.

## 2.3 Indeterminate Forms

The classification of indeterminate forms [[1](08_references.md)] has been studied extensively in calculus and real analysis. The present work does not dispute the classical categorization; rather, it provides a unified algebraic framework for manipulating these forms once they are expressed as interval numbers.

## 2.4 Positioning of This Work

The novelty of the contribution lies in combining the operational rigor of interval arithmetic with the topological scope of the extended real line, yielding a formalism in which indeterminate forms are first-class algebraic objects. To the author's knowledge, the specific combination — extended-real endpoints, an explicit value map for indeterminate products, and a worked algebraic-structure analysis tailored to indeterminate forms — has not previously been treated as a self-contained framework, although several of its individual ingredients are present in the works cited above.

---

[← Previous: Introduction](01_introduction.md) | [Back to Contents](../README.md) | [Next: Interval Numbers →](03_interval_numbers.md)
