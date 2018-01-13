# GANs
## [Original GAN Paper]()
> In NCE, as in GANs, a discriminative training criterion is employed to fit a generative model.

> To learn the generator’s distribution pg over data x, we define a prior on input noise variables pz(z), then represent a mapping to data space as G(z; θg), where G is a differentiable function represented by a multilayer perceptron with parameters θg. We also define a second multilayer perceptron D(x; θd) that outputs a single scalar. D(x) represents the probability that x came from the data rather than pg. We train D to maximize the probability of assigning the correct label to both training examples and samples from G. We simultaneously train G to minimize log(1 − D(G(z)))

> In practice, equation 1 may not provide sufficient gradient for G to learn well. Early in learning, when G is poor, D can reject samples with high confidence because they are clearly different from the training data. In this case, log(1 − D(G(z))) saturates. Rather than training G to minimize log(1 − D(G(z))) we can train G to maximize log D(G(z)).

GANs do not use a pixel-wise similarity function so they are much more flexible and capable of generating new structures.

## [Conditional GAN]()

Original GAN sampling could generate from any mode after sampling `z`, CGANs allow a way to pick a mode using say the label of an MNIST digit. This approach is flexible, the conditioning data could be any modality or neural code.

`G` is presented both `z ~ pz(z)` and y: `G(z|y)`
`D` is presented both `x` __and__ `y`:   `D(x|y)`
(This could be implemented by giving input to both nets as simple vector concatenation)

## [DCGAN](https://arxiv.org/pdf/1511.06434.pdf)

This paper proposes constraints on Conv GANs that help stability.
GANs do not naively scale to large CNNs. Progressively upscaling is usually done.
This paper proposes further tips:
  1. Do not use pooling, but strided convolutions
  2. Cut out all FC layers. Use the convolution features or *global average pooling*
  3. Use batch normalization
  4. Use ReLU in the generator, excpet the last layer use Tanh
  5. Use LeakyReLU in the discriminator


## [EBGAN](https://arxiv.org/pdf/1609.03126.pdf)
  - Use a GAN to train an EBM. Assign low energy to areas of high probability.
  - The discriminator being an energy function allows a lot of models to use it.

> The term contrastive sample is often used to refer to a data point causing an energy pull-up, such as the incorrect Y ’s in supervised learning and points from low data density regions in unsupervised learning.  

  - The Discriminator is to be viewed as an energy function with no other probablisitc interpretation.
  - EBGAN incorporates a hinge loss.
  - ...



## [InfoGAN](https://arxiv.org/pdf/1606.03657v1.pdf)
This paper has a lot of interesting discussion about latent variables and coding.




## [Wasserstein GAN]()

This paper has a good discussion on MLE and generative modelling in general.

Generative models trained with MLE (tradition) fiddle with a noise term so that MLE does not overfit and such. Introducing a distribution parameterized by `theta` and `z` and training with learned apprx. inference is closer to what we really want, but still not exactly. This gets us to VAEs. **To get to GANs, we completely give up the noise term**, which is __gives us additionly flexibility in the objective__, although we gain instability.

This paper focuses on measuring how similar two distributions are.
The __Earth-Mover__ distance is like the optimal cost of a plan to transport input `x` to `y`, where one 'plan' is used over all inputs.

(pick up on pg 4)

## [NVIDIA Progressive Growing GANS]()
`G` and `D` are mirror images, add new layers as training progresses, fade them in by weighting low at first.

Since GANs may capture just a subset of variation, **Minibatch Discrimination** has been suggested. It computes feature statistic across a minibatch (not just one image). This is done by having an extra layer that runs on all images in a minibatch, producing features per image in minibatch and handing them to `D`. This paper proposes a simplication (there are also other methods to increase variance)

> Our simplified solution has neither learnable parameters nor new hyperparameters. We first compute the standard deviation for each feature in each spatial location over the minibatch. We then average these estimates over all features and spatial locations to arrive at a single value. We replicate the value and concatenate it to all spatial locations and over the minibatch, yielding one additional (constant) feature map. This layer could be inserted anywhere in the network, but we have found it best to insert it towards the end

Batch Normalization to fix covariate shift may not be important, but they think it is needed for constraining magnitudes (the competition b/t networks increases magnitude greatly).


## [Cycle GAN]()
