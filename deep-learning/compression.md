# [Block Transforms for Signals](https://web.njit.edu/~akansu/PAPERS/Akansu-LiuOnSignalDecomposition-SPIE-OptEngJuly1991.pdf)
  - Signal Decomposition === Representing a signal by superposition of bases.
  - Block Tranforms === Decompositions which limit duration of basis functions to the number of bands in the filter bank.
  - Block transform bases not chosen for frequency, but orhogonality properties. Aliasing is usually bad. Therefore the coefficients of transformed data are not commonly used as the subbands since they had poor freq performance. But it is efficient.
  - Multires analysis has become important, allows time & frequency to be localized & analyze. Block transforms can be extended to multires.
    - The input is block transformed into `N_1` bands. Each band transformed into `N_ij` for `i = 1...N_1`, and `j` is the size of the transform performed on each `i` band. Repeat this process until sufficient features attained.
  - ...

### Half-Band Freq Split (PR-QMF)
> Aside: A *tap* is a FIR filter input component (e.g. `x[n-i]`

  - Half-band filters split the signal into high & low freq components. This pattern is popular.
  - 
# [EndToEnd Optimization of Nonlinear Codes for Compression](https://arxiv.org/pdf/1607.05006.pdf)
  - Most lossy compression is based on the pipeline `Transform -> Quantize -> Encode`

# [Real-Time Adaptive Compression](https://arxiv.org/pdf/1705.05823.pdf)
  - Toderici uses RNNs to find binary representations and entropy encode.
  - Johnston uses loss weighted SSIM & spatially adaptive bit allocation.
  - Pied Piper lmao

# [Generative Compression](https://arxiv.org/pdf/1703.01467.pdf)
