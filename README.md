# ChaosLab 1.0
### Exploring Nonlinear Dynamics and Deterministic Chaos

ChaosLab is a computational mathematics project that investigates the behaviour of nonlinear dynamical systems through numerical simulation and visualisation.

The project focuses on the **logistic map**, a discrete-time mathematical model capable of exhibiting stable equilibria, periodic behaviour, bifurcations and deterministic chaos.

The computational implementation uses C++ for numerical simulation and Python for data processing and graphical visualisation.

---

## 1. Mathematical Foundations

### 1.1 The Logistic Map

The logistic map is defined by the recurrence relation:

$$
x_{n+1}=rx_n(1-x_n)
$$

Where:

- $x_n$ represents the state of the system at iteration $n$.
- $r$ is the control parameter.
- $x_{n+1}$ represents the subsequent state.

For the parameter range:

$$
0\leq r\leq 4
$$

and an initial condition:

$$
0\leq x_0\leq 1
$$

the system exhibits several distinct dynamical behaviours depending on the value of $r$.

### 1.2 Bifurcation Analysis

A bifurcation occurs when a small change in a system parameter produces a qualitative change in its long-term behaviour.

For the logistic map, increasing $r$ produces a sequence of dynamical transitions:

- Stable fixed-point behaviour.
- Periodic oscillations.
- Period doubling.
- Increasingly complex dynamics.
- Chaotic behaviour, interspersed with periodic windows.

A bifurcation diagram visualises these transitions by plotting the long-term states against the control parameter.

### 1.3 Lyapunov Exponent

The Lyapunov exponent measures the average exponential rate of separation between initially nearby trajectories.

For a one-dimensional discrete dynamical system:

$$
x_{n+1}=f(x_n)
$$

the Lyapunov exponent is defined as:

$$
\lambda=
\lim_{N\rightarrow\infty}
\frac{1}{N}
\sum_{n=0}^{N-1}
\ln|f'(x_n)|
$$

For the logistic map:

$$
f'(x_n)=r(1-2x_n)
$$

Therefore:

$$
\boxed{
\lambda=
\lim_{N\rightarrow\infty}
\frac{1}{N}
\sum_{n=0}^{N-1}
\ln|r(1-2x_n)|
}
$$

The Lyapunov exponent provides an important numerical indicator of dynamical behaviour:

| Lyapunov exponent | Interpretation |
|---|---|
| $\lambda<0$ | Local contraction of nearby trajectories |
| $\lambda=0$ | Neutral stability or a dynamical boundary |
| $\lambda>0$ | Exponential sensitivity to initial conditions |

A positive Lyapunov exponent is a characteristic indicator of chaos in the relevant dynamical regime.

---

## 2. Computational Methodology

### C++ — Numerical Computation

The C++ implementation handles the mathematical calculations.

The primary functions are:

**`logisticMap()`**

Computes one iteration of the logistic recurrence relation.

**`simulate()`**

Generates a trajectory from a specified initial condition and control parameter.

The generated vector contains the initial state followed by all subsequent states.

**`calculateLyapunov()`**

Computes a numerical estimate of the Lyapunov exponent.

The implementation separates the simulation into two intervals:

1. Transient iterations, which are discarded.
2. Measurement iterations, which contribute to the exponent calculation.

This helps reduce the influence of initial conditions on the numerical estimate.

### Python — Data Processing and Visualisation

Python is used to process the generated CSV files and produce graphical representations of the experiments.

The visualisation scripts use:

- NumPy for numerical data processing.
- Matplotlib for graphical representation.
- pathlib for filesystem path handling.

---

## 3. Project Structure

```text
ChaosLab/
│
├── src/
│   └── LogisticMath.cpp
│
├── visualisation/
│   ├── VisualizeBifurcation.py
│   ├── VisualizeLyapunov.py
│   └── VisualizeSensitivity.py
│
├── README.md
├── requirements.txt
└── .gitignore
```

---

## 4. Experiments

### 4.1 Bifurcation Diagram

Investigates the long-term behaviour of the logistic map as the control parameter changes.

The experiment stores the long-term states corresponding to different values of $r$.

The resulting CSV contains:

| Column | Description |
|---|---|
| `r` | Logistic map control parameter |
| `Iteration` | Simulation iteration |
| `State` | Corresponding system state |

The Python visualiser produces a bifurcation diagram.

### 4.2 Lyapunov Exponent Sweep

Computes the Lyapunov exponent over a range of control parameters.

Current simulation configuration:

| Parameter | Value |
|---|---:|
| Initial condition | 0.2 |
| Minimum $r$ | 2.5 |
| Maximum $r$ | 4.0 |
| Parameter increment | 0.005 |
| Transient iterations | 1,000 |
| Measurement iterations | 10,000 |

The resulting CSV contains:

| Column | Description |
|---|---|
| `r` | Control parameter |
| `lyapunov_exponent` | Numerically estimated Lyapunov exponent |

The visualisation plots the exponent against $r$, with a horizontal reference line at $\lambda=0$.

### 4.3 Sensitivity to Initial Conditions

Investigates the evolution of two trajectories beginning from nearby initial conditions.

The separation is calculated as:

$$
\Delta_n=
|x_n^{(a)}-x_n^{(b)}|
$$

The experiment visualises both trajectories and their absolute separation.

A logarithmic vertical scale is used to make changes across different orders of magnitude easier to observe.

---

## 5. Installation and Requirements

### C++

A C++ compiler supporting C++11 or later is required.

The numerical implementation uses standard C++ libraries.

### Python

Install the required dependencies:

```bash
pip install -r requirements.txt
```

The requirements are:

```text
numpy
matplotlib
```

---

## 6. Execution

Compile the C++ implementation:

```bash
g++ -std=c++11 src/LogisticMath.cpp -o ChaosLab
```

Run the executable:

```bash
./ChaosLab
```

On Windows:

```bash
ChaosLab.exe
```

The active implementation generates:

```text
lyapunov_plotting.csv
```

Run the corresponding visualisation script:

```bash
python visualisation/VisualizeLyapunov.py
```

**Note:** The bifurcation and sensitivity visualisation scripts require their respective CSV datasets. Their corresponding data-generating experiments are separate from the currently active Lyapunov parameter-sweep entry point.

---

## 7. Reproducibility

ChaosLab separates numerical computation from graphical visualisation.

The C++ implementation generates numerical datasets, while Python processes those datasets independently.

This separation allows experiments to be repeated with different parameters without requiring changes to the visualisation pipeline.

Generated CSV datasets and PNG figures are not included in the source repository. They can be regenerated by running the corresponding experiments.

---

## 8. Project Scope

ChaosLab 1.0 is an experimental implementation focused on the numerical investigation of the logistic map.

It provides a foundation for exploring:

- Nonlinear discrete dynamical systems.
- Stability and periodicity.
- Bifurcation behaviour.
- Lyapunov exponents.
- Sensitivity to initial conditions.
- Numerical computation and scientific visualisation.

The project is intended as an exploration of computational mathematics and deterministic chaos.

---

---

## Copyright

Copyright © 2026 Asinak Goswami.

All rights reserved.

This project is currently provided without an open-source license.
No permission is granted to copy, modify, distribute, or use this
software without prior written permission from the copyright holder.

---

**ChaosLab 1.0 — Computational exploration of deterministic chaos.**


