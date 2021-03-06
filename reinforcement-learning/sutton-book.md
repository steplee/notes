# RL
The language used in RL is very important. Make sure you understand the definitions, they are simple but subtle and provide a lot of insight. This is one case where knowing the vocabulary is actually important and not just to sound complicated without meaning.

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
  - Doing several steps of policy eval per improvement helps convergence.
  - All this has been **synchrous** DP. We sweeped over the entire state set each iter.

### 4.5 Asynchronous DP
  - **Asynchronous DP** are iterative, possibly online, in-place DP methods that modify values in any order. You may update state 1 a hundred times before state 5. So long as every state is touched as time goes to infinity, we converge in the limit.

### Generalized Policy Iteration
  - Regular PI has the evaluation and iteration completely converge when alternating b/t them.
  - Switching to the async framework, we interleave the operations without running them to convergnce.
  - The value function stabilizes only when the policy improvement stabilizes, and vice versa. __Then we have found a policy that is greedy with respect to its own evaluation and is thus optimal.__
> Each process drives the value function or policy toward one of the lines representing a solution to one of the two goals. The goals interact because the two lines are not orthogonal. Driving directly toward one goal causes some movement away from the other goal. Inevitably, however, the joint process is brought closer to the overall goal of optimality.

## 5. Monte Carlo Methods
  - Do not require true sequence of steps or complete knowledge of environment. Require *experience* (samples of states, actions, and rewards), even from a simulation. Only on completion of an episode are value estimates or policies changed. We always speak of averaging complete returns.
  - There is non-stationarity from the point of view of earlier states -- the return of a past state depends on actions taken later on in the same episode.
  - Use GPI to deal with nonstationarity, but instead of *computing* from the full MDP, we *learn* from sample returns of the MDP.

### 5.1 MC Prediction
  - Estimate value of state by average returns starting from that state. Should converge.
  - A state may be visited several times in one episode. Should we include in our average only the first, or every time? Both are valid.
  - __DP methods are not great when you do not know the distribution of next events (they require the env. dynamics s the four argument function `p`)__. Monte Carlo methods make these types of problems much simpler by sampling.
  - A Monte Carlo backup tree  **goes to the end of the episode, state estimates are independent of one another, and has edges only on transitions sampled from a single episode**.
  - Sutton mentions how a soap bubble has height as average of neighboring (over a small circle) points (harmonic, laplacian=0 iirc), and boundaries meet with a steel loop. The shape can be computed by successively averaging, similar to DP's policy iteration. If instead you cared only about a small subset of mesh points, an MC method would start at the selection of points and step around their neighbors and average them all out. You can save computation by only updating local parameters (since local consistency is all we cared about).

### 5.2 MC Estimation of Action Values
  - Without a model, we fallback to action values, since we cannot do a one-step lookahead without a model and value functions are essentially useless.
  - Luckily MC methods don't change much, we just consider state-action rather than states alone.
  - Unfortunately many state-action pairs will not come up in any further episodes when `pi` is deterministic. The MC estimates then fail to converge to optimality.
  - We need to estimate value of __all actions from each state__, not just the one `pi` prescribes. The classic *exploration problem*.
  - The best way is to limit yourself to policies that are **stochastic**, another is **exploring starts** where each episode start on some random state-action pair, and we are gauranteed to start on all of them.

### 5.3 Monte Carlo Control
  - GPI with a state-action policy judged against a action-value function rather than state policy w/ state value function.
  - One way to avoid the assumption of inifinite episodes: Alternate improvement and evaluation only after an entire episode. Use *exploring starts* to ensure all state-action pairs are encountered. See page 81 for intuitive psuedocode.
  - Now, to remove need for exploring starts...

### 5.4 Stochastic Policies
  - We must ensure all actions are selected infinitely often, even if very unlikely.
  - Two approaches:
    1. On-policy methods
      - Attempt to evaluate or improve the actual current policy.
    2. Off-policy methods
      - Attempt to evaluate or improve a policy while *using a different one to generate episodes*

##### On-Policy Methods
  - Usually *soft* meaning any action has non-zero prob of being selected.
  - Exploring starts is one example, **epsilon-greedy** methods are another. Called *epsilon-soft* since all actions have greater than `eps / |A(s)|` prob of being selected.
  - GPI does not require the policy be taken to a greedy policy, only that *the policy moves towards a greedy policy*.
  - (come back to proofs)

