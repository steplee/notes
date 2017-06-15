# Profunctors

Sources:
  - [Piponi](http://blog.sigfpe.com/2011/07/profunctors-in-haskell.html)
  - [Freeman](https://www.youtube.com/watch?v=OJtGECfksds&t=4989s)
  - Hackage


#### Contravariant Functors

```Haskell
class Contravariant (f :: * -> *) where
  contramap :: (a -> b) -> f b -> f a
  (>$) :: b -> f b -> f a
```
And covariant is a normal functor.

#### Profunctors

A profunctor is covariant in *second*, contra in *first*:
```Haskell
class Profunctor (p :: * -> * -> *) where
  dimap :: (a -> b) -> (c -> d) -> p b c -> p a d
  lmap :: (a -> b) -> p b c -> p a c
  rmap :: (b -> c) -> p a b -> p a c

-- Example from Lens, actuall all lens are profunctors
type Iso s t a b = forall p f. (Profunctor p, Functor f) => p a (f b) -> p s (f t)

isoP :: Profunctor p => Iso a b -> p a a -> p b b
isoP (Iso to from) = dimap to from


---- Common Profunctors

-- Lift a Functor into a Profunctor (forwards).
newtype Star f d c = Star { runStar :: d -> f c }
```

```
      p
  a->b  c->d
  a   ->   d
```

```Haskell
class Profunctor p => Strong p where
  first  :: p a b -> p (a, x) (b, x)
  second :: p a b -> p (x, a) (x, b)

instance Strong (->) where
  first f  (a, x) = (f a, x)
  second f (x, a) = (x, f a)
```

###### From Hackage (Kmett)

Formally, the class Profunctor represents a profunctor from Hask -> Hask.

Intuitively it is a bifunctor where the first argument is contravariant and the second argument is covariant.

You can define a Profunctor by either defining dimap or by defining both lmap and rmap.

If you supply dimap, you should ensure that:
`dimap id id ≡ id`

If you supply lmap and rmap, ensure:

  `lmap id ≡ id
  rmap id ≡ id`

If you supply both, you should also ensure:
  `dimap f g ≡ lmap f . rmap g`

These ensure by parametricity:
  `dimap (f . g) (h . i) ≡ dimap g h . dimap f i
  lmap (f . g) ≡ lmap g . lmap f
  rmap (f . g) ≡ rmap f . rmap g`

```Haskell
-- Map over both arguments at the same time.
dimap :: (a -> b) -> (c -> d) -> p b c -> p a d`
-- dimap f g ≡ lmap f . rmap g

-- Map the first argument contravariantly.
lmap :: (a -> b) -> p b c -> p a c
-- lmap f ≡ dimap f id

-- Map the second argument covariantly.
rmap :: (b -> c) -> p a b -> p a c Source #
-- rmap ≡ dimap id
```


todo: read up on negative position vs positive position. I heard on a podcast it is related not to what I assumed, it actually relates to the logical definition of implication: 'a -> v = ~a v b'
