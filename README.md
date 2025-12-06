# Solution for indeterminate forms using interval numbers

*by Norbert Nopper*

## Credits

Thanks to Eric Lengyel for asking the initial right questions.

Thanks a lot, to my family and their patience having me as a 🤓.

## Note

The math formulas are encoded using [MathJax](https://www.mathjax.org/). However, the decoding and rendering are not properly done in GitHub.  
For properly displaying the formulas, please use another editor like [Visual Studio Code](https://code.visualstudio.com/).

## Motivation

The expressions $0 \cdot \infty$ and implicitly $0 \cdot -\infty$ are indeterminate forms [[1](#1-indeterminate-form)]. It is not possible to do any calculus on these expressions like $-1 \cdot (0 \cdot -\infty)$.  
However, compared to $x = -1 \cdot -x$, intuitively the following equation should be true: 

$$0 \cdot \infty = -1 \cdot (0 \cdot -\infty)$$

### Problem

A naive approach like $-1 \cdot (0 \cdot -\infty) = (-1 \cdot 0) \cdot -\infty$ with math limits results again in $0 \cdot -\infty$ even when the associative law is allowed.

#### Investigation

Existing required math limits for above assumption:

$\lim_{n\to\infty}\sqrt[n]{n}=1$  
$\lim_{n\to\infty}\frac{1}{n}=0$  

Assume the usage of the associative law is allowed:

$\lim_{n\to\infty}-\sqrt[n]{n} \cdot \lim_{n\to\infty}\frac{1}{n} = \lim_{n\to\infty}-\sqrt[n]{n} \cdot \frac{1}{n} = \lim_{n\to\infty}\frac{-1}{n}$

The result is again 0 and does not provide the expected result.

## New interval number

### Assumption

In the case of the given two indeterminate forms, the result could be **any** number. However, the resulting number can be enclosed in an interval.  

#### Using extended real numbers  

Using the extended real number system $\overline {\mathbb R}$ [[2](#2-extended-real-number-line)], the intervals $[0, \infty]$ and $[-\infty, 0]$ are allowed.

![](illustrations/visual_interval_extended.png)

#### Enclosing the result in an interval

The following is given:

$a, b \in \overline {\mathbb R} \land a \le b$

Interval, where the result for $a \cdot b$ is enclosed in the interval: 

$[x_0, x_1] = \{ x_0 = a \cdot \beta | \beta \in [a, b[ \land x_1 = \alpha \cdot b | \alpha \in ]a, b] \}$

### Definition

As the result is probably not **all** numbers in the interval, **any** or at least **one** number in the interval must be expressed as a new interval number *in*:

$[x_0, x_1]in := \{ x \in \overline {\mathbb R} | \exists x \in [x_0, x_1] \}$

The indeterminate form of $0 \cdot \infty$ can be expressed as the first rule:

***Rule I***  
$0 \cdot \infty = [0, \infty]in$

Similarly, the expression for the indeterminate form of $0 \cdot -\infty$ is the second rule:

***Rule II***  
$0 \cdot -\infty = [-\infty, 0]in$

### Interval number operations

These are the given mathematical operations.

#### Multiplication

$[x_0, x_1]in \cdot [y_0, y_1]in := [\min(x_0 \cdot y_0, x_0 \cdot y_1, x_1 \cdot y_0, x_1 \cdot y_1), \max(x_0 \cdot y_0, x_0 \cdot y_1, x_1 \cdot y_0, x_1 \cdot y_1)]in$

Regarding the algebraic structure [[3](#3-algebraic-structure)], only the required multiplication for the given rules is investigated.

The algebraic structure of the interval numbers is at least a Magma [[4](#4-magma-algebra)], as all multiplications in $\overline {\mathbb R}$ including ***Rule I*** and ***Rule II*** are defined.

### Deduction

|                                    | Operation or rule                    |
|------------------------------------|--------------------------------------|
| $-1 \cdot (0 \cdot -\infty)$       | ***Rule II***                        |
| $-1 \cdot [-\infty, 0]in$          | Multiplication for interval number   |
| $[-1 \cdot -\infty, -1 \cdot 0]in$ | Operation in $\overline {\mathbb R}$ |
| $[0, \infty]in$                    | ***Rule I***                         |
| $0 \cdot \infty$                   |                                      |

## Implementation

In the [test](test/) folder is a C++ implementation of the interval number and the unit tests.


## Some indeterminate forms as interval numbers

At the time of writing, the expression $\frac{0}{0}$ is undefined, also in $\overline {\mathbb R}$ [[5](#5-affinely-extended-real-numbers)].  
However, with interval numbers, the expression can be defined:

$\frac{0}{0} = [-\infty, \infty]in$

Because the limits of the given example formulas result in $+\infty$ and $-\infty$:

$\lim_{n\to0^+}\frac{n}{n^2} = +\infty$

$\lim_{n\to0^-}\frac{n}{n^2} = -\infty$

---

Similarly, the indeterminate form $\infty - \infty$ can be expressed as:

$\infty - \infty = [-\infty, \infty]in$

Because different limit approaches yield different results:

$\lim_{n\to\infty}(n - n^2) = -\infty$

$\lim_{n\to\infty}(n^2 - n) = \infty$

---

The indeterminate form $\frac{\infty}{\infty}$ can be expressed as:

$\frac{\infty}{\infty} = [0, \infty]in$

Because different limit approaches yield different results:

$\lim_{n\to\infty}\frac{n}{n^2} = 0$

$\lim_{n\to\infty}\frac{n^2}{n} = \infty$

---

The indeterminate form $0^0$ can be expressed as:

$0^0 = [0, 1]in$

Because different limit approaches yield different results:

$\lim_{n\to0^+}0^n = 0$

$\lim_{n\to0^+}n^n = 1$

---

The indeterminate form $1^\infty$ can be expressed as:

$1^\infty = [0, \infty]in$

Because different limit approaches yield different results:

$\lim_{n\to\infty}(1 - \frac{1}{\sqrt{n}})^{n^2} = 0$

$\lim_{n\to\infty}(1 + \frac{1}{n})^{n^2} = \infty$

---

The indeterminate form $\infty^0$ can be expressed as:

$\infty^0 = [1, \infty]in$

Because different limit approaches yield different results:

$\lim_{n\to\infty}n^{\frac{1}{n}} = 1$

$\lim_{n\to\infty}n^{\frac{1}{\ln(\ln(n))}} = \infty$

## Some equations from indeterminate forms resulting back in a non-indeterminate form

$(0^0) \cdot 0 = 0$

Because:

$0^0 = [0, 1]in$

$[0, 1]in \cdot 0 = [\min(0 \cdot 0, 1 \cdot 0), \max(0 \cdot 0, 1 \cdot 0)] = [0, 0]in = 0$

---

$|\frac{0}{0}| + \infty = \infty$

Because:

$\frac{0}{0} = [-\infty, \infty]in$

$|-\infty, \infty|in = [0, \infty]in$

$[0, \infty]in + \infty = [0 + \infty, \infty + \infty] = [\infty, \infty]in = \infty$

---



## Conclusion

Using this approach, other indeterminate forms could be expressed as intervals and solved in equations as well. Especially the usage and current definition in measure theory should be further evaluated [[6](#6-extended-real-numbers)].

For now, it is shown that the algebraic structure of the interval number is a Magma. However, including the other mathematical operations, the algebraic structure could be further investigated.

Furthermore, other intervals for indeterminate forms could be estimated and defined.

## References

##### 1 Indeterminate form
https://en.wikipedia.org/wiki/Indeterminate_form

##### 2 Extended real number line
https://en.wikipedia.org/wiki/Extended_real_number_line

##### 3 Algebraic structure
https://en.wikipedia.org/wiki/Algebraic_structure

##### 4 Magma (algebra)
https://en.wikipedia.org/wiki/Magma_(algebra)

##### 5 Affinely Extended Real Numbers
https://mathworld.wolfram.com/AffinelyExtendedRealNumbers.html

##### 6 Extended real numbers
https://planetmath.org/extendedrealnumbers
