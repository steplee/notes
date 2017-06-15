# Recursion Schemes

See:
  - [https://medium.com/@jaredtobin/practical-recursion-schemes-c10648ec1c29](jtobin's blog post series)
  - Banana's and Barbed Wires
  - [https://github.com/ekmett/recursion-schemes/](ekmett's recursion schemes library)
  - [http://blog.sumtypeofway.com/an-introduction-to-recursion-schemes/](a blog post)

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
## sumtypeofway post 1

```Haskell
data   Term f  = In (f (Term f))
out :: Term f ->       (Term f)
out    (In t)  = t

Term Expr = In $ Expr $ Term Expr
out_f :: Term Expr -> Expr (Term Expr)

```
Allows unwrapping of Term Expr -> **arbitarirly nested** (Term Expr)s
Defining recursive types using fixed-points of functors : **codata**

### Generic Traversals

#### Bottom Up

To traverse a Term bottom-up with a function ƒ:
  1. Unpack the term so as to access its children.                    out
  2. Recursively traverse each child of the unpacked term with ƒ.     f
  3. Repack the term.                                                 In
  4. Apply ƒ to it.                                                   f (In ...)

Using (>>>) is more helpful to the intuition here then (.)
  ` f >>> g x   =   g $ f x`

*Unpack, recurse, repack, apply*
`bottom_up fn = out >>> fmap >>> In >>> fn`

Flatten example
```Haskell
flattenTerm :: Term Expr -> Term Expr  
flattenTerm (In (Paren e)) = e  -- remove all Parens  
flattenTerm other = other       -- do nothing otherwise

flatten :: Term Expr -> Term Expr  
flatten = bottomUp flattenTerm
```

#### Top Down

```
To traverse a Term top-down with a function ƒ:
  1. Apply ƒ to the term.
  2. Unpack the term so as to access its children.
  3. Recursively traverse each child of the term with ƒ.
  4. Repack the term.
```
*apply, unpack, recurse, repack*

``` Haskell
topDown, bottomUp :: Functor f => (Term f -> Term f) -> Term f -> Term f

topDown  f = In  <<< fmap ( topDown f) <<< out <<< f 
bottomUp f = out >>> fmap (bottomUp f) >>> In  >>> f
```
Actual **duals**

## sumtypeofway post 2

```Haskell
mystery :: Functor f => (f a -> a) -> Term f -> a
mystery fn =  
  out                   -- 1) unpack the Term
  >>> fmap (mystery fn) -- 2) recursively apply `fn`
  >>> fn                -- 3) apply `fn`

countNodes :: Expr Int -> Int
countNodes (Literal _) = 1 
   ...

type Algebra f a = f a -> a
countNodes :: Algebra Expr Int
mystery :: (Functor f) => Algebra f a -> Term f -> a
```
The name 'Algebra' comes from *unify*, it is like we are **unifying a `f a` *back* to `a`.**
 - So `a` usually has some monoidal/collapsable structure?

#### Catamorphisms
```Haskell
-- mystery is cata, the generalized `fold` operation
cata :: (Functor f) => Algebra f a -> Term f -> a  
cata f = out >>> fmap (cata f) >>> f
```
Bottom-up is like a catamorphism that rebuilds then entire tree after applying the function.
```Haskell
bottomUp f = cata (In >>> f)
```
#### Anamorphisms
An `unfold`.
```Haskell
what :: (Functor f) => (a -> f a) -> a -> Term f
what f = In  <<< fmap (what f) <<< f
cata f = out >>> fmap (cata f) >>> f

type Algebra   f a = f a -> a
type Coalgebra f a = a   -> f a
type Coalgebra f a = f a <- a

ana :: Coalgebra f a -> a -> Term f
ana f = In <<< fmap (ana f) <<< f
```
If algebras are reunions, coalgebras are **disassembly and dispersion.**
"We are taking one established `a` and stuffing it inside a context `f`.

## sumtypeofway post 3


