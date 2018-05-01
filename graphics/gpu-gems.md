# GPU Gems

## 20. GPU Importance Sampling
[Link](https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch20.html)

## 24. Being Linear
[Link](https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch24.html)

> Light transport is linear. The illumination contributions from two light sources in a scene will sum. They will not multiply, subtract, or interfere with each other in unobvious ways.

**Monitors are nonlinear, renderers are linear**

> Gamma correction is the practice of applying the inverse of the monitor transformation to the image pixels before they're displayed. That is, if we raise pixel values to the power 1/gamma before display, then the display implicitly raising to the power gamma will exactly cancel it out, resulting, overall, in a linear response.
> The usual implementation is to have your windowing systems apply color-correction lookup tables (LUTs) that incorporate gamma correction. This adjustment allows all rendering, compositing, or other image manipulation to use linear math and for any linear-scanned images, paintings, or rendered images to be displayed correctly.

Can't use LUTs for games, we don't know consumer's monitor and applications would mismatch (why?)

> All modern GPUs support sRGB texture formats. These formats allow binding gamma-corrected pixel data directly as a texture with proper gamma applied by the hardware before the results of texture fetches are used for shading.
> Texture lookups can apply inverse gamma correction so that the rest of your shader is working with linear values. However, using an sRGB texture is faster, allows proper linear texture filtering (GeForce 8 and later), and requires no extra shader code.
> The last step before display is to gamma-correct the final pixel values so that when they're displayed on a monitor with nonlinear response, the image looks "correct." Specifying an sRGB frame buffer leaves the correction to the GPU, and no changes to shaders are required. Any value returned in the shader is gamma-corrected before storage in the frame buffer (or render-to-texture buffer). Furthermore, on GeForce 8-class and later hardware, if blending is enabled, the previously stored value is converted back to linear before blending and the result of the blend is gamma-corrected. Alpha values are not gamma-corrected when sRGB buffers are enabled. If sRGB buffers are not available, you can use the more costly solution of custom shader code, as shown in Listing 24-2; however, any blending, if enabled, will be computed incorrectly.



