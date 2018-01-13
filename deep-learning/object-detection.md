# Object Detection with CNNs
## [Fast R-CNN]()
#### Recap of original R-CNN
  1. fine-tune on proposals using log-loss. 
  2. Fit SVM to CNN features, replacing the softmax learnt by fine-tuning.
  3. Learn bounding-box regressors

Requires days of GPU training, hundreds of gigabytes of storage for features. Has slow test time as well (forward pass per class).

#### New Architecture


## [Karpathy Thesis](http://cs.stanford.edu/people/karpathy/main.pdf)
###### Generating Sentences from Images
Past Methods:
  - Detect objects and patch together n-grams.
  - Extract `<object, action, scene>` pairs, form simple phrase.
  - Map images and sentences to *meaning space*, find closest pairs.

This Method:
  - End-to-end
