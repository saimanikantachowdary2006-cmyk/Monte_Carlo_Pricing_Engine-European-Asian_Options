Asian Option Pricing & Greeks via Monte Carlo (C++):
A C++ program that prices an arithmetic-average Asian call option using Monte Carlo simulation and estimates its Greeks (Delta, Gamma, Vega) via finite differences with common random numbers (fixed seed) for variance reduction.

Overview
This program:

Simulates GBM stock paths and prices an arithmetic-average Asian call option with Monte Carlo.

Estimates the option's Delta, Gamma, and Vega using central finite differences.

Uses a fixed RNG seed across bumped revaluations, so the same random paths are reused — a technique known as common random numbers (CRN) that substantially reduces noise in the finite-difference estimates.

Model
1. Asian option price (Monte Carlo)
Stock price evolution (Euler discretization of GBM):


S_{t+dt} = S_t + r * S_t * dt + sigma * S_t * sqrt(dt) * Z,   Z ~ N(0,1)
Arithmetic average and payoff:


A = (1 / steps) * sum_{t=1}^{steps} S_t
payoff = max(A − K, 0)
Asian price = exp(-r * T) * (1 / simulations) * sum(payoffs)
2. Greeks via central finite differences
Delta (sensitivity to spot):


Δ = [V(S0 + h) − V(S0 − h)] / (2h)
Gamma (second-order sensitivity to spot):


Γ = [V(S0 + h) − 2·V(S0) + V(S0 − h)] / h²
Vega (sensitivity to volatility):


ν = [V(σ + h_σ) − V(σ − h_σ)] / (2·h_σ)
Bump sizes used in the code:

Greek	Bump	Value
Delta	h (spot)	1.00
Gamma	h (spot)	1.00
Vega	h_sigma (σ)	0.01
Convention note: Vega is reported per unit volatility (i.e., per 1.00 change in σ). To express it per 1% vol move (the more common market convention), divide the printed value by 100.

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
    int simulations,    // number of Monte Carlo paths
    unsigned int seed   // RNG seed (fixed -> common random numbers)
);
Returns the discounted Monte Carlo price of the arithmetic-average Asian call.

Why the seed is a parameter: passing the same seed to every bumped revaluation ensures the same sequence of normal shocks is used across scenarios. This makes finite-difference Greeks far more stable than using fresh randomness each time.

Parameters
Parameter	Value	Description
S0      	100.00	Initial stock price
K	        100.00	Strike price
r	          0.05	Risk-free rate (annualized)
sigma	      0.20	Volatility (annualized)
T	          1.00	Time to maturity (years)
steps	       252	Time steps per path (trading days)
simulations	10000	Number of Monte Carlo paths
fixed_seed	  42	RNG seed shared across bumped revaluations
h          	1.00	Spot bump for Delta & Gamma
h_sigma    	0.01	Vol bump for Vega

Requirements
A C++11 (or later) compiler (g++, clang++, or MSVC)

Compile
bash
g++ -O2 -std=c++11 Monte_Carlo_Asian_Greeks.cpp -o mc_asian_greeks
Run
bash
./mc_asian_greeks
