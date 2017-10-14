# Parsing Language
## Projective / Non-projective
See [wiki](https://en.wikipedia.org/wiki/Discontinuity_(linguistics)
See [graph based parsing slides](http://demo.clab.cs.cmu.edu/fa2015-11711/images/6/66/Graph-based.pdf)

For arc-factored model, optimal dependency parse of a tree **is same as max weighted spanning tree** in graph with edge-weights as arc-scores
**Eisner's algorithm** (modification to CYK) finds optimal *projective* max spanning tree.
To find optimal *non-projective* max span. tree, use **Chu-Liu-Edmonds algorithm**
Chu-Liu-Edmonds essentially looks for a cycle, collapses it, recurses until tree.
**Dual decomposition**
