# Vanilla ADTs - Free Monads - F-Algebras

These seem to be disjoint ways of accomplishing operation on recursive data types.

## ADTs

 - Straight-forward (sort of) pattern matching.
 - Type-level, Value-level.
 - Can have a 'tag' type parameter.
   - Let's say it's different from an F-algebra for classification purposes.

## F-Algebras
[Bartosz](https://www.schoolofhaskell.com/user/bartosz/understanding-algebras)
[Williams (f-alg and GADTs](http://www.timphilipwilliams.com/posts/2013-01-16-fixing-gadts.html)
[Wadler](http://homepages.inf.ed.ac.uk/wadler/papers/free-rectypes/free-rectypes.txt)
[Sheard](http://web.cecs.pdx.edu/~sheard/course/AdvancedFP/notes/CoAlgebras/Code.html)
  - ADTs with 'carrier-type', a type parameter 'tag' in the ADT definition.
  - Allows 

## Free Monads
[Gonzalez](http://www.haskellforall.com/2012/06/you-could-have-invented-free-monads.html)
[Gonzales](http://www.haskellforall.com/2012/07/purify-code-using-free-monads.html)
[Gonzales transformers](http://www.haskellforall.com/2012/07/free-monad-transformers.html)
[Kmett](http://comonad.com/reader/2011/free-monads-for-less/)

  - Define an ADT representing all states/paths of a program.
  - Write one or many 'interpreters' that assosciates different actions to the ADT.
  - A Free Monad is equivalent to a tree??
