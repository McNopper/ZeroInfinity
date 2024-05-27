# Solving indeterminate forms with extended real numbers and intervals

*by Norbert Nopper*

#### Credits

Thanks to Eric Lengyel for asking the initial right questions.

Thanks a lot to my family and their patience having me as a 🤓.

### Thesis

$$0 \cdot ∞ = -1 \cdot (0 \cdot -∞)$$

#### Status quo

The expressions $0 \cdot ∞$ and implicitly $0 \cdot -∞$ are indeterminate forms [1].

A naive approach like $-1 \cdot (0 \cdot -∞)$ <=> $(-1 \cdot 0) \cdot -∞$ with math limits results again in $0 \cdot -∞$ even when the associative law is allowed.

Existing required math limits for above assumption:

$\lim_{n\to\infty}\sqrt[n]{n}=1$  
$\lim_{n\to\infty}\frac{1}{n}=0$  

Assume the usage of the associative law is allowed:

$\lim_{n\to\infty}-\sqrt[n]{n} \cdot \lim_{n\to\infty}\frac{1}{n} = \lim_{n\to\infty}-\sqrt[n]{n} \cdot \frac{1}{n} = \lim_{n\to\infty}\frac{-1}{n}$

The result is again 0.

### Idea

Using extended real number line $\overline {\mathbb R}$ [2], the intervals $[0, ∞]$ and $[-∞, 0]$ are allowed.

The indeterminate form of $0 \cdot ∞$ can be expressed as the interval $[0, ∞]$.  
Similar, the indeterminate form of $0 \cdot -∞$ is $[-∞, 0]$.

![](illustrations/visual_interval_extended.png)

The interval $[x_0, x_1]$ is estimated from $a \cdot b \in \overline {\mathbb R} \land a \le b$ providing following rule:

$$[x_0, x_1] = \{ x_0 = a \cdot b | b \in [a, b[ \land x_1 = a \cdot b | a \in ]a, b] \}$$

*Note:*  
GitHub can not properly resolve the above curly brackets. They are invisible on GitHub. Please use e.g. Visual Studio Code to display properly.

### Interval operators

*ToDo:*  
*Are interval addition and multiplication of interval trivial?*  
*https://www.lernhelfer.de/schuelerlexikon/mathematik/artikel/intervalle-rechnen.*  
*Define Addition and Multiplication for minimal algebraic structure Ring [3].*

### Deduction

$-1 \cdot (0 \cdot -∞)$  
$-1 \cdot [-∞, 0]$  
$[-1 \cdot -∞, -1 \cdot 0]$  
$[0, ∞]$  
$0 \cdot ∞$

*ToDo:*  
*For each step, name the rules and operators.*

### Implementation

In the [test](test/) folder is an implementation of the interval operators.   

*ToDo:*  
*Depending on the mathematical Ring, extend implementation and unit tests.*

### Conclusion

Using this approach, other indeterminate forms could be expressed as an interval and solved to equations as well.

*ToDo:*  
*Estimate intervals for indeterminate forms with exponents e.g.*  
$1^∞ = [1, ∞]$  
$∞^0 = [1, ∞]$  
*results in this equation:*  
$1^∞ = ∞^0$

*ToDo:*  
*Add investigation, if the algebraic structure is more than a mathematical Ring.*

### References

[1] [Indeterminate form](https://en.wikipedia.org/wiki/Indeterminate_form)  
[2] [Extended real number line](https://en.wikipedia.org/wiki/Extended_real_number_line)  
[3] [Ring (mathematics)](https://en.wikipedia.org/wiki/Ring_(mathematics))
