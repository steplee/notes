# Haskell

## Asymptotic Improvement of Computations over Free Monads
[link](http://www.janis-voigtlaender.eu/papers/AsymptoticImprovementOfComputationsOverFreeMonads.pdf)

## Faking optional named arguments

  Have the function take a full-fledged single data-type that implements the Default typeclass.
  Use lens setters to change fields from defaults.
  e.g.
```
  foo def
  foo (def & arg0 ~. 1 & arg2 ~. 2)
```

## Misc tips

  - Use zipWith with first arg as an inifnite list of functions and second argument as finite list
    - From diagrams: zipWith (repeat (circle 1)) [1,4,7]
```
    sequence [[1,2,3],[10,20,30]]
    -- [[1,10],[1,20],[1,30],[2,10],[2,20],[2,30],[3,10],[3,20],[3,30]]
```
