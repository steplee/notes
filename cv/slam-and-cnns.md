# My Thoughts
  - For detectors and dense predictors alike we should eliminate all FC layers, they are too expensive. This seems like it shouldn't degrade performance because we only ever care about local properties of images. Classification needs to consider global structure (FCs help), but detection doesn't (e.g. roads don't move)
  - Look further into training rotationally invariant kernels.
  - Pretraining can be slow, fine-tuning must be quick, inference/search/alignment must be very quick.

# Aerial Localization by Matching Intersections (Costea)
1. Pixelwise classification by applying CNN at each 10th pixel
2. Detect intersections from detected roads
3. Uniquely identify intersections based on traditional features / sparse matching
4. Geometric alignment & adjust road fittings
#### 1.
Uses global conv net (LG-Net), which uses VGG for local features, AlexNet for global features.
Local receptive field is 64x64, 'global' is actually only 256x256.
Looks like it combines by concat & 2x FC layers.
#### 2.
Detection of intersections is done by tuning AlexNet on a binary classification task on whether the center point is an intersection or not.
#### 3.
Feature descriptors for intersections are learned. Equivalent detected intersections & labelled OSM intersections **should have similar features**, but **different intersections should have different descriptors**
Extraction is done similar to [this paper](http://www.iis.sinica.edu.tw/~kevinlin311.tw/cvprw15.pdf), [notes below](#Deep-Learning-of-Hash-Codes-for-Fast-Image-Retrieval), although they mention training also with a Siamese net to encourage same intersections & away from different ones, and using a margin-loss.
#### 4.
to read.

# Deep Learning of Hash Codes for Fast Image Retrieval
1. Pretrain on ImageNet
2. Fine-tune to learn, at the same time, domain-specific features & hash-like functions
3. Retrieval by deep hierarchical search (coarse to fine)
  - Coarse level uses binary codes, fine level uses L2 distance between another layer's activations.

### My Thoughts
If only training to classify, the sufficient learned information need not be visually similar, only up to the same class. Instead, train an encoder-decoder to reconstruct entire image.

# FCN for Aerial (Sherrah)

# SuperPoint (DeTone)

# FutureMapping / Spatial AI (Davison)
SLAM is heading from sparse/feature to dense/convnet.
