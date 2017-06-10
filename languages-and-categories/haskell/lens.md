# Lens

![http://i.imgur.com/ALlbPRa.png](lens picture)
#[https://www.youtube.com/watch?v=cefnmjtAolY&feature=youtu.be&hd=1](ed kmett)
#[https://github.com/ekmett/lens](readme)
#[http://comonad.com/reader/2012/mirrored-lenses/](comonad reader)

## s t a b

s : initial  full type
t : result   full type
a : result  local type
b : initial local type

## From Hackage

Every Lens is a valid Setter.

Every Lens can be used for Getting like a Fold that doesn't use the Applicative or Gettable.

Every Lens is a valid Traversal that only uses the Functor part of the Applicative it is supplied.

Every Lens can be used for Getting like a valid Getter, since Functor is a superclass of Gettable.

Since every Lens can be used for Getting like a valid Getter it follows that it must view exactly one element in the structure.

The Lens laws follow from this property and the desire for it to act like a Traversable when used as a Traversal.

### Laws

1) You get back what you put in:
 `view l (set l b a)  ≡ b`

2) Putting back what you got doesn't change anything:
 `set l (view l a) a  ≡ a`

3) Setting twice is the same as setting once:
 `set l c (set l b a) ≡ set l c a`


##

(.) is compositon of lenses

set = .~
```
_1 .~ "hello" $ ((),"world")
("hello","world")
  where
    (.~)  :: ASetter s t a b -> b -> s -> t
    -- notice: .~ does not access the 'a' type
    -- Takes a setter -> result -> function -> result
```

view = ^.
```
(^.) :: s -> Getting a s a -> a
-- notice Getting has no reference to t or b since they are for writing
```

You can make a Getter out of a pure function with to.
```
"hello"^.to length
  where
    to :: (Prelude.Functor f, Contravariant f, Profunctor p) =>
          (s -> a) -> Optic' p f s a
```

Recall contravariant:
```Haskell
class Contravariant (f :: * -> *) where
  contramap :: (a -> b) -> f b -> f a
  (>$) :: b -> f b -> f a
```
And covariant is a normal functor.

Recall a profunctor is covariant in first, contra in second:
```Haskell
class Profunctor (p :: * -> * -> *) where
  dimap :: (a -> b) -> (c -> d) -> p b c -> p a d
  lmap :: (a -> b) -> p b c -> p a c
  rmap :: (b -> c) -> p a b -> p a c
```
todo: read up on negative position vs positive position. I heard on a podcast it is related not to what I assumed, it actually relates to the logical definition of implication: 'a -> v = ~a v b'

```Haskell
  (&)   :: a -> (a -> b) -> b

  each  :: (Applicative f, Each s t a b)
        => (a -> f b) -> s -> f t

  (&~)  :: s -> State s a -> s

```
