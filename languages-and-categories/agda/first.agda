module first where

-- http://www.cse.chalmers.se/~ulfn/papers/afp08/tutorial.pdf

data Bool : Set where
  true  : Bool
  false : Bool

not : Bool -> Bool
not true = false
not false = true

data Nat : Set where
  zero : Nat
  suc : Nat -> Nat

_+_ : Nat -> Nat -> Nat
zero  + m = m
suc n + m = suc (n + m)

_*_ : Nat -> Nat -> Nat
zero  * m = zero
suc n * m = m + (n * m)

_or_ : Bool -> Bool -> Bool
false or x = x
true  or _ = true

if_then_else_ : {A : Set} -> Bool -> A -> A -> A
if true  then x else y = x
if false then x else y = y

data List (A : Set) : Set where
  [] : List A
  _::_  : A -> List A -> List A

-- what?
data _* (a : Set) : Set where
  eps  : a *
  _<<_ : a -> a * -> a *

-- (x : A) -> B
-- for the type of functions taking an argument x of type A and returning a result of type B, where x may appear in B

identity : (A : Set) -> A -> A
identity A x = x

zero' : Nat
zero' = identity Nat zero

-- a function that takes a dependent function and applies it to 
-- an argument
apply : (A : Set)(B : A -> Set) ->
        ((x : A) -> B x) -> (a : A) -> B a
apply A B f a = f a

-- shorthand:
-- (x : A)(y : B) -> C for (x : A) -> (y : B) -> C
-- (x y : A) -> B for (x : A)(y : A) -> B

-- many shorthand:
identity2 : (A : Set) -> A -> A
identity2 = \A x -> x
identity3 : (A : Set) -> A -> A
identity3 = \(A : Set)(x : A) -> x
identity4 : (A : Set) -> A -> A
identity4 = \(A : Set) x -> x