### 5.5 Off-Policy Prediction w/ Importance Sampling
  - We must behave non-optimally to explore options and find optimal policy!
  - On-policy cheats by looking for an explorative *near-optimal* policy when training.
  - Here we use *two* policies, the *target* of interest and the *behavior* to generate episodes.
  - Off-policy is more complicated, higer variance, and slower to converge; also more powerful and general.
  - First lets consider how to estimate `v_pi` given `v_b` where `pi` is the target and `b` is the behavior policy.
     - First off, they must all execute the same set of actions. (**Coverage**)
     - Many times `b` is stochastic but `pi` is deterministic.
  - **Importance sampling** is a technique to estimate expectations of one dist given samples of another. Use here by weighting returns to the relative probability of their trajectories occuring under the target and behavior policies, called the **importance-sampling ratio**.
    - We form the probabilities of `P [ A_t, S_{t+1}, A_{t+1}, ..., S_T | S_t, A_t:T-1 ~ pi ]` by taking the product using the MDP transitions and policy.
    - We take the ratio of *two of these products*, the numerator using `pi`, the denominator using `b`. Something interesting happens: the factors from the MDP are common and thus cancel!
    - So the __ratio depends only on the policies and the sequence__, not the MDP.
    - To estimate `v_pi(s)` **scale returns by ratios, and average results** 
    - (I am not bothering to TeX up the math here, just see page 86)
    - **Weighted IS** is biased, but more stable. Sometimes **much** more stable in practice and has lower error in beginning of training.

### 5.6 Incremental Implementation
On-policy incremental is straight-forward.
Off-policy depends on ordinary/weighted IS.
  - Ordinary IS: straight-forward
  - Weighted IS: In addition to keeping returns `G_i` and weights per update `W_i`, also keep the cumulative weights per state `C_n` and when updating the value, use : `V_n+1 = V_n + W_n/C_n * (G_n - V_n)`

### 5.7 Off-policy MC Control


## 6. TD Learning
TD methods are the best of DP & MC: they can update based on other learned estimates (DP) and they can learn from raw experience without a model (MC)

### 6.1 TD Prediction (Policy Eval)
TD(0): $V (St) ← V (St) + α[R_{t+1} + γV (S_{t+1}) − V (S_t)]$

Like MC, update estimate `V` for all states seen in an experience.
MC waits for a return to use as a target in the update. TD updates immediately after acting, with a target $R_{t+1} + \rho*V(S_{t+1})$ (this is TD(0)). It *bootstraps* like DP.
_MC assumes uncertaintity in the return, DP in the current policy_. **TD assumes uncertaintity in both.**
The **TD error** is the target minus the current estimate, which is multiplied by the learning rate and used to update the value estimate, similar to a gradient in SGD.

TD is like updating while the episode is in progress, MC can only do after the final reward is observed and episode over. The waiting in traffic example: you must change your estimate of how long it takes to get to work depending on traffic conditions (TD), you don't need to wait until you finally get there (MC).

### 6.3 TD Optimality
TD tends to learn faster then MC, both are sound mathematically.
Batch TD __gets better answer__ then MC, even though they both converge.
The 2-state Markov process example where A -> (0,B) -> V(3/4) shows how MC & TD differ.
  - MC assigns V(A) = 0 since the next state has reward 0
  - TD assigns V(A) = V(B) since A -> B.
  - MSE on the data is consistent with MC, *but in reality we expect TD to do better*.

### 6.4 Sarsa: On-Policy TD
Switch to learning `q_pi` action-value pairs. GPI but with TD updates.
$Q(S_t, A_t) ← Q(S_t, A_t) + α[R_{t+1} + γQ(S_{t+1}, A_{t+1}) − Q(S_t, A_t)]$
(Algorithm on page 106)

### 6.5 Q-Learning: Off-Policy TD
$Q(S_t, A_t) ← Q(S_t, A_t) + α[R_{t+1} + γ max_a Q(S_{t+1}, a) − Q(S_t, A_t)]$
Q-Learning directly approximates `q*`  with `Q`, **independent of behavior policy**.
This means we can sample actions any way we like to encourage exploration (usually epsilon-greedy)
The 'cliff walking' example demonstrates Sarsa v Q-learning. Because of epsilon-greedy changing Q-learning learns slower since it samples bad actions. If epsilon were decayed, it would converge to Sarsa's performance.

### 6.6 Expected Sarsa
