# CSPs and Back-Tracking
[Good survey on backtracking](https://cs.uwaterloo.ca/~vanbeek/Publications/survey06.pdf)

**CSPs**: Variables, Values, Constraints

## Naive Back Tracking
 - DFS -> search tree
 - Requires _branching strategy_: the method of determining which node to extend next.
 - Prune subtrees that violate constraints.
 - If a node is a _deadend_, backtrack to parent (recurisvely)

A node is _extended_ by picking a free variable and assigning it a value (_posting_: `x = a` along a branch).
Search corresponds to iterated posting and backtracking (_rectracting_ postings).

More generally, a node in a search tree is a set of _branching constraints_, with extension adding more branches, cutting out a solution or deadend.
The order of adding branches is a heuristic and is **vital to running time**.

> Usually, branching strategies consist of posting unary constraints. In this case, a variable
 ordering heuristic is used to select the next variable to branch on and the ordering of
 the branches is determined by a value ordering heuristic (see Section 4.6).

Popular branching strategies relating to *unary* constraints:
  1. Enumeration
      - Try all in parallel
      - a.k.a. **d-way branching**
  2. Binary choice points
      - Pick e.g. x = 1 and x /= 1 and try in parallel
      - a.k.a. **2-way branching**
  3. Domain Splitting
      - Variable not instantiated, but *domain of values is reduced*

These are all equivalent if domain is binary (SAT)

**Variable Ordering**: Choosing variables to post next.
**Value Ordering**: Rank domain values to be extended to next. Note: we are not concerned with what *variable* to be expanded, but for a *given variable* the next *value* to be posted.

Value ordering _does not matter_ for d-way branching, but it is _substantial_ for 2-way branching.
Consider Variable Elimination in graphical models.

## Constraint Propagation
> A fundamental insight in improving the performance of backtracking algorithms on CSPs
is that local inconsistencies can lead to much thrashing or unproductive search [47, 89].
A local inconsistency is an instantiation of some of the variables that satisfies the relevant
constraints but cannot be extended to one or more additional variables and so cannot be
part of any solution. (Local inconsistencies are nogoods; see Section 4.4.) If we are using
a backtracking search to find a solution, such an inconsistency can be the reason for many
deadends in the search and cause much futile search effort.

> A generic scheme to maintain a level of local consistency in a backtracking search is
to perform constraint propagation at each node in the search tree. **Constraint propagation
algorithms remove local inconsistencies by posting additional constraints that rule out or
remove the inconsistencies.** When used during search, constraints are posted at nodes as
the search progresses deeper in the tree. But upon backtracking over a node, the constraints
that were posted at that node must be retracted.

We propagate restrictions that are demanded by ancestor's constaints to descendents of the
search tree to *cut down the cardinality of future variable's domains*.

(pick up at pg 92)
