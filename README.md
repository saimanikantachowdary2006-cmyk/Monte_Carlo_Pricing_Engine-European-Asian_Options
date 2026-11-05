Asian Option Pricing & Greeks via Monte Carlo with Antithetic Variates (C++)
A C++ program that prices an arithmetic-average Asian call option using Monte Carlo simulation with antithetic variates for variance reduction, and estimates its Greeks (Delta, Gamma, Vega) via finite differences with common random numbers.

Overview
This program:

Simulates GBM stock paths and prices an arithmetic-average Asian call option using Monte Carlo.

Uses antithetic variates: for each simulated shock Z, a mirror path using −Z is also generated. This pairs positively correlated paths and reduces the variance of the estimator at essentially no extra cost.

Estimates the option's Delta, Gamma, and Vega using central finite differences.

Uses a fixed RNG seed across all bumped revaluations — common random numbers (CRN) — so the same random paths are reused, dramatically stabilizing the finite-difference Greeks.

Model
1. Asian option price (Monte Carlo + antithetic variates)
Stock price evolution (Euler discretization of GBM):

text
S_{t+dt} = S_t + r * S_t * dt + sigma * S_t * sqrt(dt) * Z,   Z ~ N(0,1)
For each path drawn with Z, a paired antithetic path is simulated with −Z:

text
Path A:  S1_{t+dt} = S1_t + r·S1_t·dt + sigma·S1_t·√dt·Z
Path B:  S2_{t+dt} = S2_t + r·S2_t·dt + sigma·S2_t·√dt·(−Z)
Arithmetic average and payoff per path:

text
A = (1 / steps) * sum_{t=1}^{steps} S_t
payoff = max(A − K, 0)
Price estimate (averaged over all simulations paths, i.e. simulations/2 antithetic pairs):

text
Asian price = exp(-r * T) * (1 / simulations) * sum(payoffs)
Because each iteration produces two payoffs (payoff1 + payoff2), the loop runs simulations / 2 times while still averaging over simulations total paths.

2. Greeks via central finite differences
Greek	Formula
Delta	Δ = [V(S0 + h) − V(S0 − h)] / (2h)
Gamma	Γ = [V(S0 + h) − 2·V(S0) + V(S0 − h)] / h²
Vega	ν = [V(σ + h_σ) − V(σ − h_σ)] / (2·h_σ)
Bump sizes used in the code:

Greek	Bump	Value
Delta	h (spot)	1.00
Gamma	h (spot)	1.00
Vega	h_sigma (σ)	0.01
⚠️ Convention note: Vega is reported per unit volatility (per 1.00 change in σ). To express it per 1% vol move (the more common market convention), divide the printed value by 100.

Variance Reduction Techniques Used
Antithetic Variates
For every normal draw Z, the program also simulates the same path using −Z. Since −Z is also N(0,1), the antithetic path is valid, and its payoff is negatively correlated with the original path's payoff. Averaging the pair reduces the estimator variance.

Benefits:

Typically 30–60% variance reduction for Asian options (depends on parameters).

No extra random number generation cost — the same Z is reused with sign flipped.

Keeps the estimator unbiased.

Common Random Numbers (CRN)
All bumped revaluations (S0 ± h, σ ± h_σ) use the same seed 42. This aligns the random shocks across scenarios, so the finite-difference Greeks reflect only the parameter change, not random noise.

Function Reference
monte_carlo_asian_price(...)
cpp
double monte_carlo_asian_price(
    double S0,          // initial stock price
    double K,           // strike
    double r,           // risk-free rate
    double sigma,       // volatility
    double T,           // time to maturity
    int steps,          // time steps per path
    int simulations,    // total number of paths (must be even; loop runs simulations/2)
    unsigned int seed   // RNG seed (fixed -> common random numbers)
);
Returns the discounted Monte Carlo price of the arithmetic-average Asian call, using antithetic variates.

Parameters
Parameter	Value	Description
S0	100.00	Initial stock price
K	100.00	Strike price
r	0.05	Risk-free rate (annualized)
sigma	0.20	Volatility (annualized)
T	1.00	Time to maturity (years)
steps	252	Time steps per path (trading days)
simulations	10000	Total number of paths (5000 antithetic pairs)
fixed_seed	42	RNG seed shared across bumped revaluations (CRN)
h	1.00	Spot bump for Delta & Gamma
h_sigma	0.01	Vol bump for Vega
Note: simulations must be even, since the loop runs simulations / 2 iterations and generates two paths per iteration.
