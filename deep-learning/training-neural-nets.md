# Some papers, thoughts, etc.

# [Parallelizing CNNs](https://arxiv.org/pdf/1404.5997.pdfs://arxiv.org/pdf/1404.5997.pdf)

1. Model Parallelization
	- When *per neuron* computations are expensive
2. Data Parallelization
	- When *per weight computations* are expensive

**Convolutional layers are ~95% of the computation, but only __5% of total parameters__**
**Fully connected layers are ~5% of the computation, but only __95% of total parameters__**
Convolutional layers are __data parallelizable__.
FC layers are __model parallelizable__.

Assume FC layers are only at the top of the network (last). Then

# Optimization Methods
## Vanilla SGD
Classic.
**__SGD and Batch GD are the most accurate. All improvements lead to faster convergence, but worse solutions!__**.

__SGD generalizes the best.__
## SGD + Momentum

## Adagrad

## Adadelta

# Regularization (from dl book)
### L2
Under a quadratic approximation of the loss in the nbhd of current weights, L2 regularization is like adding values to the diagonals covariance matrix (and rescaling eigenvalues, as shown by an eigendecomposition). This addition tricks the model's optimization to contract all weights, __but pairs with low covariance are effected much more__, i.e. L2 weight-decay has least effect on diagonal/variance and most effect on nearly uncovarrying variable pairs. Regularization tries to shrink everything, but smaller values are shrinked more.

L2 regularization always puts a spherical/symmetric prior close to origin on weights, but many learning problems have a chaotic Hessian (even a quadratic loss could be stretched). Also think in terms of this: if the objective function is stretched, we need to go a long way to lower the loss, but our regularizer favors being close to the center and will fight moving far. However, if the objective is compressed, we can easily walk down hill with minimal resistance from the regularizer.

### L1
Aims for sparsity moreso than L2.
L2 ~ MAP w/ normal prior
L1 ~ MAP w/ laplacian prior

### Other
> In particular, Hinton et al. (2012c) recommend a strategy introduced by Srebroand Shraibman (2005): constraining the norm of each column of the weight matrixof a neural net layer, rather than constraining the Frobenius norm of the entireweight matrix. Constraining the norm of each column separately prevents any onehidden unit from having very large weights. If we converted this constraint into apenalty in a Lagrange function, it would be similar toL2weight decay but with aseparate KKT multiplier for the weights of each hidden unit. Each of these KKTmultipliers would be dynamically updated separately to make each hidden unitobey the constraint. In practice, column norm limitation is always implemented asan explicit constraint with reprojection

### Early Stopping

### Sparse Representations
There are two kinds of sparsity, weight/parameter and representational.
Weight/parameter sparsity aims for having many zero weights, but the computed value may be dense.
Representational sparsity aims for many zeros in the output, possibly with dense weights.
You can place an L1 prior on the output of a model to enforce rep. sparsity.
You can place hard constraints on the model (constrained opt.) such as in Orthogonal Matching Pursuit.

### Dropout
...


# Computing Convolutions
## Dense
## Simple Parallel+Sparse
## im2col Preprocessing+Dense

## [Shattered Gradients](https://arxiv.org/pdf/1702.08591.pdf)
  - Why do skip connections help so much?
  	- Gradient correlations in deep FF nets **decay exponentially** (becoming white noise)
	- Gradients w/ skipcons **decay sublinearly** (becoming in b/t brown and white noise) with rate $\frac{1, \sqrt{L}}$
		- Brown Noise has more power at __low frequencies__
		- White Noise has equal power at __all frequencies__
  - ... finish ...
  
  - 'Looks Linear initialization'
