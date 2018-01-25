# [Boyd Book]()
### 4. 
##### Examples of LPs
  1. Diet problem
  2. Largest ball in a polyhedron (Chebyshev center)
  3. Activity Planning (with exponential decay, okay since not an optim. variable)

##### Examples of QPs
  1. Least squares & Regression
  2. Bounding Variance
  3. LP with random cost (has 'risk aversion' hyperparam)
  4. Markowitz Portfolio
    - The variance (`x'x`) of portfolio `x` is to be minimized, st. a minimum mean return is met.

##### SOCPs
  1. LP with random constraints
  2. Minimal surface

##### Geometric Programs
These arise from posynomials: sums of monomials. They are not convex on the surface, but a transformation `y = log x` so that `x = exp y` turns the objective into an a sum of exponential of affine functions.
  1. Frobenius Norm diagonal scaling (find `diag(d)` s.t. `DMD^-1` is min)
  2. Spectral Radius of a PSD matrix

##### CPs with Generalized (Vector) Constraints
  1. Matrix norm optimization
  2. Moment problems
  3. Portfolio risk w/ incomplete covariance info


### 5. Duality
##### 5.1 Lagrange Duality
Augment objective by adding terms formed by weighting constraints.
__It gives lower bounds on the optimum__.

Recall the conjugate of a function `f`: `f*(y) = sup_x [y'x - f(x)]`
The conjugate and Lagrange dual are related.
Eg. for an LP with constraints `Ax < b`, `Cx = d`, `g(\,v) = -b'\ - d'v - f*(-A'\ - C'v)`
Also see entroy maximization example.
