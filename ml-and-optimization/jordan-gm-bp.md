# Graphical Models and Variational Inference (from Jordan)
These are my notes pertaining to two comprehensive papers:
  - [shorter](https://drive.google.com/file/d/0B50aU2cYzAJFWGlkWkxEQmFQd00/view?usp=sharing)
  - [longer](https://drive.google.com/file/d/0B50aU2cYzAJFdHFSaDFyWlJ4bWs/view?usp=sharing)

## Shorter paper

Inference is finding values of hidden nodes given observed nodes.
Likelihood is important, not in-and-of-itself, but as a subroutine.
VI is based on the assumption that *dense graphs have averaging phenomena, meaning nodes are apprx. like their neighbors.*
A potential is a function on *the set of configurations of a clique*, each setting -> probability.
The _joint pdf is a product over clique potentials_, normalized by $Z$, a _sum of a product over all settings of cliques_
Boltzmann: clique potentials are products of exponentials of quadratic terms. So each clique potential is a product of $exp(\theta_{ij} S_i S_j)$ and $exp(\tehta_{i0} S_i)$ (which is a sum in the $exp^{.}$)
The negative of the exponent is **energy**

Factorial HMM good fo modeling joint configuration of uncoupled set of dynamical systems.
(198)
