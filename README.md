# Solution for indeterminate forms using interval numbers

*by Norbert Nopper*

## Credits

Thanks to Eric Lengyel for asking the initial right questions.

Thanks a lot, to my family and their patience having me as a 🤓.

Thanks to 🤖, for cross checking the math, wording and implementation.

## Note

The math formulas are encoded using [MathJax](https://www.mathjax.org/).  
If the rendering of the math formuls are not properly done, please use another editor/viewer like [Visual Studio Code](https://code.visualstudio.com/).

## Motivation

The expressions $0 \cdot ∞$ and implicitly $0 \cdot -∞$ are indeterminate forms [[1](#1-indeterminate-form)]. It is not possible to perform algebraic operations on these expressions like $-1 \cdot (0 \cdot -∞)$.  
However, compared to $x = -1 \cdot -x$, intuitively the following equation should be true: 

$$0 \cdot ∞ = -1 \cdot (0 \cdot -∞)$$

### Problem

A naive approach like $-1 \cdot (0 \cdot -∞) = (-1 \cdot 0) \cdot -∞$ with mathematical limits results again in $0 \cdot -∞$ even when the associative law is allowed.

#### Investigation

Existing required mathematical limits for the above assumption:

$\lim_{n\to\infty}\sqrt[n]{n}=1$  
$\lim_{n\to\infty}\frac{1}{n}=0$  

Assume the usage of the associative law is allowed:

$\lim_{n\to\infty}-\sqrt[n]{n} \cdot \lim_{n\to\infty}\frac{1}{n} = \lim_{n\to\infty}\left(-\sqrt[n]{n} \cdot \frac{1}{n}\right) = \lim_{n\to\infty}\left(-\frac{\sqrt[n]{n}}{n}\right)$

The result is again 0 and does not provide the expected result.

## New interval number

### Assumption

In the case of the given two indeterminate forms, the result could be **any** number. However, the resulting number can be enclosed in an interval.  

#### Using extended real numbers  

Using the extended real number system $\overline {\mathbb R}$ [[2](#2-extended-real-number-line), [3](#3-affinely-extended-real-numbers)], the intervals $[0, ∞]$ and $[-∞, 0]$ are allowed.

![](illustrations/visual_interval_extended.png)

### Definition

Since an indeterminate form can evaluate to any value within a specific range, we introduce the interval number *in* to represent all possible values in that range:

$[x_0, x_1]in := \{ x \in \overline {\mathbb R} \mid x_0 \le x \le x_1 \}$

**Sign convention (for limits)**  
In the following, $\infty$ means positive infinity. Negative infinity is written as $-\infty$.

The indeterminate form of $0 \cdot \infty$ can be expressed as the first rule:

***Rule I***  
$0 \cdot \infty = [0, \infty]in$

Similarly, the expression for the indeterminate form of $0 \cdot (-\infty)$ is the second rule:

***Rule II***  
$0 \cdot (-\infty) = [-\infty, 0]in$

### Deduction

|                               | Operation or rule                    |
|-------------------------------|--------------------------------------|
| $-1 \cdot (0 \cdot (-\infty))$       | ***Rule II***                        |
| $-1 \cdot [-\infty, 0]in$            | Multiplication for interval number   |
| $[-1 \cdot (-\infty), -1 \cdot 0]in$ | Operation in $\overline {\mathbb R}$ |
| $[0, \infty]in$                      | ***Rule I***                         |
| $0 \cdot \infty$                     |                                      |

Regarding the algebraic structure [[4](#4-algebraic-structure)], only the required multiplication for the given rules is investigated.

The algebraic structure of the interval numbers is at least a Magma [[5](#5-magma-algebra)], as all multiplications in $\overline {\mathbb R}$ including ***Rule I*** and ***Rule II*** are defined.

### Interval number operations

These are the given mathematical operations, following standard interval arithmetic [[6](#6-interval-arithmetic)].

#### Multiplication

$[x_0, x_1]in \cdot [y_0, y_1]in := [\min(x_0 \cdot y_0, x_0 \cdot y_1, x_1 \cdot y_0, x_1 \cdot y_1), \max(x_0 \cdot y_0, x_0 \cdot y_1, x_1 \cdot y_0, x_1 \cdot y_1)]in$

For the indeterminate forms $0 \cdot \infty = [0, \infty]in$ (***Rule I***) and $0 \cdot (-\infty) = [-\infty, 0]in$ (***Rule II***).

#### Addition

$[x_0, x_1]in + [y_0, y_1]in := [x_0 + y_0, x_1 + y_1]in$

For the indeterminate form $\infty + (-\infty)$ or $(-\infty) + \infty$, the result is $[-\infty, \infty]in$.

#### Subtraction

$[x_0, x_1]in - [y_0, y_1]in := [x_0 - y_1, x_1 - y_0]in$

For the indeterminate form $\infty - \infty$ or $(-\infty) - (-\infty)$, the result is $[-\infty, \infty]in$.

#### Division

$[x_0, x_1]in \div [y_0, y_1]in := [x_0, x_1]in \cdot [\frac{1}{y_1}, \frac{1}{y_0}]in$

For the indeterminate form $\frac{0}{0}$, the result is $[-\infty, \infty]in$.

#### Absolute Value

$|[x_0, x_1]|in := [\min(|x_0|, |x_1|), \max(|x_0|, |x_1|)]in$ if $x_0 \cdot x_1 \ge 0$

$|[x_0, x_1]|in := [0, \max(|x_0|, |x_1|)]in$ if $x_0 \cdot x_1 < 0$

The absolute value depends on whether the interval contains zero (when $x_0 \cdot x_1 < 0$).

#### Power

$[x_0, x_1]in^{[y_0, y_1]in} := [\min(x_0^{y_0}, x_0^{y_1}, x_1^{y_0}, x_1^{y_1}), \max(x_0^{y_0}, x_0^{y_1}, x_1^{y_0}, x_1^{y_1})]in$

This general form handles both interval and scalar exponents (scalar $n$ is treated as $[n, n]in$).

For the indeterminate forms involving exponentiation:
- $0^0 = [0, ∞]in$
- $1^∞ = [0, ∞]in$
- $∞^0 = [0, ∞]in$

Special considerations:
- For even integer exponents with intervals containing zero: result includes $0$
- For negative exponents with zero in base: result approaches infinity
- Interval-to-interval power computes all combinations of base and exponent endpoints to find the result range

## Implementation

In the [test](test/) folder is a C++ implementation of the interval number and the unit tests.

## Indeterminate forms as interval numbers

This section demonstrates how various indeterminate forms can be expressed as interval numbers, with limit examples justifying the interval bounds.

### Forms involving zero and infinity

The indeterminate form $\frac{0}{0}$ is undefined in $\overline {\mathbb R}$, but with interval numbers it can be expressed as:

$\frac{0}{0} = [-∞, ∞]in$

Because the limits of the given example formulas result in $∞$ and $-∞$:

$\lim_{n\to0^+}\frac{n}{n^2} = ∞$

$\lim_{n\to0^-}\frac{n}{n^2} = -∞$

---

The indeterminate form $∞ - ∞$ can be expressed as:

$∞ - ∞ = [-∞, ∞]in$

Because different limit approaches yield different results:

$\lim_{n\to\infty}(n - n^2) = -∞$

$\lim_{n\to\infty}(n^2 - n) = ∞$

---

The indeterminate form $\frac{∞}{∞}$ can be expressed as:

$\frac{∞}{∞} = [0, ∞]in$

Because different limit approaches yield different results:

$\lim_{n\to\infty}\frac{n}{n^2} = 0$

$\lim_{n\to\infty}\frac{n^2}{n} = ∞$

### Forms involving exponentiation

The indeterminate form $0^0$ can be expressed as:

$0^0 = [0, ∞]in$

$\lim_{n\to\infty}\left(\frac{1}{n}\right)^{\frac{1}{\sqrt{\ln(n)}}} = 0$

$\lim_{n\to\infty}\left(\frac{1}{n}\right)^{\frac{1}{\ln(n)}} = e^{-1}$

$\lim_{n\to\infty}\left(\frac{1}{n}\right)^{-\frac{1}{\sqrt{\ln(n)}}} = ∞$

---

The indeterminate form $1^∞$ can be expressed as:

$1^∞ = [0, ∞]in$

$\lim_{n\to\infty}(1 - \frac{1}{\sqrt{n}})^{n^2} = 0$

$\lim_{n\to\infty}(1 + \frac{1}{n})^{n^2} = ∞$

---

The indeterminate form $∞^0$ can be expressed as:

$∞^0 = [0, ∞]in$

$\lim_{n\to\infty}n^{-\frac{1}{\ln(\ln(n))}} = 0$

$\lim_{n\to\infty}n^{\frac{1}{\ln(\ln(n))}} = ∞$

## Some equations from indeterminate forms resulting back in a non-indeterminate form

$|\frac{0}{0}|+ ∞ = ∞$

Because:

$\frac{0}{0} = [-∞, ∞]in$

$|-∞, ∞|in = [0, ∞]in$

$[0, ∞]in + ∞ = [0 + ∞, ∞ + ∞] = [∞, ∞]in = ∞$

---

$(\frac{∞}{∞}) + ∞ = ∞$

Because:

$\frac{∞}{∞} = [0, ∞]in$

$[0, ∞]in + ∞ = [0 + ∞, ∞ + ∞] = [∞, ∞]in = ∞$

## Conclusion

Using this approach, other indeterminate forms could be expressed as intervals and solved in equations as well. Especially the usage and current definition in measure theory should be further evaluated [[7](#7-extended-real-numbers)].

For now, it is shown that the algebraic structure of the interval number is a Magma. However, including the other mathematical operations, the algebraic structure could be further investigated.

Furthermore, other intervals for indeterminate forms could be estimated and defined.

## References

##### 1 Indeterminate form
https://en.wikipedia.org/wiki/Indeterminate_form

##### 2 Extended real number line
https://en.wikipedia.org/wiki/Extended_real_number_line

##### 3 Affinely Extended Real Numbers
https://mathworld.wolfram.com/AffinelyExtendedRealNumbers.html

##### 4 Algebraic structure
https://en.wikipedia.org/wiki/Algebraic_structure

##### 5 Magma (algebra)
https://en.wikipedia.org/wiki/Magma_(algebra)

##### 6 Interval arithmetic
https://en.wikipedia.org/wiki/Interval_arithmetic

##### 7 Extended real numbers
https://planetmath.org/extendedrealnumbers
