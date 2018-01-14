# [Deep Image Prior](https://sites.skoltech.ru/app/data/uploads/sites/25/2017/12/deep_image_prior.pdf)
> For instance, the authors of [32] recently showed that the same image classification network that generalizes well when trained on genuine data can also overfit when presented with random labels.  Thus, generalization requires the structure of the network to “resonate” with the structure of the data.
In this work, we show that, contrary to expectations, a great deal of image statistics are captured by the structure of a convolutional image generator rather than by any learned capability.
  - Apply a CNN (encoder+decoder) to do inverse problems (restoration, inpainting, etc.), but **only train it on the single corrupted image**, __the structure aids the restoration process__.
  - Nothing is *learned* in a traditional sense, randomly initialize the weights & fit to single image & minimize a __task-dependent regularization objective__.
  - Use traditional energy minimization problem `x* = min_x [  E(x, x0) + R(x) ]`
    - Traditionally `E` is the task-dependent energy, `R` is a regualarizer such as *Total Variation*
    - **Instead, replace `R` with an implicit prior captured by the CNN's structure**
      - `0* = argmin_0 [  E(f_0(z); x0) ]`, `x* = f_0*(z)`
        - `0*` is chosen using SGD
        - Result is given as `x* = f_0*(z)`
        - Optimization over `z` is also possible, but authors keep it random.

  - It is true that a CNN can produce unreal images, even random noise, but fitting to the corrupted image has a suprisingly large effect at making the network 'resist bad solutions'

###### Basic Task: Reconstructing an Image
Minimize pixel-wise sq. error
> The parametrization offers high impedance to noise and low impedance to signal.
The resulting prior then corresponds to projection onto a reduced set of images that can be produced from z by ConvNets with parameters θ that are not too far from the random initialization θ0.

...
