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
