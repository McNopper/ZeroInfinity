# 5. Algebraic Structure

[← Previous: Operations](04_operations.md) | [Back to Contents](../README.md) | [Next: Applications →](06_applications.md)

---

This section examines the algebraic structure induced by interval-number operations, with emphasis on which classical axioms hold and which fail.

## 5.1 Closure under Multiplication

**Theorem 5.1 (Closure).** *The set of interval numbers $\mathcal{I}$, equipped with the multiplication operation of [Definition 4.1](04_operations.md#41-multiplication), forms a* **Magma** *[[5](09_references.md)].*

**Proof.** A Magma is a set with a single binary operation that is closed [[4, 5](09_references.md)]. Let $I = [x_0, x_1]_{in}$ and $J = [y_0, y_1]_{in}$ be interval numbers, with $x_0, x_1, y_0, y_1 \in \overline{\mathbb{R}}$. Each of the four products $P_{ij} := x_i \cdot y_j$ for $i, j \in \{0, 1\}$ is either:

(a) a defined element of $\overline{\mathbb{R}}$, or
(b) the indeterminate form $0 \cdot (\pm\infty)$, treated by [Rule I](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) or [Rule II](03_interval_numbers.md#34-foundation-rules-for-indeterminate-forms) as a finite endpoint set $\{0, \pm\infty\}$.

In both cases the value map $\mathcal{V}(P_{ij})$ is a non-empty finite subset of $\overline{\mathbb{R}}$. Hence the candidate set $\mathcal{C}(I, J) = \bigcup_{i,j} \mathcal{V}(P_{ij})$ is a non-empty finite subset of $\overline{\mathbb{R}}$, and its minimum and maximum are well-defined. Therefore $I \cdot J = [\min \mathcal{C},\ \max \mathcal{C}]_{in} \in \mathcal{I}$, establishing closure. $\blacksquare$

## 5.2 Failure of Associativity

**Proposition 5.2 (Non-associativity).** *Multiplication on $\mathcal{I}$ is not associative.*

**Counterexample.** Let $a = -1$, $b = 0$, $c = -\infty$ (each viewed as a point interval). Then:

$$b \cdot c \;=\; 0 \cdot (-\infty) \;=\; [-\infty, 0]_{in} \quad \text{(Rule II)},$$

$$a \cdot (b \cdot c) \;=\; -1 \cdot [-\infty, 0]_{in} \;=\; [0, \infty]_{in},$$

while

$$a \cdot b \;=\; -1 \cdot 0 \;=\; 0,$$

$$(a \cdot b) \cdot c \;=\; 0 \cdot (-\infty) \;=\; [-\infty, 0]_{in} \quad \text{(Rule II)}.$$

Hence $a \cdot (b \cdot c) = [0, \infty]_{in} \ne [-\infty, 0]_{in} = (a \cdot b) \cdot c$. $\blacksquare$

This counterexample is verified in the implementation by the test `MultiplicationNotAssociative` ([`test/src/main.cpp`](../test/src/main.cpp)).

The non-associativity has a precise interpretation: the bracketing of an expression determines *when* indeterminate forms are resolved into intervals, and once an interval has been formed, subsequent multiplication propagates uncertainty rather than collapsing it. This is structurally analogous to the well-known non-associativity of classical interval arithmetic in the presence of zero-spanning operands [[6](09_references.md)].

## 5.3 Limitations of the Structure

Beyond the Magma property, the following stronger algebraic axioms do *not* hold in general:

| Axiom | Status | Remark |
|-------|--------|--------|
| Closure | **holds** | [Theorem 5.1](#51-closure-under-multiplication) |
| Associativity | **fails** | [Proposition 5.2](#52-failure-of-associativity); test `MultiplicationNotAssociative` |
| Multiplicative identity | restricted | $[1, 1]_{in}$ acts as identity on point intervals; on general $I$, $[1, 1]_{in} \cdot I = I$ holds when no $P_{ij}$ is indeterminate |
| Multiplicative inverses | fails | intervals containing $0$ admit no inverse in $\mathcal{I}$ |
| Distributivity over $+$ | fails | inherited from classical interval arithmetic [[6](09_references.md)]; only sub-distributivity holds |

The Magma property is therefore the strongest classical axiom that holds universally on $\mathcal{I}$. Identifying maximal sub-structures on which stronger axioms recover (e.g., associativity on point-interval subsemigroups, monoidal behaviour on intervals bounded away from zero) is left to future work; see [Section 8](08_conclusion.md).

## 5.4 Significance

Despite the limitations of [Section 5.3](#53-limitations-of-the-structure), the Magma property is sufficient to support consistent algebraic manipulation of indeterminate forms within bracketed expressions, as demonstrated in [Section 6](06_applications.md). Crucially, the framework makes the failure of associativity *visible and meaningful* rather than hiding it behind an undefined symbol: bracketing now corresponds to a specific algebraic choice with computable consequences.

---

[← Previous: Operations](04_operations.md) | [Back to Contents](../README.md) | [Next: Applications →](06_applications.md)
