# [Stam Classic Paper](http://www.dgp.toronto.edu/people/stam/reality/Research/pdf/GDC03.pdf)
  - Navier Stokes is a second-order equation, so we end up simulating a two fields: the velocity and the density.
  - The density equation is **linear**, the velocity equation is notoriously) **non-linear**

#### Density Field
  1. Add sources
  2. Diffuse
  3. Advect

###### Diffusion
Naive interpolate-with-neighbors diffusion __will not work__, it is too unstable, density values oscillate and diverge. Instead, model as linear system with unknowns `x[,]` and find a solution such that when diffusing backwards you get the same densities you started with (e.g. multiplying by a matrix and then inverting is identity). To be tractable (this is a very small, sparse matrix), use Gauss-Seidel iteration.

###### Advection
> Similarly to the diffusion step we could set up a linear system and solve [advection] using GaussSeidel relaxation. However, the resulting linear equations would now depend on the velocity, making it trickier to solve. Fortunately, there is an alternative which is more effective. The key idea behind this new technique is that moving densities would be easy to solve if the density were modeled as a set of particles. In this case we would simply have to trace the particles though the velocity field.
The problem is that we then have to convert these particles back to grid values. How to properly do that is not necessarily obvious. A better method is to find the particles which over a single time step end up exactly at the grid cell’s centers as shown in Figure 6 (c). The amount of density that these particles carry is simply obtained by linearly interpolating the density at their starting location from the four closest neighbors. This suggests the following update procedure for the density.  __Start with two grids: one that contains the density values from the previous time step and one that will contain the new values.__ For each grid cell of the latter we trace the cell’s center position backwards through the velocity field. We then linearly interpolate from the grid of previous density values and assign this value to the current grid cell.

#### Velocity Field
There are three drivers: user forces, diffusion, and self-advection.

We have to add an additional constraint, carried out in function `project`, to force the field to be *mass-conserving*, which builds vortices.
> To achieve this we use a result from pure mathematics called the Hodge decomposition: every velocity field is the sum of a mass conserving field and a gradient field. 

The figures provided show that the:
  - Incompressible field pushes arrows in trails and is divergence free (I think)
  - Gradient field pushes arrows out from each point in a straight line (like a terrain map)

> Computing the gradient is then equivalent to computing a height field. Once we have this height field we can subtract its gradient from our velocity field to get a mass conserving one as shown in Figure 7 (bottom). We will not go into the hairy mathematical details, but will simply state that computing the height field involves the solution of some linear system called a Poisson equation. This system is sparse and we can re-use our Gauss-Seidel relaxation code developed for the density diffusion step to solve it. 


# [GPU Gems Chapter](https://www.cs.cmu.edu/~kmcrane/Projects/GPUFluid/paper.pdf)
### 30.3 Rendering

# [Dynamic Particle Level Set](http://nishitalab.org/user/nis/cdrom/ievc/ievcMatuda.pdf)
  - Fluids with different properties in the same grid (air, water, etc.) need to have boundaries tracked.
    - One way: level set method, which tracks interfaces by tracking zero-valued points of the *level set function*, which is maintained by updating wrt. the advection function. But this can lose accuracy.
    - Good way: particle level set methods, which put particles at interfaces and update independent of the level set function.
  - We need to dynamically delete/add particles, so textures not suitable, use VBO instead.


# [Online Notes](http://www2.cs.uregina.ca/~anima/408/Notes/Gas/Fluids.htm)
