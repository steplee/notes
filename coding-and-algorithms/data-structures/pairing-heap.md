# [Paring Heap](http://www.cs.cmu.edu/~sleator/papers/pairing-heaps.pdf)
 - For decrease-key and delete to be fast we need to represent the heap in the *'child-sibiling representation'*, where every node stores **a pointer to left-most child, and a right pointer to its next older sibiling**, and a parent pointer.
 - This allows, and forces, to order the children of every node. We end up with a **heap-ordered tree that is also a half-ordered binary tree**, with empty right subtree. Half-ordered means the key of any node is at least as small as the key of any node in its left subtree.
 - A diagram shows compression to two pointers: the the *left-pointer* will optionally point to a child, the *right-pointer* will point to the sibiling to the right, or the parent if you are the right-most child. The right-pointer is per node, not per level.

##### Extract Min
  - Delete the root, we have `O(n)` subtrees (amoritized to `O(lgn)`), we must link them in a particular order.
  - Do potential based analysis where each a node with d children in an n node heap has potential `1 - min[d, srqt(n)]`. Note it is always non-negative when summed over children.
  - I didn't quite follow the rest of the procedure (and didn't finish reading the analysis). They mention __pairing by most-recent__ order, then choosing root to satisfy the usual heap property. How do sibilings key odrders come into play?

