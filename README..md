# Optical Flow Estimation Project

## Project Overview
This project focuses on the **estimation of optical flow**—a technique to compute the apparent motion of objects, surfaces, and edges between two consecutive frames of an image sequence caused by the relative motion between the observer and the scene.

Two primary methods are implemented and explored:
1. **Horn-Schunck Method** (a global method)
2. **Lucas-Kanade Method** (a local method)

The project also introduces a hybrid approach that combines the strengths of both.

---

## Mathematical Formulations

### 1. Optical Flow Constraint Equation (OFCE)
The intensity of pixels remains constant during motion:
\[
I_x(p)u + I_y(p)v + I_t(p) = 0
\]
where:
- \(I_x, I_y, I_t\) are the spatial and temporal intensity gradients.
- \(u, v\) are the components of the velocity vector.

---

### 2. Horn-Schunck Regularization
The Horn-Schunck method assumes smoothness in the flow field by minimizing the following energy function:
\[
E(u, v) = \int_\Omega \left( (I_x u + I_y v + I_t)^2 + \alpha \left( \|\nabla u\|^2 + \|\nabla v\|^2 \right) \right) d\Omega
\]
where:
- \(\alpha\) is a regularization parameter.
- \(\nabla u, \nabla v\) are gradients of the flow field components.

---

### 3. Lucas-Kanade Local Estimation
The Lucas-Kanade method assumes a constant flow within a local window:
\[
E_{LK} = \sum_{i} \left( I_{xi} u + I_{yi} v + I_{ti} \right)^2
\]
This results in solving:
\[
\begin{bmatrix}
\sum I_x^2 & \sum I_x I_y \\
\sum I_x I_y & \sum I_y^2
\end{bmatrix}
\begin{bmatrix}
u \\
v
\end{bmatrix}
=
\begin{bmatrix}
-\sum I_x I_t \\
-\sum I_y I_t
\end{bmatrix}
\]

---

### 4. Hybrid Approach
The hybrid approach combines the smoothness constraint of Horn-Schunck with the localized robustness of Lucas-Kanade using Gaussian-weighted convolution:
\[
E(V) = \int_\Omega \left( V \cdot (W * (\nabla I \nabla I^T)) V^T + \alpha (\|\nabla u\|^2 + \|\nabla v\|^2) \right) d\Omega
\]
where:
- \(W\) is a Gaussian filter.

---

## Implementation Highlights

### Programming Languages
- **C** for core computation.
- **MATLAB** for visualization.

### Features
- Partial derivative estimation using finite difference and Gaussian smoothing.
- Iterative minimization for velocity computation.
- Multi-resolution pyramids for faster computation and handling large motions.

---

## Visual Demos

### 1. Zero Padding Example
Illustrates boundary handling during derivative computation:
![Zero Padding Example](path/to/zero_padding_image.png)

### 2. Vector Field Visualization
Resultant optical flow vectors displayed using MATLAB's `quiver`:
![Vector Field](path/to/vector_field_image.png)

### 3. Multi-resolution Pyramids
Under-sampling and over-sampling for efficient computation:
![Pyramids](path/to/pyramids_image.png)

---

## Known Issues and Improvements
### Challenges:
- Handling boundary conditions during subsampling.
- Ensuring robustness in noise-prone regions.

### Proposed Enhancements:
- Adaptive regularization parameter \(\alpha\).
- Improved hybrid methods using machine learning.
