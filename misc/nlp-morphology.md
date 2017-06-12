# Morphology & Parsing
[Chapter](http://ling.umd.edu/~idsardi/620/Jurafsky/jurafsky2000-3.pdf)

#### FSA : recognizer
 $\sigma$ is set of recognized strings
 $Q$ is set of states
 $F$ is set of final states (i.e. letters)
 $\delta$ is transition from letter-to-letter
 isomorphic to regular expressions
#### FST : translator
 $\sigma$ is set of pairs
 $Q$ is set of states
 isomorphic to **regular relations**
 
 Can be **inverted** $T(T^{-1})$, switches input-output
 	- FST-parser $\iff$ FST-generator
 Can be **composed** $T_1 \circle T_2$
 	- allows conceptual simplification

 i.e. map "cats" $\rightarrow$ "cat +N +PL"

##### Tapes
Conceptualize FST as having two tapes:
	1) Upper tape (*lexical*)
		- the a in (a:b) pairs
	2) Lower tape (*surface*)
		- the b in (a:b) pairs

"default pairs" when input and output alphabets are the same ~ a : a

(page 74)
