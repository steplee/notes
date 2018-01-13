# Polynomials and stuff
## Symmetric Polynomials
[Link](https://0fps.net/2013/01/24/comparing-sequences-without-sorting/)

You can hash list of integers (e.g. some list unique ids) so that they are _equal iff they are permutations of one another_ using symmetric polynomials.
> Polynomial multiplication is convolution.
Therefore this hash can be computed in `O(n lg^2(n))`

#### Improving running time
Move from *commutative rings* to *semirings* (don't need commutativity, don't have inverse addition).
Keep same symmetric polynomial formula, but
	- swap + for min 
	- swap * for max
	- swap 0 for inf
	- and 1 for -inf
now
```
S_2,0 = min(a0,a1)
S_2,1 = max(a0,a1)
```
They are the **rank functions**
_*Evaluating symmetric polynomials over min/max semiring ~=~ sorting.*_

#### Tropical Semiring
Tropical semiring has:
	- max  for addition
	- +    for multiplication
	- -inf for zero (additive)
	- 0    for unit (multiplicative)

log(a+b) ~ max(log a, log b) + O(1).
> This basically a formalization of that time honored engineering philosophy that once your numbers get big enough, you can start to think about them on a log scale.  If you do this systematically, then you eventually will end up doing arithmetic in the (max,+)-semiring.  Masolv asserts that this is essentially what happens in quantum mechanics when we go from small isolated systems to very big things.  A brief overview of this philosophy that has been translated to English can be found here:

_*The elementary symmetric polynomials on the (max,+) semiring are the partial sums of the sorted sequence.*_


## Grobner Bases
[Link](http://www.risc.jku.at/people/buchberg/papers/2001-02-19-A.pdf)

> It is interesting to note that the Grobner bases algorithm,
>	- for linear polynomials, specializes to Gauss algorithm, and
>	- for univariate polynomials, specializes to Euclids algorithm.
