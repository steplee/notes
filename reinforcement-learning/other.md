# Policy Gradients [(Karpathy's post)](http://karpathy.github.io/2016/05/31/rl)
	- Play many games, update *all* actions in winning games as good, losing as bad
		- _*Yes*_ this is inaccurate, but over the long run it should average out
	- Very similar to SGD in supervised setting, its just that we don't have the loss immediately and so _all states must be saved until end of episdde_
	- Different ways of applying updates & loss
		1. Monolithic score at end of episode
			- $\sum_i{A_i \ p(y_i | x_i)}$
			- Note: _there is no temporal structure, but $p$ will condition on state $x_i$!_
		2. Scores applied throughout
### Modification of advantage/score
	- Good to standardize, e.g. $\frac{x-{\mu}_x}{{\sigma}_x^2}$

### Theory
	- Special case of *score function gradient estimator*
	- There is a trick where you multiply/divide by $p(x)$ after expanding the expectation, then use the factor $\frac{\nabla p(x|\theta)}{p(x|\theta)}$ to subsitute the logarithm in. The final expression is expectation $f(x) \nabla_{\theta } log(p(x|\theta))$
	- **What is the relation to importance sampling?**
		- I'm convinced there is, the same multiply/divide trick is used
	- Key question: _How to shift $\theta$ to increase score of episode-samples, as gauged by score-function $f(.)$?_


# TODO Read
	- Cross entropy method
	- TRPO, [here](https://arxiv.org/pdf/1502.05477.pdf)
	- [Gradient Estimation Using Stochastic Computation Graphs](https://arxiv.org/pdf/1506.05254.pdf)
	- [Building Machines that Think and Learn Like People](https://arxiv.org/abs/1604.00289)

