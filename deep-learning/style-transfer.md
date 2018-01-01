# Style Transfer

# [2015 Breakout Paper](file:///home/slee/Documents/dl/style-transfer.pdf)
Decompose images as content and style. Style is represented as correlations of feature activations of filters at different layers.

Treat the image itself as the parmeters to be tuned. Minimize a balance of two losses:
  1. Content reconstruction
  2. Style loss derived from difference bt image and style-template filter correlations.

# [2017 Survey]()

Two main approaches:
  1. Descripive with Image Iteration
    - Further divided into Maximum Mean Discrepancy and MRF methods
    - MMD
      - MMD is a metric b/t distributions based on mean in Hilbert space (kernelized, e.g. via Gram matrices)
      - Using the Gram matrix for the loss is equivalent to the second-order poly kernel
    - MRF
      - MRF w/ prior to localize semantic content to original area

  2. Generative with Model Iteration
    - Have a second CNN assess performance of a generator net.

Improvement to Gatys:
  - To preserve colors of content image (not style image) do style loss only on a luminance channel.

Improving Generative methods:
  - Replace batch normalization with instance normalizataion


