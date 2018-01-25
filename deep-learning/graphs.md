# [Graph Attention Networks]()
  - Graph Neural Networks propagate node states until equilibrium is reached, which produces an output at each state
  - More recent work used GRUs to gate the iterative propagation.
  - But how do we apply *convolutions* to the Graph domain?
    - **Spectral approaches** work in the spectral/Fourier domain after performing an eigendecomposition of the graph Laplacian. The filters learned are specific to the graph's structure.
    - **Non-spectral approaches** perform convolutions directly on the graph. The challenge is to define filters that work on multiple sizes of neighbor-sets, while sharing weights like in CNNs.
  - *Self-attention* is using attention on a single sequence, it decodes and directs attention on it's own.
  
### 2. GATs
  - Each node has features
  - A GAT layer takes in the features from each node and creates new features, with the same dimensionality but a different cardinality, i.e. there is no 1-to-1 correspondance b/t features:nodes anymore.
    - First a matrix mult is applied to each node with some weights.
    - Second attention coeffs are computed for __pairs__ of output features. **The graph structure comes into play by only computing coeffs in some neighborhood**
    - Third compute a seperate softmax for each node of its neighborhood to determine ...

