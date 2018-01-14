There are many kinds of perceptual loss functions.

# [Style & SR with Perceptual Loss Functions](https://cs.stanford.edu/people/jcjohns/papers/eccv16/JohnsonECCV16.pdf)
  - Most image generation models use a pixel-wise error.
    - Note: we are talking about generator nets *and* optimization of pixel values.
    - Pixel-wise error is not how humans judge quality however.
    - Pixel-wise error requires computing per pixel (obviously)
  - This paper proposes to use a loss function over higher-level features.
  - Train feed-forward **transformation networks** with **perceptual loss functions** from a pretrained **loss network**

  - The image transform net is feed-forward (deep resnet). The loss net is pretrained and feed-forward and all errors are counted here. 
    - For style: the style and content are piped into the loss net, not the transform net.
    - For SR: the losses are derived from the ground truth high res image.

#### Image Transform Nets
 - Use strided/fractionally-strided conv layers, __no pooling__.
 - ResNet-like with batch-norm.
 - ReLU except last layer which is scaled tanh in range [0..255]
 - Down/Upsampling for SR:
   - for factor of f, use residual blocks followed by logf conv layers with stride 1/2.
   - Other papers propose bicuic interp, then deconv. But in this paper, upsampling is learned.
 - Down/Upsampling for Style:
   - Downsampling is followed by upsampling. This allows the network to spend its capacity on larger structures at a higher receptive field size.

#### Perceptal Loss Nets
  - Feature Reconstruction Loss:
    - Loss not incurred at final output (what would be per pixel), but at intermediate layers.
    - Euclidean distance. Loss at lower-layers forces reproduction, loss at higher-layers will not preserve texture, color, etc. but will still force spatial structure.
  - Style Reconstruction Loss:
    - Squared Frobenius norm of he difference between Gram matrices of output and target images.
    - Minimization encourages correllations of different feature maps to be the same in source/target images.


# [SRGAN](https://arxiv.org/pdf/1609.04802.pdf)
  - Minimizing MSE maximizies PSNR, but PSNR is not what humans focus on.
  - Propose to use a deep ResNet with GAN perceptual loss.
  - Train a generator as a feed-forward CNN
  - Loss is a composite of content, advesarial GAN, VGG activations. Similar to Johnson paper, but with advesarial loss added.
