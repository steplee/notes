# Solving Linear Systems

There are two methodolgies: 1) exact, 2) iterative methods

## Exact Methods
### Gaussian Elimination

## Iterative
### Jacobi
$$x^{k+1} = D^{-1}(b - Rxk)$$
where D and R are *diagonal* and *remainder* of matrix A.
### Gauss-Seidel
must be PSD & Symmetric.
### Krylov Subspace
Umbrella for several big-name techniques: _conjugate gradient_, conjugate residual, Lanczos biorthogonalization, ...
Does not need to see the system in it's entirity, _only matrix-vector products for chose vectors_. *(TODO: Relation to signal processing?)*

## Schur
#### Schur Polynomial
[wiki](https://en.wikipedia.org/wiki/Schur_polynomial)
