# Generative Models

## (Lecture 3)[http://www.cs.toronto.edu/~duvenaud/courses/csc2541/slides/lec3-autoregressive.pdf]
  - (Density Estimation w/ Real NVP)[https://arxiv.org/pdf/1605.08803.pdf]
    - Turn latent $z$ into more interesting shapes using **bijective function**
    - Bijectivity allows fast computation through change of vars formula
        - You need the determinant of the Jacobian.
        - __the det of a triangular matrix is just product of diagonals!__
        - So Real NVP is to use **affine coupling layers**, which are triangular w/ triangular jacobians.
    - TODO read the section about nonlinear ICA again
