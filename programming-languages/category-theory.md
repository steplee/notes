# Category Theory

## Adjunctions
[Catsters](https://www.youtube.com/watch?v=loOJxIOmShE&list=PL54B49729E5102248&index=1)
	- Categories C,D not equivalent, but there is an *interesting* relationship
	- Could have isomorphism (equivalence): 
		$$1_C = GF 
	          FG = 1_D$$
	- **Adjunction**: We don't have full equivalence, we have natural transformations, not isomorphisms (with laws):
		$$1_C \rightarrow GF    
		  FG \rightarrow 1_D$$

$F -| G$ : F is left-adjoint to G.

It is a pair of natural transformations (**unit, counit**):
$$\eta: 1_C \rightarrow GF
 \epsilon: FG \rightarrow 1_D$$

F -> FGF   -- using $\eta$
FGF -> F   -- using $\epsilon$


