# 7. Conclusion and Future Work

[← Previous: Applications](06_applications.md) | [Back to Contents](../README.md) | [Next: References →](08_references.md)

---

## 7.1 Summary

This work has introduced **interval numbers** as a formal algebraic framework for representing and manipulating indeterminate forms. By embedding indeterminate expressions into closed intervals of the extended real line $\overline{\mathbb{R}}$, the basic arithmetic operations (addition, subtraction, multiplication, reciprocal, division, absolute value) are made total on $\mathcal{I}$, and exponentiation is defined on a precisely stated admissible domain. The induced multiplicative structure is a **unital magma**—closed, with two-sided identity $[1,1]_{in}$, but neither associative nor monoidal—and supports consistent algebraic manipulation while preserving the intuitive interpretation of indeterminate forms as ranges of admissible limit values. A C++ reference implementation accompanied by a unit test suite exercises the framework computationally on representative cases; build and verification details are documented in [`test/README.md`](../test/README.md).

## 7.2 Limitations and Open Questions

To support an honest appraisal, the principal limitations of the framework are stated explicitly:

1. **Multiplication is not associative.** [Proposition 5.2](05_algebraic_structure.md#52-failure-of-associativity) exhibits a concrete counterexample. Consequently, the result of an interval-number expression depends on its bracketing, and the framework only enjoys unital-magma structure—not semigroup, monoid, or group structure—on $\mathcal{I}$ as a whole.

2. **Loss of tightness for division by zero-spanning intervals.** When the divisor strictly contains zero, the natural reciprocal is a union of two intervals; to retain closure within $\mathcal{I}$, the framework returns $[-\infty, \infty]_{in}$, which is sound but not tight ([Section 4.4](04_operations.md#44-reciprocal)).

3. **Convention behind $`\tfrac{0}{0}`$.** The reciprocal of the point interval $`[0,0]_{in}`$ is assigned $`[-\infty, \infty]_{in}`$ by the convex-hull convention of [Definition 4.4](04_operations.md#44-reciprocal); the value of $`\tfrac{0}{0}`$ then follows internally from [Definition 4.5](04_operations.md#45-division). The choice of $`[-\infty, \infty]_{in}`$ for the reciprocal of $`[0,0]_{in}`$ is a convention motivated by directional limits, not an internal derivation.

4. **No proven distributivity.** Sub-distributivity of multiplication over addition holds in classical interval arithmetic [[6](08_references.md)]; full distributivity does not transfer, and a precise statement for $\mathcal{I}$ is not given here.

5. **Choice of limit witnesses.** The interval assigned to each indeterminate form is justified by exhibiting limit sequences whose values reach (or approach) the endpoints. A proof that the chosen interval is *optimal*—i.e., that no admissible value lies strictly outside it—is informal and rests on standard real-analytic intuition rather than a fully formal argument.

6. **Floating-point realization.** Any numerical realization (such as the reference implementation) inherits the rounding behaviour of its arithmetic substrate. The mathematical claims are stated in $\overline{\mathbb{R}}$; floating-point realizations are approximate.

These limitations delineate the scope of the present contribution and motivate the directions outlined in [Section 7.3](#73-future-directions).

## 7.3 Future Directions

The interval-number framework opens several avenues for further investigation:

1. **Richer algebraic structure.** Investigate whether interval numbers exhibit additional structure (associativity, distributivity, identities, inverses) under suitable restrictions—for example, on intervals not containing zero, or on the set of point intervals.

2. **Measure-theoretic integration.** Reconcile interval-number operations with measure-theoretic conventions for handling indeterminate forms [[2](08_references.md)], where context-specific conventions such as $0 \cdot \infty = 0$ are common.

3. **Applications.** Explore applications in:
   - numerical analysis (controlled treatment of overflow and underflow),
   - complex analysis (extension to complex-valued interval numbers),
   - probability and statistics (representing imprecise probabilities).

4. **Extended operations.** Define and characterize additional operations on interval numbers, including:
   - logarithm and exponential,
   - trigonometric and hyperbolic functions,
   - transcendental functions and their inverses.

5. **Categorical perspective.** Examine interval numbers from a categorical or topos-theoretic viewpoint to uncover deeper structural properties and connections with related frameworks (fuzzy sets, rough sets, interval-valued probabilities).

6. **Formal verification.** Mechanize the theory in a proof assistant (Coq, Lean, Isabelle) to obtain machine-checked guarantees of soundness for all operations and identities.

7. **Estimation of additional indeterminate intervals.** Other indeterminate forms—possibly arising in specific application domains—could be assigned interval representations through the same limit-based justification methodology employed here.

## 7.4 Closing Remark

While the immediate significance of the framework remains theoretical, it offers a mathematically principled approach to a long-standing problem in real analysis. The unification of interval arithmetic and extended-real semantics provides a foundation upon which further algebraic, computational, and applied investigations can be built.

---

[← Previous: Applications](06_applications.md) | [Back to Contents](../README.md) | [Next: References →](08_references.md)
