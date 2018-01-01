# Object Detection with CNNs
## [Fast R-CNN]()
#### Recap of original R-CNN
  1. fine-tune on proposals using log-loss. 
  2. Fit SVM to CNN features, replacing the softmax learnt by fine-tuning.
  3. Learn bounding-box regressors

Requires days of GPU training, hundreds of gigabytes of storage for features. Has slow test time as well (forward pass per class).

#### New Architecture
...
