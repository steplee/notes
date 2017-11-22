# 23. Strongly Connected Components

# Tarjan's algorithm
A low-link approach.
Start at a root. Maintain stack of visited nodes when setting low-value.

On low-link backup (after visting all children and setting low-value)
  - if there is a back-edge then pop all nodes up to the back-node and add them all to a new scc.
    Pop the stack until popped node is current node. (See psuedo-code)
    Also, set the value to the back-node's dfs-number as usual.
  - if no more children are left, then pop this node off stack and add it as it's own scc.
    Also, set this node's low-val to $\infinity$ so that no cross-edges have any effect.

This SCC decomposition leads to a **metagraph**, a _dag_, which can be labelled in the order that they are found.
It has nodes as SCCs and edges as (directed) weakly connected components.
This dag is a _(reverse) topological order_, so no need to use a topo. sort algorithm.
A lot of problems require a topo order of the metagraph.
_Beware of parallel arcs!_

### Implementing
Need:
  - `pre` array for prefix number per node. This can be used to know if vertex visited.
  - `preorderCounter`
  - `id` vector for the found SCC index
  - `low` array for low-link data
  - `stack` for dfs  history

When explore node:
  - Set dfs number
  - Visit children
  - Set low value
  - If low == pre: 
```
      while (true)
          v = pop stack 
          set v's SCC to id.size()
          if u == v: break
```

