# WYAH
[Link](http://dev.stephendiehl.com/fun/)

## 6 : Hindley-Milner Inference
 	- family of type systems
	- infer types by unification
	- a well structured program always has unique *principle type*

	- When you don't know a type, guess, collect constraints, and see if you can eliminate possibilities
		- Classic example of iterating search and inference.
	
#### Aside
I have a lot of questions about defining a grammar via a vanilla recursive algebraic data type vs. via F-algebras. There seems to be pluses and minuses to both approaches. **When should you choose one over the other??**
	- Vanilla ADTs:
		+ simpler
		+ faster
		- must write duplicate code
		- no recursion schemes
	- F-algebra
		+ recursion schemes
		+ derive Functor
		- slow
		- more complex (but also simpler in a sense)

### Polymorphism
```Haskell
-- I think this is right ...

(.) :: (b->c) -> (a->b) -> (a->c)
fmap :: (a->b) -> f a -> f b
forall f g. fmap f . fmap g = fmap (f . g)
	    fmap (f . fmap g)
	    fmap (f (fmap g))
	    fmap (fmap . (f g))
	    id (fmap . (f g))
	    fmap . (f g)
	    fmap (f . g)
```

### Types
Type schemes ( ) model polymorphic types
```
newtype TypeEnv = TypeEnv (Map.Map Var Scheme)
data Type = ...
data Scheme = Forall [TVar] Type
```
"The typing context or environment is the central container around which all information during the inference process is stored and queried. In Haskell our implementation will simply be a newtype wrapper around a Map of Var to Scheme types."
"The two primary operations are extension and restriction which introduce or remove named quantities from the context."

#### Inference Monad
Contains all logic for type inference. ExceptT + StateT.
`runInfer :: Infer (Subst, Type) -> Either TypeError Scheme`
returns `Right $ closeOver res`

We will need to *query free variables* and *apply substitutions*.
Apply a subst will remove the variable from the set of free vars.

It appears there is double of everything -- one for variables as you'd expect, **and another for types**. Type variables behave a lot like value variables. We can query, subst them.
Diehl implements Substitutions via a map, and abstracts via a typeclass. Scheme, List, and TypeEnv are instances.

two expressions e,e' unifiable if [s]e = [s]e'
s is the 'unifier'
