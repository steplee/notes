# [Auto-Encoding Variatonal Bayes](https://arxiv.org/pdf/1312.6114.pdf)
> *How can we perform efficient inference and learning in directed probabilistic models, in the presence of continuous latent variables with intractable posterior distributions, and large datasets? We introduce a stochastic variational inference and learning algorithm that scales to large datasets and, under some mild differentiability conditions, even works in the intractable case. Our contributions is two-fold. First, we show that a reparameterization of the variational lower bound yields a lower bound estimator that can be straightforwardly optimized using standard stochastic gradient methods. Second, we show that for i.i.d. datasets with continuous latent variables per datapoint, posterior inference can be made especially efficient by fitting an approximate inference model (also called a recognition model) to the intractable posterior using the proposed lower bound estimator. Theoretical advantages are reflected in experimental results.*

Posit a $q_{\phi}(z|x)$ approximation to the true $p_{\theta}(z|x)$. Learn $\phi$ jointly with $\theta$. Unlike in Mean Field VI, `q` is not factorial and may be arbitrarily complex (a neural network in case of VAEs).
$z$ is like the code, $q$ the encoder, $p_{\theta}$ the decoder, $x$ the data.

Marginal (log-)likelihood is a sum over individual marginal log-likelihoods of individual datapoints, each of which can be rewritten as `KL( q(z|xi) || p(z|xi) ) + LBO(theta,phi, xi)`
The KL term is non-negative, we optimize the LBO wrt theta and phi, but the gradient wrt phi is high variance under an MC estimate.

(Math heavy, see paper)

Auxliary distribtion need be one of:
	1. Tractable CDF
	2. "location-scale" family such as Normal, Laplacian, etc.
	3. Compositional (in terms of transformations of aux variables), such as Log-Normal, Gamma, etc.

# [Stochastic Backprop](https://arxiv.org/pdf/1401.4082.pdf)
> We marry ideas from deep neural networks and approximate Bayesian inference to derive a generalised class of deep, directed generative models, endowed with a new algorithm for scalable inference and learning. Our algorithm introduces a recognition model to represent an approximate posterior distribution and uses this for optimisation of a variational lower bound. We develop stochastic backpropagation rules for gradient backpropagation through stochastic variables and derive an algorithm that allows for joint optimisation  of the parameters of both the generative and recognition models. We demonstrate on several real-world data sets that by using stochastic backpropagation and variational inference, we obtain models that are able to generate realistic samples of data, allow for accurate imputations of missing data, and  provide a useful tool for high-dimensional data visualisation.

(Too math heavy, but I will write some important observations).

`L` layers in the stack, generative process starts at the top.
The top activation $h_L$ is **sampled**
All other activations $h_1 \ldots h_{L-1}$ are **computed by transforming above activations** by a non-linear transformation then perturbing with Gaussian noise.
$T_l$ will represent the MLPs at each layer.
$G_l$ are the matrices at each layer.
$\pi(v|.)$ is a distribution over data with parameters specified by a transformation of the first latent layer.
$\theta^g$ or just $\theta$ will represent the parameters of maps $T_l$ and matrices $G_l$

The generative process is this:
	1. Sample an $\Epsilon$ standard Gaussian vector **for every** layer.
	2. Sample $h_{L} = G_L \Epsilon_L$
	3. Compute $h_l = T_l(h_{l+1}) + G_l \Epsilon_l$  for every layer.
	4. Finally, draw the visible sample $v ~ \pi(v | T_0(h_1))$

Conditionals $p(h_l | h_{l+1})$ are defined by (3) and have mean $\mu_l = T_l(h_{l+1})$ and covariance $S_l = G_l G_l'$

You can parameterize joint b/t hidden & visible in two ways.
DLGMs generalize factor analysis, non-linear FA, non-linear Gaussian belief net

Gradient descent in a latent variable model typically involves $\nabla_{\theta} \mathbb{E}_{q_{\theta}}[f(\Epsilon)]$, which is difficult to compute (__but not for gaussians__).
A general rule for multivariate-gaussian gradients through any function $f$ can be derived for a 'modified backprop', though it requires Hessian (paper reduces this need to something for only O(nn) computation required).

A general rule for any exp. family is also given. Also, SBP can be derived for any __invertible smooth transformation of a base distribution__

##### 4. Scalable Inference in DLGMs
denote $V$ for full dataset with `N x D` $v_n$ observations.
> To perform inference in DLGMs we must integrate out the effect of any latent variables  this requires us to compute the integrated or marginal likelihood. In general, this will be an intractable integration and instead we optimise a lower bound on the marginal likelihood. We introduce an approximate posterior distribution q(.) and apply Jensens inequality following the variational principle 

(Math similar to AEVB paper follows)
Again, two terms:
	1. KL-Divergence b/t variational dist. (q) and prior (p), this term is a regularizer
	2. A reconstruction error (an (negative) expectation under q of $p(V | \Epsilon, \tehta) * p(\theta)$

Recall recognizer $q(\Epsilon | v)$ does not factorize like MeanField, __but it does factor across layers__, that is the conditional of a single $v$ is a product over layers.

...
