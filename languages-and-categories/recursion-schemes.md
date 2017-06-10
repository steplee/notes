# Recursion Schemes

See:
  - [https://medium.com/@jaredtobin/practical-recursion-schemes-c10648ec1c29](jtobin's blog post series)
  - Banana's and Barbed Wires
  - [https://github.com/ekmett/recursion-schemes/](ekmett's recursion schemes library)

## jtobin's exposition
  - Factor out recursion
    - Pattern Functors
    - Fixed Points
  - Foldable, Unfoldable, and Base

  From a fully-qualified recursive type (e.g. data Natural = Z | S Natural) we can create a new, parameterized type with the parameter replacing *all recursive calls* in the original type.
  The new type must be functorial in the added parameter, so it is said to be a **pattern functor**

```Haskell
x = 5 :: Int
```
