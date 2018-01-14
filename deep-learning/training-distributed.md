# Distributed Training

## [Asynchronouse SGD]()
  - Workers request parameters from *parameter servers*.
  - Workers compute minibatch gradients and send to parameter servers.
  - Parameter servers atomically take SGD step.
  - Note: Workers receive new params when they ask for them, but by the time they are done the params are **stale**.
       - The effects of stale parameters depends on architecture, latency, goal, etc.

## [Synchronouse SGD]()
  - Parameter server averages all gradients reported by workers, which sync every iteration.
  - The averaging is exactly like having a bigger, distributed mini-batch.
  - Disadvantage is that we moving as slow as the slowest machine per batch.

## [Parallel Hyperparameter Search]()
  - Each worker trains a model with different hyperparams, no gradient aggregation.
