# Haykin NN (Drive)

## 3. LMS
### 3.3 Unconstrained Optimization


LMS, being stochastic, has optimal solution that wanders around a small region.
Analogical to a particle in a system with heat and random dynamics (think brownian motion and 'Langevin' dynamics)

## 8. Unsupervised Learning
### 8.1 Principles
##### 1. Self-amplification:
Neighboring neurons must fire together (**interactive**), if they fire apart they get *weaker*.
This is expressed $\nabla w_{kj}(n) = f(y_k(n), x_j(n))$, where y and x denote the pre/post synaptic firings of nuerons k and j, respectively.
The most basic case is $\nabla w_{kj}(n) = \eta \cdot y_k(n) \cdot x_j(n))$
Here, firings will raise the synapse strength until saturation at which point selectivity is lost.
To avoid saturation you can *normalize* over all output neurons.

##### 2. Competition
Stability depends on some neighbors pushing up, some down.

##### 3. Cooperation
Lateral interaction.
Preceded by comptetition.

##### 4. Structural Information
wrt input.

### 8.4 PCA
Rotate basis as to minimize variance of components. 'maximize rate of decrease'
You are finding a vector `q` which solves an eigenvalue problem `Rq = \q`, where `R` is the correlation matrix, to get a matrix `Q`.

### 8.5 PCA ('eigenfilter') from Hebbian Rule
> A single linear neuron with a Hebbian-type adaptation rule for its synaptic weights can evolve into a filter for the first principal component of the input distribution

Use the linear update from above, along with normalization to prevent saturation/encourage competition.


### 10.14 Natural Gradient

### 11.7 Boltzmann Machine

...

1. Positive Phase
2. Negative Phase

Call x the observed samples in one instance, X the full training data.
Call observed samples xa, a subset of variables in x.
Training set examples are iid, so p(Xa = xa) is factorial distribution (product)
log-liklihood is thus a sum of log p


Push up on positive samples
Push down on all samples
End result: positive samples higher

Gibbs Sampling is a means to draw these positive samples.

pg. 603


### 11.10 Deterministic Annealing

...

_Equivalent to EM_

## 14. Bayesian Filtering
State-Space Model. Can view state-estimation is an inverse problem.


