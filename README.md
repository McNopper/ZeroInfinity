# Solving indeterminate forms using interval arithmetic

*by Norbert Nopper*

#### Credits

Thanks to Eric Lengyel for asking the initial right questions.

### Thesis

$$0 \times ∞ = -1 \times (0 \times -∞)$$

#### Status quo

The expressions `0 x ∞` and implicitly `0 x -∞` are indeterminate forms [1].

A naive approach like `-1 x (0 x -∞)` <=> `(-1 x 0) x -∞)` with math limits [2] results in `0 x -∞` even when the associative law is allowed.

Existing required math limits:  
$$\lim_{n\to\infty}\sqrt[n]{n}=1$$  
$$\lim_{n\to\infty}\frac{1}{n}=0$$  
$$\lim_{n\to\infty}{n}=\infty$$  
  
Assume the usage of the associative law is allowed:    
$$\lim_{n\to\infty}-\sqrt[n]{n} \times \lim_{n\to\infty}\frac{1}{n} = \lim_{n\to\infty}-\sqrt[n]{n} \times \frac{1}{n} = \lim_{n\to\infty}\frac{-1}{n}$$  
The result is again 0.

### Idea

In interval arithmetic, the intervals `[0, ∞]` and `[-∞, 0]` are allowed [3].

The indeterminate form of `0 x ∞` can be expressed as the interval `[0, ∞]`.  
Similar, the indeterminate form of `0 x -∞` is `[-∞, 0]`.

![](illustrations/visual_interval_arithmetic.png)  

*ToDo:*  
*Check, if this is plausible and if it has to be further explained.*

### Deduction

*ToDo:*  
*Same as in status quo, however with intervals*

`-1 x (0 x -∞)` <=> `-1 * [-∞, 0]` <=> `[-1 * -∞, -1 * 0]` <=> `[0, ∞]` <=> `0 x ∞`  

### Interval arithmetic operators

*ToDo:*  
*Define Addition and Multiplication for minimal algebraic structure of Ring [4]*  

### Implementation

*ToDo:*  
*Adapt source code.*  

### Conclusion

Using this approach, other indeterminate forms could be expressed as interval arithmetics and solved to equations as well.

### References

[1] [Indeterminate form](https://en.wikipedia.org/wiki/Indeterminate_form)  
[2] [Limit (mathematics)](https://en.wikipedia.org/wiki/Limit_(mathematics))  
[3] [Interval arithmetic](https://en.wikipedia.org/wiki/Interval_arithmetic)  
[4] [Ring (mathematics)](https://en.wikipedia.org/wiki/Ring_(mathematics))  
