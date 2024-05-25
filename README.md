# Solving indeterminate forms using interval arithmetic

*by Norbert Nopper*

#### Credits

Thanks to Eric Lengyel for asking the initial right questions.  

### Status quo

The expressions $0 \times ∞$ and implicitly $0 \times -∞$ are indeterminate forms [1].

*ToDo:*  
*Explain problem, why  `0 x -∞` => `0 x (-1 x ∞)` => `(0 x -1) x ∞` => `0 x ∞` is not allowed.*  
*Add scanned sketch regarding the inspiration (analogy to complex number `i`)*  

### Thesis

The above expressions can be solved to the equation:  

$0 \times ∞ = 0 \times -∞$

### Deduction

In interval arithmetic, the intervals `[0, ∞]` and `[-∞, 0]` are allowed [2].

The indeterminate form of `0 x ∞` can be expressed as the interval `[0, ∞]`.  
Similar, the indeterminate form of `0 x -∞` is `[-∞, 0]`.

### Idea

The idea is to calculate the two interval bounds for not indeterminate forms.

I.  
`0 x ∞ = [0, ∞]`:

Replacing second multiplier with 0:  
`0 x 0 = 0`  
Replacing first multiplier with 1:  
`1 x ∞ = ∞`

II.  
`0 x -∞ = [-∞, 0]`:

Replacing second multiplier with 0:  
`0 x 0 = 0`  
Replacing first multiplier with 1:  
`1 x -∞ = -∞`

### Proof

*ToDo*  
*In the Proof, each step has to be explained, that this is based on improper limits.*  

```
0 x -∞      | see II.
[-∞, 0]     | Exclude -1
-1 x [0, ∞] | see I.
-1 x 0 x ∞  | -1 x 0 is 0
0 x ∞

q.e.d.
```

### Interval arithmetic operators

*ToDo:*  
*Define Addition, Subtraction etc.*  
*Check the algebraic structure*

### Implementation

*ToDo:*  
*Adapt source code, that it represents the improper limits.*  

### Conclusion

Using this approach, other indeterminate forms could be expressed as intervals and solved to equations as well.

### References

[1] [Indeterminate form](https://en.wikipedia.org/wiki/Indeterminate_form)  
[2] [Interval arithmetic](https://en.wikipedia.org/wiki/Interval_arithmetic)

#

*ToDo*  
*Quick links and to be removed later.*

### Form

Markdown Cheat Sheet  
https://www.markdownguide.org/cheat-sheet/

Writing mathematical expressions  
https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/writing-mathematical-expressions

SysML  
https://sysml.org/

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

### Übersetzungen

Unbestimmter Ausdruck (Mathematik) (zu [1])  
https://de.wikipedia.org/wiki/Unbestimmter_Ausdruck_(Mathematik)

Intervallarithmetik (zu [2])  
https://de.wikipedia.org/wiki/Intervallarithmetik
