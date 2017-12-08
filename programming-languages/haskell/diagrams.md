# Haskell / Diagrams

regPoly (and most other functions for describing shapes) can be used to produce not just a diagram, but also a trail or path. 
```
node    = circle 0.2 # fc green
example = atPoints (trailVertices $ regPoly 6 1) (repeat node)
```

atPoints appears to be with zipWith in that it deals with infinite lists
