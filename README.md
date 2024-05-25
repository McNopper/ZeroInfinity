# Solving indeterminate forms using interval arithmetic

*by Norbert Nopper*

#### Credits

Thanks to Eric Lengyel for asking the initial right questions.  

### Status quo

The expressions $0 \times ∞$ and implicitly $0 \times -∞$ are indeterminate forms [1].

*ToDo:*  
*Explain problem, that no calculations can be done.*  

*ToDo:*  
*Does not work `-1 x (0 x -∞)` => `(-1 x 0) x -∞)`=> `-1 x -∞` => `0 x ∞` with math limits even if associative law can be used.*

$\lim_{n\to\infty}\sqrt[n]{n}=1$  
$\lim_{n\to\infty}\frac{1}{n}=0$  
$\lim_{n\to\infty}{n}=\infty$  
  
For explanation $\lim_{n\to\infty}\sqrt[n]{n} \times \lim_{n\to\infty}\frac{1}{n} = \lim_{n\to\infty}\sqrt[n]{n} \times \frac{1}{n} = \lim_{n\to\infty}\frac{1}{n}$ which is again 0.

### Thesis

$0 \times ∞ = -1 \times (0 \times -∞)$

### Inspiration

In interval arithmetic, the intervals `[0, ∞]` and `[-∞, 0]` are allowed [2].

The indeterminate form of `0 x ∞` can be expressed as the interval `[0, ∞]`.  
Similar, the indeterminate form of `0 x -∞` is `[-∞, 0]`.

*ToDo:*  
*Explain illustration and so on*  
![](illustrations/visual_interval_number.png)  

### Deduction

*ToDo:*  
*Same as in status quo, however with intervals*

`0 x -∞` => `[-∞, 0]`  

### Interval arithmetic operators

*ToDo:*  
*Define Addition and Multiplication for minimal algebraic structure of Ring [3]*  

### Implementation

*ToDo:*  
*Adapt source code.*  

### Conclusion

Using this approach, other indeterminate forms could be expressed as interval arithmetics and solved to equations as well.

### References

[1] [Indeterminate form](https://en.wikipedia.org/wiki/Indeterminate_form)  
[2] [Interval arithmetic](https://en.wikipedia.org/wiki/Interval_arithmetic)  
[3] [Ring (mathematics)](https://en.wikipedia.org/wiki/Ring_(mathematics))  

#

*ToDo:*  
*Quick links and to be integrated and/or removed later.*

### Form

Markdown Cheat Sheet  
https://www.markdownguide.org/cheat-sheet/

Writing mathematical expressions  
https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/writing-mathematical-expressions

### Inhalt

Teilgebiete der Mathematik  
https://de.wikipedia.org/wiki/Teilgebiete_der_Mathematik

**Algebra**

Algebraische Struktur  
https://de.wikipedia.org/wiki/Algebraische_Struktur

- Kommutativgesetz  
https://de.wikipedia.org/wiki/Kommutativgesetz

- Distributivgesetz  
https://de.wikipedia.org/wiki/Distributivgesetz

- Assoziativgesetz  
https://de.wikipedia.org/wiki/Assoziativgesetz

- Inverses Element  
https://de.wikipedia.org/wiki/Inverses_Element

Körper (Algebra)  
https://de.wikipedia.org/wiki/K%C3%B6rper_(Algebra)

Ring (mathematics)  
https://en.wikipedia.org/wiki/Ring_(mathematics)  

*Zahlen*

Hyperreelle Zahl  
https://de.wikipedia.org/wiki/Hyperreelle_Zahl

Unendlich (Mathematik)  
https://de.wikipedia.org/wiki/Unendlich_(Mathematik)

**Analysis**

improper limits  
https://planetmath.org/improperlimits

Grenzwert (Funktion)  
https://de.wikipedia.org/wiki/Grenzwert_(Funktion)
https://de.wikipedia.org/wiki/Grenzwert_(Folge)#Wichtige_Grenzwerte

Grenzwertrechner  
https://mathdf.com/lim/de/
Enter: sqrt(x,x)*1/n  

### Übersetzungen

Unbestimmter Ausdruck (Mathematik) (zu [1])  
https://de.wikipedia.org/wiki/Unbestimmter_Ausdruck_(Mathematik)

Intervallarithmetik (zu [2])  
https://de.wikipedia.org/wiki/Intervallarithmetik
