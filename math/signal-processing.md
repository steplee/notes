# Signal Processing
[TODO: read](http://inis.jinr.ru/sl/tot_ra/0/0/3/Rugh-Nonlin.pdf)

## Volterra and Wiener Series
[Link](http://www.scholarpedia.org/article/Volterra_and_Wiener_series)

Traditional signal processing analyses LTI systems, but Volterra generalized to drop linearity.

LTI Systems express, _uniquely_, an output by a linear transformation of the input, **equivalent** to a **convolution of the input signal**.

Volterra extended the representation to nonlinear signals by adding a series of nonlinear integral operators.
$$ y(t) = H_0x(t) + H_1x(t) + ... $$
Each $H_nx(t)$ is an integral over $$\mathbb{R}^n$$, integrating over x evaluated at _all time lags_ $\tau_n$ and multiplied by $h^{(n)}(\tau_1, ..., \tau_n)$.

The $h$ multi-argument functions are **Volterra Kernels**
The support of a Volterra kernel defines memory of the system: larger support = longer influences.

*Volterra Series ~ Taylor Series with memory*

> The output of two different functionals in a Volterra series is usually not orthogonal, i.e., their respective output time series are correlated. They can be orthogonalized by a procedure which is very similar to a Gram-Schmidt orthogonalization which is, however, only valid in the average case over all inputs. As a consequence, one has to assign a probability to all input signals, i.e., one has to define a stochastic process over which the Volterra functionals are orthogonalised in terms of
> the correlation between their output over all possible inputs. The resulting functionals are sums of Volterra functionals of different order, or nonhomogeneous Volterra functionals. [Called a Wiener process]

In reality, you are given input/output signals and must minimize some error (integral sq. error usually), so estimating Volterra Kernels ~ solution of set of integral equations, usually impossible, Wiener operators being mutually uncorrelated can be estimated independently assuming signals are a Wiener process.

> A further reason for the popularity of the Wiener series is that the leading Wiener kernels can be directly measured via the crosscorrelation method of Lee and Schetzen (1965). If one uses Gaussian white noise with standard deviation A instead of the Wiener process as input, the leading Wiener kernel can be estimated as the cross-correlations [equations shown]

TODO: finish article
