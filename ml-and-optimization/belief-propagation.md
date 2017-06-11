# Belief Propagtion

## Vanilla BP

Exact Inference on trees.
'Non-Serial' Dynamic Programming on trees.
The essential message-passing algorithm in machine learning.
Heavily tied to many other algorithms, BP is in a sense the unified algorithm for many others:
  * Forward-Backward (for HMMs)
  * Sum-Product
  * Junction Tree (when a tree)
  * Kalman Filter
  * ...

Is a local -> global algorithm:

Two phases:
  1) Bottom Up:
      Starting at leaves propagate 'evidence' upward.
      A parent will take a SUM of states over the PRODUCT of belief messages from children.
      Evidence is weighted by:
        * unary belief of state
        * binary (compatibility) of my state and EACH child states
        * belief of child that he is in that state.

  2) Top Down:
      Propagate info from parents to children after accumulating evidence from them in the bottom up stage.
      Children will ...

## Junction Tree

Exact inference on *arbitrary* graphs, though running time is *exponetnial in tree-width*.
Recall, graphs:
  - Must have edges added such that they are **chordal**.
  - Should be thought of as **clique nodes** in two types: **cliques** and **seperators**.
      - cliques are nodes with interesting information.
      - seperators are for computation.
      - If a node is in two cliques, it is in any connecting path between them.
  - Marginals/Modes calculated as a division of product of cliques over product of seperators.

## Generalizations

Many message-passing (*many*) machine learning algorithms are a special case of BP.
But some notable generalizations are ...

## Considerations to investigate
  - Can I imagine taking any data structures / algorithms on trees and applying them?
      - dynamic graphs (link-cut, etc.)
      - decompositions (centroid, heavy-light)
      - more dynamic programming
      - convex hull opt.
