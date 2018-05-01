# Knowledge Graphs
## [Review Paper](https://arxiv.org/pdf/1503.00759.pdf)
> There are two main classes of SRL techniques: those that capture the correlation between the nodes/edges using latent variables, and those that capture the correlation directly using statistical models based on the observable properties of the graph.

### 2. Intro to KGs
#### Representation of Knowledge
RDF: `<subject, predicate, object>`
#### Open v Closed assumption
Closed World Assumption: Non-existing RDF triplets indicate **false** facts
Open World Assumption: Non-existing RDF triplets indicate **unknown** facts
#### KG construction
Semi-supervised (regexs and learned rules) are key to scaling
Schema-based vs Schema-free
#### KG usages
#### Tasks
 - *Link Prediction*: Given entities and relations, which edges should we fill in?
 - *Entity Resolution/Linkage*: Identification, deduplicatication
 - *Clustering*: Cluster by features and links, also community detection.


### 3. SRL for KGs
#### Probablistic KGs
RDF Triplets represented as rank 3 tensor. Space is huge, but types of enitites/relations greatly restrict space of relations and the tensor is pretty sparse anyways.
Notation: $y_{ijk} = 1$ iff triple $(e_i, r_k, e_j)$ exists.
#### Statistical Properties of KGs
 - *Homophily/Autocorrelation*: entities with like features tend to share more similar relations
 - *Block structure*
 - *Global/Long-Range dependencides*: e.g. being born in Boston probably means you are a US citizen
#### SRL Models
Focus on three types:
  1. **Latent Feature**: all `y_ijk` cond. independent given **latent** features and model params
  2. **Graph Feature**: all `y_ijk` cond. independent given **graph** features and model params
  3. **Markov Random Fields**: all `y_ijk` have local interactions

(1) and (2) predict existence of $x_{ijk}$ by a learned score function $f(x_{ijk}; \Theta)$. The dataset tensor $\underline{T}$ is modelled as a triple product Bernoulli conditioned on $f$
There are many choices for the score function and optimizing it under a non-probablistic (margin, etc.) loss.

(1) Will learn latent feature-vectors that go with each entity. (2) uses __graph edges alone__ for all predictions.

### 4. Latent Feature Models
> The key intuition behind relational latent feature models is that the relationships between entities can be derived from interactions of their latent features.

#### RESCAL: A bilinear model
$e_i \mathbf{W_k} e_j$
Now $W_k$ specifies how strong relation `k` is between entities. Subject/Object entities share reps.
Training/learning invovles *jointly* learning the weight matrix and latent features.

**Semantic Embedding**: Learning the latent features gives us a similarity metric on entities, can be used for clustering, kernel machines, etc.

Rescal is related to tensor factorization methods and recommendation techniques.
> Fitting the model: If we want to compute a probabilistic > model, the parameters of RESCAL can be estimated by > minimizing the log-loss using gradient-based methods such as stochastic gradient descent [68]. RESCAL can also be computed as a score-based model, which has the main advantage that we can estimate the parameters Θ very efficiently: Due to its tensor structure and due to the sparsity of the data, it has been shown that the RESCAL model can be computed via a sequence of efficient closed-form updates when using the squared-loss [63, 64]. In this setting, it has been shown analytically that a single update of E and Wk scales linearly with the number of entities Ne, linearly with the number of relations Nr, and linearly with the number of observed triples, i.e., the number of non-zero entries in Y. We call this RESCAL-**ALS**. RESCAL-ALS is __very fast and scalable__.

#### (other) Tensor Factorization Models
CP Tensor factorization
#### Matrix Factorization Methods
Reshape tensor `e . e . r` to `e*e . r` where rows are subject-object pairs, then do a matrix factorization. Loses information.
#### MLPs
concat two entities -> run thru MLP -> matrix multiply (per relation or global) -> another non-linearity + reshape -> inner product with (per-relation or global) weight vector
#### Neural Tensor Networks
#### Latent Distance Models
Predict links on entities with small distance in latent space.
#### Summary:

### 5. Graph Feature Models
#### Similarity for uni-relational data
#### Rule Mining
#### Path Ranking Algorithm

### 6. Hybrid
#### Additive relational effects
#### Other hybrids

### 6. Training SRL models on KGs
#### Penalized MLE
#### Negative examples?
#### Pairwise loss models
#### Model Selection

### 7. MRFs
#### Representation
#### Inference
#### Learning
#### Summary

### 9. Knowledge Vault: Constructing KGs

### 10. Extensions
#### Non-binary Relations
#### Hard Constraints
#### New entites
#### Querying Probablistic KGs

### 11. Conclusion
