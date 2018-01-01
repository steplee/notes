# RL

# Sutton Book
## 1.
RL as a whole:
**Sensation -> Action -> Goal -> [Action]**

**Policy**: State -> Action
Stimulus, response.
Could be lookup table, neural net, search tree, etc.
**Reward Signal** could be delayed to long time in future
**Value Function**: tells the value of a state 'in the long run', if we can reach a high profit from a shitty state, the value of that state is still high. Like a postfix sum.
  - **Action Value**: Expected value next state of being in a state, and taking action
**(Optional) Model of Environment**: Allows inference of state based on action, critical in **planning**. *Trial-and-error* RL methods are __Model-free__.

#### Tic-Tac-Toe without Traditional DP
Let's say we don't want to do full enumeration + DP.
Using a value function method, set all winning state's to reward value 1, and all others to .5. Simulate many games, usually making the greedy best next choice but sometimes going off policy (*exploratory* moves). While playing, __change the value of each state by **backing up** future states and interpolating values__. Under mild assumptions this converges to true answer (decay step size). Not decaying step size can adapt to player changing his strategy.
This method will actually learn to create multi-move traps, even without constructing a model!

## 2. Bandit Problems
Which levers would you use? By the end, pull the one with highest expected value, but you need to balance exploration+exploitation when learning the expectaition.
Setting high initial action value function values (rather than 0) will encourage exploration
##### Epsilon greedy
Select greedy with certain probability, random with `1-` that prob.
Maintain Action-Value function `Q` for each lever.
###### Nonstationarity
Rather then using true mean as the expectation, weight recent values higher (*exponential receny-weighted value*). See book for formula.

## 3. Finite MDPs
Must deal with **State-Action value function**

`p(s', r | s, a)`

#### Sources
 [Karpathy's excellent post](http://karpathy.github.io/2016/05/31/rl)

# TODO Read
	- Cross entropy method
	- TRPO, [here](https://arxiv.org/pdf/1502.05477.pdf)
	- [Gradient Estimation Using Stochastic Computation Graphs](https://arxiv.org/pdf/1506.05254.pdf)
	- [Building Machines that Think and Learn Like People](https://arxiv.org/abs/1604.00289)

# Policy Gradients
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


