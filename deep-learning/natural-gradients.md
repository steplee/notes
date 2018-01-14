# [Revisiting Natural Gradients](https://arxiv.org/pdf/1301.3584)
  - 3 Common approaches for accelerating optimizaion
      1. use second-order information (hessian free optimization, LBFGS)
      2. use underlying geometry of the manifold (natural gradient descent)
      3. use uncertainty in gradient (TONGA)

One method (used in hessian free & Krylov subspace descent) is to use forward and backward passes to compute products b/t Jacobian or Hessian matrices and vectors. The products used to approximate the Hessian.

> Given a loss function L parametrized by θ, natural gradient descent attempts to move along the manifold by correcting the gradient of L according to the local curvature of the KL-divergence surface, i.e. moving some given distance in the direction ∇N L(θ):
  `∇N L(θ) = ∇L(θ) E_z [ h (∇ log pθ(z))' . (∇ log pθ(z)) ]^−1`
   = ∇L(θ) . F^−1

The natural gradient corrects the gradient of L (our loss function) by multiplying it by the inverse Fisher matrix. (which is equal to `E [del p(z) . del p(z)]`)

> We can derive this result by considering natural gradient descent to be defined as the algorithm which, at each step, attempts to pick a descent direction such that the amount of change (in the KL-sense) induced in our model is some given value. Specifically we look for a small ∆θ that minimizes a first order Taylor expansion of L when the second order Taylor series of the **KL-divergence between pθ and pθ+∆θ has to be constant**...
Using this constraint we __ensure that we move along the functional manifold with constant speed, without being slowed down by its curvature__. This also makes learning locally robust to reparametrizations of the model, as the functional behaviour of p does not depend on how it is parametrized.

> Natural gradient descent is robust to local re-parametrization of the model. This comes from the constraint that we use. The KL-divergence is a measure of how the probability density function changes, regardless on how it was parametrized. Sohl-Dickstein (2012) explores this idea, defining natural gradient descent as doing whitening in the parameter space.

#### TONGA
> In Le Roux et al. (2008) one assumes that the gradients computed over different minibatches are distributed according to a Gaussian centered around the true gradient with some covariance matrix C. By using the uncertainty provided by C we can correct the step that we are taking to maximize the probability of a downward move in generalization error (expected negative log-likelihood), resulting in a formula similar to that of natural gradient descent.

There is a use of an uncentered covariance matrix that looks like what is used in NG's step, but it is the empirical cov of the minibatch `q(x, t)`, not the theoretically truth like NG's.

####
....
