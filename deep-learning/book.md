# [Deep Learning Book](http://www.deeplearningbook.org/)
## 1 - 17: see green notebook
## 18. Confronting the Partition Function
$\tilde{p}$ is unnormalized.
$Z = \int{\tilde{p}(x) dx}$ is usually intractable. Some deep generative models are designed to have a tractable normalizing constant, some avoid computing it.
But others 'confront' it, and we'll focus on that now.
### Log-Likelihood Gradient
$\nabla_{\theta} log\ p(x;\theta) = \nabla_{\theta}\tilde{p}(x;\theta) - \nabla_{\theta} log Z(\theta)$
The term seperates into the **positive phase** and **negative phase**
Positive phase easy, negative hard : RBM
Positive hard, negative phase easy : VAE
To approximate the negative term, assuming p(x) > 0 and set $\tilde{p}(x) = exp(log(\tilde{p}(x)))$
(See book for analytical tricks)
Then the negative term is minus expectation of del log $\tilde{p}$
This expectation is usually Monte Carlo approximated and used for ML optimization.
Two steps for MC approach to learning undirected models:
  1. (Positive) Sample $x$ from **data** and increase log $\tilde{p}(x)$
  2. (Negative) Sample $x$ from **model** and decrease log $\tilde{p}(x)$
And log $\tilde{p}(x)$ is usually parameterized as energy function, so that the Positive phase pushes *down* and the Negative phase pushes *up*.

### Stochastic Max Likelihood & Contrastive Divergence
Negative phase is making 'hallucinations' less believed-in.
Approximating $\nabla_{\theta} log Z$ requires MCMC which may have long burn-in and needs to restarted every SGD step and is thus inefficent. How can we make it faster?
###### Contrastive Divergence
Initialize your Markov Chain to samples from the data distribution, so burn-in is not really required. Negative phase won't do much at beginning, but as positive phase shapes model to fit the data distribution, the negative phase will trim and tune the model. **Note: CD fails to suppress hallucinations far from the data distribution** since it pushes down only near the data manifold. It is baised, but a good initialization procedure if full MCMC is done after CD. CD is good for shallow models, but not deep ones, because inner hidden units are hard to tie to visible ones.
> The CD algorithm can be thought of as penalizing the model for having aMarkov chain that changes the input rapidly when the input comes from the data.This means training with CD somewhat resembles autoencoder training.
> Sutskever and Tieleman (2010) showed that the CD update direction is not thegradient of any function. This allows for situations where CD could cycle forever,but in practice this is not a serious problem.

##### Stochastic Max Likelihood
'Carry on' the chain from the previous iteration, rather then burning-in new one or using CD. also called Persistent Contrastive Divergence. It makes sense since SGD takes only small steps and chains from successive steps will be consistent.
SML is the best empirically, but it may fail if too many MC steps taken or MC step size is too large for how large the SGD step size is (Model updates and MCMC chain must retain consistentcy). Also spending too much time in a mode may corrupt bias (exasperated by persistance).
###### Fast PCD/SML
Have two sets of model parameters, while having the same number of MCMC chains. One set moves fast, one slow. Forces MC chain to mix rapidly.
##### Psuedolikelihood
Avoids estimating Z.
Optimize ratios of subsets of variables by approximating conditionals.
...
Requires __true__ $log \tilde{p}(x)$ and not a lower-bound as most variational methods provide. So it can't be used with RBMs, VAEs, etc. Maximizing an upper-bound makes no sense.
##### Score Matching
Avoids Z.
The *score* is $\nabla_x log p(x)$, note its the gradient wrt $x$, not $\theta$.
Score matching aims to minimize expected sq. diff. between derivatives of model'
s log density and the data's log density (score).
Note Z is not involved in the gradient.
We don't actually know $p_{data}(x)$, but there is an equivalent objective involving second derivatives, see the text.
(To me, it looks like an autoencoder objective)
Also requires true unnormalized p(x), can't be used in VAEs etc.
Ratio Matching: new objective that works on binary data.
Denoising score matching: regularized by smoothing (or corrupting) data distribution
**Some autoencoders are equivalent to score matching**

#### Summary so far:
SML/PCD and CD estimate gradient of log partition function, not logZ itself.
Score Matching and Psuedolikelihood side-step logZ.

### NCE
$log p_{model}(x) = log \tilde{p}_{model}(x;\theta) + c$
where $c$ is an approximation to $- log Z(\theta)$
$c$ is treated as just another parameter and estimated along with $\theta$
The resulting model density is not a true prob. dist., but will converge to one.
ML would set $c$ to infinity.
**NCE reduces learning $p(x)$ to learning a probabilistic binary classifier in which we predict if the data is from the model or not.**
The other class is the **noise distribution**, which is easy to sample from and is sampled with $.5$ probability.
$p_{train}$ samples y=0 or y=1 with equal probability (0 is noise, 1 is data).
The goal is to fit $p_{joint}$ to $p_{train}$ with supervised maximum likelihood wrt $\theta$ and $c$
$p_{joint}$ is de facto logistic regression on difference between pmodel and pnoise.
NCE typically learns good at first and slows down, it greedily picks a good feature to focus on and does not learn many 'backups'. It is not great with many random variables

