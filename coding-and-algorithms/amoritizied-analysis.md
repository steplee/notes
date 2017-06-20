# Amoritized Analysis
## CLRS (Chap. 17)

Bound $\sum a_i$ by $\sum t_i$ where $a_i$ is amoritized cost and $t_i$ is real cost.
Costs only considered in sequences.
Prove bounds on average running-time *of* the worst case, **not** the average case.

### Aggregate Analysis
	- All operations considered to be same running time.
	- Multipop stack example: can only be O(n) since can only pop what you push.
### Banker / Accounting
	- Different operations can have different running times
	- Difference of $a_i - t_i$ is *credit*, that can help 'pay' for future operations
	- "Total credit must be non-negative at all times"
		- Negative credit is like undercharging earlier operations with the promise of paying them off.
	- Stack example
		- Pushing uses one dollar *immediately*
		- Popping has no charge, we use credit (we take the dollar off the plate at the top of the stack)
		- "charging push operation a little bit more, we can charge pop nothing"
		- there is always a positive number of credit since pushing adds one dollar.
### Physicist / Potential
	-
### Dynamic Tables


## Okasaki
