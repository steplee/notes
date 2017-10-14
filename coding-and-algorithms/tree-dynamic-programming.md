# DP on Trees
[Link](https://threads-iiith.quora.com/Dynamic-Programming-on-Trees-Tutorial)

In these problems you usually root the tree at some arbitrary (or given) vertex.
Sometimes if order truly matters, you will need to do a _second pass_ to fix the
assumption you made by rooting the tree.
For example, in Belief Propagation you need to do forward and backward passes.

## 1.
### Aside: simple dp on an array
We have an array a[]. We want to know max sum of non-adjacent elements.
Simple DP solution is to build array b[] with recurrence: `b[i] = max( b[i-2]+a[i] , b[i-1] )`
I.e. at each position `i`, you either take it (and add pred-pred) or do not (and take previous)

Now to do this on trees where we cannot take adjacent-leveled nodes (i.e. parent and child).
Form a dp table where we either take node u (and sum of children's children) or take the max of u's children.
```dp[u] = max(
  sum of dp[c] for all children of u,
  value[u] + sum of dp[cc] for all cc of all children of u)
```
Or more efficiently, create two tables:
```dp1[u] = value[u] + sum dp2[c] for children of u
dp2[u] = sum max[dp1[c],dp2[c]]
// then pick max(dp1[root], dp2[root])
```
To compute this, do a dfs and on post set dp1/dp2 for current node based on children.

## 2. Diameter
Keep tables `f` and `g`.
  - `f` is the longest depth-wise path through vertex `u` to a leaf. Hence it has `u` as an *endpoint*
  - `g` is longest path that goes *through* `u` and has endpoints at two ancestors.
```f[u] = 1 + max[f[c]] for all children c of u
g[u] = 1 + f[c1] + f[c2] where c1/c2 chosen as argmax of f over children of u
// then pick max of them at root for final answer
```

## 3.
