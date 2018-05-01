# [Survey (2003-2016)](https://ipsjcva.springeropen.com/articles/10.1186/s41074-017-0027-2)
These are only rough notees, see below for notes on the papers themselves.
#### MonoSLAM
  - 6 DoF camera and all keypoints as state vector in EKF.
  - Map initialized by known object. This defines the coordinate frame as well.
  - Not scalable: EKF state vector too large
#### PTAM
  - Split tracking & mapping to two threads
  - Bundle Adjustment for mapping, after triangulation of feature correspondances
  - Tracking is near real-time. BA estimated points projected into 2d, camera pose estimated
  - BA is applied to *keyframes* (when enough change has gone on), and is applied locally & globaly (to close loops)
  - Map initialized w/ five-point algorithm (finds epipolar geometry of two frames using 5 points)
  - Relocalization w/ tree-based classifer of key frame based on features.
### Global Map Optimization
There is a large divide between BA & Bayes Filter approaches [see here for excellent comparison](https://www.doc.ic.ac.uk/~ajd/Publications/strasdat_etal_ivc2012.pdf).

BA can be used for GMO, but it suffers from local minima. **Pose-Graph Optimization** avoids this by **closing loops**. Stereo has the benefit of always knowing the scale, Monocular systems do not, scale drift occurs, and thus they need to perform __global bundle adjustment__ and estimate 7 DoF (with scale included).
#### ORB-SLAM
  - This system does Pose Graph Optimization, loop closing, and 7 DoF camera estimation.
#### DTAM
  - First direct method.
  - Initialize map by aligning stereo measurement with model of environment
  - Camera motion estimated by optimizing synthetic view & aligning to measurements
  - Depth estimation by stereo, then optimizing wrt space continuity
#### LSD-SLAM
  - Direct w/ semi-dense visual odometry
    - Semi-dense in that it only considers areas with textures of high gradients
    - Semi-dense VO is **not** globally consistent, that is where LSD-SLAM comes in.
  - Does 7 DoF pose-graph opt & loop closure detection.
  - Works like this:
    - Random vales set as initial depth for each pixel
    - Camera motion estimated w/ synthetic view generation of high gradient areas
    - 7 DoF PGO
  - Can run real-time on just CPU
#### SVO & DSO
  - Semi-*direct* Visual Odometry (**note**: direct not dense)
    - Track with features
    - Map with direct methods
    - Camera motion estimated by minimizing photometric error
    - Sparse version of DTAM/LSD-SLAM
  - Direct Sparse Odometry
    - Fully direct (tracking & mapping)
    - Block image & calibrate mapping.
    - Not globally consistent, therefore it is VO, not SLAM.
#### RGB-D SLAM
  - Scale is known, even with monocular camera.
  - Usually an __iterative closest point__ algorithm is used to estimate motion.
  - Then environment reconstructed (BA??)
##### KinectFusion
  - Combine depth maps in voxel space, ICP estimates 3d structure.
  - Many many points cause slowdown, but real-time on GPU.
##### SLAM++
  - Object oriented SLAM (haha)
  - Starts with database of 3D objects, tries to find & align them to measured points.
### Open Problems
  - Pure Rotation
  - Map Initialization
  - Estimating Intrinsic Camera Parameters
  - Rolling Shutter Distortion
  - Scale Ambiguity


# Sparse / Feature-based

## [MonoSLAM](https://www.doc.ic.ac.uk/~ajd/Publications/davison_etal_pami2007.pdf), [ROS implementation](https://github.com/rrg-polito/mono-slam)
  - Notes on ROS Implementation pdf
  - VSLAM has two approaches:
    - BA
    - Filtering (dense, sparse, or semantic)
  - This implementation uses **active search**. Features are only matched if they are consistent with estimated movement (pdf under Gaussian is within `s` stddevs). Old features are discarded.
  - Patch matching with cross-correllation matched filter. Patches blurred based on predicted translation to account for motion-blur.
  - **1 Point RANSAC**: First select low-innovation inliers, then select high-innovation inliers. Consensus set given by inliers which __agree with the EKF__ (this incorporation of EKF prediciton is special). 
    - The high-innovation inliers are selected after partially updating the EKF, based only upon the low-innovation inliers. They are used to perform a second EKF update.
  - Inverse Depth Coding ...

## PTAM
  - In addition to the description given above:
  - New points are initialized with epipolar search
  - Previous systems go through great hassle to prevent data-association errors (active search, ransac, etc.), and still are not robust enough. Using BA and keyframe vs. incremental mapping helps.
  - Tracking by local bundle adjustment over last `N` frames.

## [ORB-SLAM](https://arxiv.org/pdf/1502.00956.pdf)

## ORB-SLAM 2 [slides](https://cseweb.ucsd.edu/classes/sp17/cse252C-a/CSE252C_20170503.pdf)

## [SLAM++](https://www.doc.ic.ac.uk/~ajd/Publications/salas-moreno_etal_cvpr2013.pdf)
### Note: SLAM++ is also the name of a nonlinear least squares solver (no relation afaict), [here](https://arxiv.org/pdf/1608.03037.pdf)

# Dense
## LSD-SLAM

## DPAM

