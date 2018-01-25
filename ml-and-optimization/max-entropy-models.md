# [MaxEnt Models (Berger)](https://www.cs.cmu.edu/afs/cs/user/aberger/www/html/tutorial/tutorial.html)
#### Summary
We impose constraints on our model derived from observations in the data that we think are important. This defines an entire family of valid distributions. From all of these, select the one with maximum entropy. Frame as an optimization problem with Lagrange Multipliers to handle constraints.

#### French Translation Example & Equations
Model: $p(y | x)$
True: $p(x,y)$
Sample: $\tilde{p}(x,y)$
Feature: $f(x,y)$, which is a binary value in this case whose expectation under $\tilde{p}$ is what is needed.
We need to match (constrain) the observed distribution of $f$ with the models:
 $\Sigma \tilde{p}(x) p(y|x) f(x,y)\ =\ \Sigma \tilde{p}(x,y) f(x,y)$

#### MaxEnt Principle & Optimization
With `n` feature constraints, we restrict our model to lie in certain subspaces of the full simpliex. Each constraint removes one dimension by forcing the model on a hyperplane, we assume we will ask no invalid constraints.
**Max Entropy philosophy dictates that of the remaining distributions, we pick the most uniform one**, where uniformity is measured by conditional entropy: $H(p)\ =\ -\Sigma \tilde{p}(x)\ p(y|x)\ log p(y|x)$

#### Exponential Form
Analytical solution usually not possible. Use Lagrange Multipliers to convert constrained to unconstrained optimization.

You end up with three terms (one being a larger triple-sum however) that correspond to entropy, feature constraints, and the sum-to-one constraint for a conditional.

**To solve the optimization problem:**
  1. Hold Lagrange mults fixed and maximize wrt `p`
  2. Plug `p` back in and solve for Lagrange mults.

When solving for `p`, you will see that **the entropy term leads to the optimal form `p*` being an exponential form.**

One Lagrange mult corresponds to normalization and can be found by sum-of-exp-sums. The rest can be solved from plugging in and solving (gauranteed by **KKT**). The *dual function* is the lagrangian with form+normalization plugged in and held constant. 

#### Max Likelihood
__Solving the dual function is maximizing the log-likelihood__
$ L_{\tilde{p}}(p) = log \prod_{xy} p(y|x)^{\tilde{p}(x,y)} = \sum_{xy} \tilde{p}(x,y) log\,p(y|x)$
Of which the last form matches with the dual function.

#### Computing
The dual function is smooth & convex.
**Iterative Scaling** is a popular algortihm to use when `f_i` are non-negative.

It loops until convergence and has an inner optimization step to solve for $\nabla \lambda_i$

#### Inductive Learning
Can compute *feature gain* to select which features to use.
