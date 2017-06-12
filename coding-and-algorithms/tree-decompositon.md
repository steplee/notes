# Tree Decompositions

## Centroid Decomposition
See [this Algorithms Live video](https://www.youtube.com/watch?v=3pk02p1-weU)

- A tree *centroid* is a node that, when removed, maximizes the remaining two components
  - It/they must be either the **single center** or **two middle nodes**.

Can be used for divide and conquer approaches: 
  1) Solve problem for all paths going through some node
  2) Remove node
  3) Solve sub-problems recursively

#### Ex. problem: Yin-Yang Paths
find all balanced paths.

__Approach:__
  - Root tree at centroid.
  - Solve recursively.
    - Store array starting at root, all elements will be accessed. But when solving sub-problems, 
      only at-most half will be accessed, times the number of components that the centroid shatters.
    - Actually need two arrays, one for current recursion level that will replace the other when all children-components considered.
    - Each child-component shattered by a centroid will look at its sibiling-components, count # of balanced paths
      (e.g. [-1,2] ~ [-2,5] corresponds to 1 balanced path due to 2 and -2)
    - Then, update table and repeat on children-components.

## Heavy Light Decomposition
