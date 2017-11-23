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

## 

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
