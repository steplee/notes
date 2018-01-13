# RL

# Sutton Book
## 1.
RL as a whole:
**Sensation -> Action -> Goal -> [Action]**

**Policy**: State -> Distribution over actions (representing prob of selecting each)
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

### 3.5
*Values* used for almost all RL to approximate expected return.
The **State-Action** function `v_pi(s)` tells expected reward of being in state `s` under policy `pi`
The **Action-Value** function `q_pi(s,a)` is value of being in state `s`, taking action `a`, and following `pi` from thereon. Note: we may not be acting in accordance with `pi` when taking the first action.
The **Bellman equation** expresses a relations between the value of a state and it's sucessors. Essentially, the value of a state must be equal to the expected value of its successors states plus the reward along the way. The flow of information is an instance of a**backup operation**.
It is a triple sum over action (pi(a|s)), next state, and next reward (p(s',r | s,a)).
If linear (or known for each state), can be solved.
You typically have too many states to keep track of in `v` and `q`, so they are substituted by parameterized functions (neural nets) and trained.

The value of an action depends on expected next reward and the expected sum of remaining rewards, but nothing else. **Note:** our value function is an expectation since we have only a probability that action `a` will result in state `s'`: `p(s',r | s,a)`

If you have an optimal value function, you can greedily pick the next best-looking state (i.e. with a search depth of one)
If you have an optimal action function, it is even easier since `q` essentially caches results and we would pick `argmax_a` from it.

With a value function, you pick a 1-step state by assigning a value to each one *equal to the average of its children 2-step states (plus reward incurred)*.
With an action function, the `max` is pushed into the expectation.


## 4. Dynamic Programming
  - For now, assume finite MDP (w/ discrete states)
  - Use value functions to structure search for better policies.
  - DP values filled in using Bellman eqn. as updates for approximations.
  - **Policy Evaluation** is computing the state-value function `v_pi` for some policy `pi`.
    - **Iterative Policy Evaluation** uses a policy successively and updates the value function. The approximation `v_k -> v_k+1` will converge to `v_pi`. This kind of update is called an **expected update**. Usually implemented by stopping when a the value function has not changed beyond some small number delta (i.e. has converged).

### 4.2 Policy Improvement
  - General note: **A policy precedes a value function. Also, we also consider a converged value function.**
  - For now, think in terms of deterministic policies.
  - How to know when to change our policy, assuming we have its value func?
  - One way: use `q_pi(s, a)` to consider the value of taking an action `a` and thereafter following the old policy.
  - **Policy Improvement Theorem**: If `q_pi(s, pi'(s)) >= v_pi(s)`, then `v_pi'(s) >= v_pi(s)`
    - The consequent __only__ considers state `s`.
    - If following `pi'` at state `s` and `pi` onward achieves better value than `pi` at `s`, then `pi'` is atleast better at all states reachable from `s`.
    - What this all means is that if you do an off-policy lookahead, you should always take the best-looking state that maximizes your current value function (and modify your current policy), as it will always improve your reward and thus your value.
    - This is the heart of the Bellman optimality eqn.
    - These results carry over to the stochastic policy case.

### 4.3 Policy Iteration
  - Continually improve a base policy by recomputing the value function each time you improve.
  - You will have a chain of monotonically improving polcies & value functions
  - The chain is interleaving *policy evaluations* and *policy improvements*
  - Each policy evaluation reuses the previous value function and modifies it.

### 4.4 Value Iteration
  - The policy evaluation step is usually lengthy, we want to avoid a full convergence each iteration.
  - Doing one update per state at each iteration is called **Value Iteration**. Note: this still calls for doing an update *per state* in the global state set.
  - VI is just turning the Bellman eqn into an update rule.
  - 







#### Other Sources
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