### Estimating the Partition Function
...
#### Annealed Importance Sampling
...

## 19. Approximate Inference
(This chapter is math heavy, see the text or my green notebook)
Exact inference in multi-layered models has exponential complexity.
Intractable inference usually due to interactions b/t latent vars ('explaining away')
### Inference as Optimization 
Need log-prob of observed data $log p(v;\theta)$, so you need to integrate out all latent variables $h$.
Instead compute **evidence lower bound (ELBO)** $\L(v, \theta, q)$, which is equalt to the `TRUE - KL_DIV( q(h|v) || p(h|v,theta))`
	When the divergence approaches zero, the bound is tight.
The optimization problem is to find the distribution `q` that maximizes `L`.

### EM
...
M too expensive in deep networks.

### MAP Inference & Sparse Coding

### Variational Inference
Maximize `L` over __restricted family__ of `q`, which makes computing expectation of log-joint easy under `q`, usually by **having `q` factorize** (mean-field)
...
> Specically, the mean eldxed-point equations dened a recurrent neural network. The task of this networkis to perform inference. We have described how to derive this network from amodel description, but it is also possible to train the inference network directly.
> We can thus think of unitias attempting to encode the residualerror invgiven the code of the other units. We can thus think of sparse coding as an iterative autoencoder, which repeatedly encodes and decodes its input, attemptingto x mistakes in the reconstruction after each iteration

Approximate Inference introduces feed-back and leads to self-fulfilling prophecies and it is hard to gauge to how much extent.
### Learned Apprx. Inference


## 20. Generative Models
### Boltzmann Machines
#### RBMs
### DBNs
### DBMs
### BMs for Real values
### Convolutional BMs
### BMs for Structured Outputs
### Backprop through Random Ops
> The requirement thatfbe continuous and dierentiable of course requiresyto be continuous. If we wish to back-propagate through a sampling process thatproduces discrete-valued samples, it may still be possible to estimate a gradient on, using reinforcement learning algorithms such as variants of the REINFORCEalgorithm (Williams, 1992), discussed in section 20.9.1.
> REINFORCE-based estimators can be understood as estimating the gradientby correlating choices ofywith corresponding values ofJ(y). If a good value ofyis unlikely under the current parametrization, it might take a long time to obtain itby chance and get the required signal that this conguration should be reinforced.
### Directed Generative Nets
> One cannot simply back-propagatethrough the output of the inference network, but instead must use the relativelyunreliable machinery for back-propagating through discrete sampling processes,as described in section 20.9.1.

#### Diff. Generator Networks.
> In the case of generative modeling, the learning procedure needs to determine howto arrange z space in a useful way and additionally how to map from z to x.

#### VAEs
1. Draw z from $p_{model}$
2. Compute g(z)
3. Sample x from $p_{model}(x; g(z)) = p_{model}(x | z)$.
BUT: while training $z$ is drawn from an 'approximate inference netowrk' or 'encoder' and the same p_model is used and is interpreted as a 'decoder'
Train on a variational lower bound. The first term is the approximate joint log-likelihood. The second term is the entropy of the approximate posterior. Objective is partially to **increase the this entropy term, encouraging model to place mass on many z values and prevent mode collapse.**
> Traditional approaches to variational inference and learning infer q via an optimization algorithm, typically iterated fixed-point equations ... The main idea behind the variational autoencoder is to train aparametric encoder (also sometimes called an inference network or recognitionmodel) that produces the parameters of q. As long aszis a continuous variable, wecan then back-propagate through samples ofzdrawn from q(z | x) to obtain a gradient with respect to. Learning then consists solely of maximizing L with respect to the parameters of the encoder and decoder.
Main drawback of VAE is that samples are blurry (due to increasing that entropy term??)
Another drawback is that `g` is probably not factorized and we cannot specify a subset of `z` (unless we are willing to marginalize).
VAE is good at learning manifolds.
#### GANs
Simplest formulation is with a zero-sum game with a payoff function $v(\theta^{g}, \theta^{d})$ and its complement determine loss for discriminator and generator respectively. Each player tries to maximize own payoff, converges to $g^* = arg\ min_g \ max_d \ v(g,d)$. v(.,.) could be `expected_data log d(x) + expected_model log(1-d(x))`
GANs require neither approximate inference nor approximation of a partition function gradient. Under a convexity assumption, convergence is expected. 
Can also setup GAN payoff to be equivalent to ML assuming the discriminator is optimal.
Better GAN payoff scheme: 
  - Generator aims to increase log-prob that D makes mistake, rather then aiming to decrease prob D makes correct.
  - This formulation causes derivative of G's cost function wrt D's logits to __remain high even when D confidently rejects G's samples__.
[Conditional GANs](https://arxiv.org/pdf/1411.1784.pdf)
Use dropout in D.


#### Generative Moment Matching Nets
#### Convolutional Generative Nets
#### Autoregressive Nets
### Sampling from Autoencoders
### Generative Stochastic Networks
### Others

