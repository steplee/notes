# Some Specific Architectures

## [Pixel CNN](https://arxiv.org/pdf/1601.06759.pdf)
  - Generative
  - Predict pixels sequentially by XY, fast recurrent layers + residual connections
 
## [mixup](https://arxiv.org/pdf/1710.09412.pdf)
  - Draw $\lambda$ from a beta distribution, use it to interpolate both labels & inputs from two randomly drawn training examples.
  - All deep nets share two commonalities:
  	1. Trained to with ERM principle
	2. Network scales linearly with number of training examples
  - VC theory: ERM convergence guaranteed if size of learning machine doesn't increase with number of parameters (and VC-complexity by extension)
  - ERM may lead to *memorization* not *generalization*. ERM usually inaccurate on *adversarial inputs*, even chosen very close to input training manifold.
  - One solution: __augment data: 'Vicinal Risk Minimization'__.
  	- BUT: this requires a human to say which augmentations are valid (e.g. for an image: reflections, shears, etc.)
  - Another solution: __mixup augmentations__: blend two original training examples (and labels)
  - Most mixup-ped example pairs should have different labels
  - (Might this be like crossing in genetic algorithms? Mixups explore underrepresented areas of the input manifold.)

## [Breaking Down the Softmax Bottleneck](https://arxiv.org/pdf/1711.03953.pdf)
  - Formulate language modeling as matrix factorization, show softmax models bottlenecked by softmax layer => NLP w/ distributed embeddings is limited by last layer!
  - RNN NLP Modeling in a nutshell:
  	1. RNN consumes sentence to fixed-size vector, each step is matmul w/ embeddings
	2. These 'logits' pushed through softmax
> We show that learning a Softmax-based recurrent language model with the standard formulation is essentially equivalent to solving a matrix factorization problem. More importantly, due to the fact that natural language is highly context-dependent, the matrix to be factorized can be high-rank. This further implies that standard Softmax-based language models with distributed (output) word embeddings do not have enough capacity to model natural language. We call this the Softmax bottleneck.

Uhhh... why?

  - Rather than softmax, __Mixutre of Softmaxes__, which learns matrices with larger normalized singular values => much higher rank.
  - Language Modeling by softmax: Predict word `x` given context `c`, using embeddings `w` and with context `c` represented by hidden auto-regressive state vectors `h`
  	- The paper has matrices `H`, `W` for a matrix of `h`, `w` as row vectors stacked vertically. There is also $A_ij$ for $log\ P*(x_j | c_i)$*
  	- Paper proceeds to define $F(A)$, an infinite set of matrices that correspond to all possible logits of the true data distribution.
	- Main question: is there some $\theta$ that parameterizes `H` and `W` such that `H` times `W'` factorizes any `B` in $F(A)$ ???
		- Answer: if embedding dim `d` >= rank(`B`), then yes

  - Authors posit log prob matrix `A` is high-rank (due to context-dependency, and learning complexity)
	  - You *could*
  		1. Use non-parametric model
		2. Use higher dim embeddings
	  - BUT: too expensive
	  - Instead: MoS
  - MoS maintains `K` `h` representations and uses a weighted average of them as the output.
  - Bad alternative: MixtureOfContexts: maintain `K` `h` representations, but average them *before* softmax.
  	- DOES NOT fix low rank problem: average the softmaxes outside is key.

##### Follow up [blog post](http://smerity.com/articles/2017/mixture_of_softmaxes.html)
  - Low-rank matrices common in RNNs because `rank(AB)` is the minimum of component ranks.
  - Taking a sum of softmax outputs at each RNN step makes it more likely the average is not low rank.



## [DiracNet](https://arxiv.org/pdf/1706.00388.pdf)
  - Deep w/ skip connections became popular.
  	- These nets may be just an ensemble of shallower nets
	- ResNet widening is more effective than deepening
	- But deeper may be more efficent than shallower and wider
  - Deep nets w/ skip connections suffer from:
    1. Feature reuse: upper layers may not learn useful reps given lower layers
    2. Widening is more effective then deepening after a certain depth
    3. Actual depth =/= model depth: it might be determined by shortest path (taking skip paths)
  - DiracNets: try to avoid skip connections

Like ResNet, parametrize weights as residual of Dirac function (but without skipcon). Convolving any input with Dirac => identity, so info propagates deep into network and alleviates vanishing grads.

... finish ...

## [ResNets](https://arxiv.org/pdf/1512.03385.pdf)
> When deeper networks are able to start converging, a degradation problem has been exposed: with the network depth increasing, accuracy gets saturated (which might be unsurprising) and then degrades rapidly. Unexpectedly, such degradation is not caused by overfitting, and adding more layers to a suitably deep model leads to higher training error.
There exists a solution by construction to the deeper model: the added layers are identity mapping, and the other layers are copied from the learned shallower model. The existence of this constructed solution indicates that a deeper model should produce no higher training error than its shallower counterpart.

See paper for some formulas/graphs.
> We hypothesize that it is easier to optimize the residual mapping than to optimize the original, unreferenced mapping. To the extreme, if an identity mapping were optimal, it would be easier to push the residual to zero than to fit an identity mapping by a stack of nonlinear layers.
The formulation of F(x) +x can be realized by feedforward neural networks with “shortcut connections”. Shortcut connections are those skipping one or more layers. In our case, the shortcut connections simply perform identity mapping, and their outputs are added to the outputs of the stacked layers.

Deep nets lose information amongst all their parameters and error-assignment is foobarred. If we could provide a mechanism for layers to pass info directly through, adding more layers would not hurt performance.
I think they are saying we want to perform identity mapping, but this is hard for whatever nonlinearity+bias we are using to create, so explicity add it after the layer and we our layer can learn to output **0** which is much easier (0 matrix & 0 bias).

The authors compare deep residual nets with shortcut connections to multi-grid PDE methods (in which different grid scales are responsible for residual solution from coarser -> finer). They further mention hierarchical basis preconditioning which rely on variables that represent residual vectors between scales.
**Highway-networks** are similar to ResNest but have gating functions for allowing/preventing shortcut connections.

> In real cases, it is unlikely that identity mappings are optimal, but our reformulation may help to precondition the problem. If the optimal function is closer to an identity mapping than to a zero mapping, it should be easier for the solver to find the perturbations with reference to an identity mapping, than to learn the function as a new one. We show by experiments (Fig. 7) that the learned residual functions in general have small responses, suggesting that identity mappings provide reasonable preconditioning.

...


