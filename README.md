Monte Carlo Option Pricing (C++)
A simple C++ implementation of Monte Carlo simulation for pricing a European call option, with a Black–Scholes analytical price included as a benchmark for validation.

Overview
This program:

Simulates N paths of a stock price using Geometric Brownian Motion (GBM) under the risk-neutral measure.

Computes the discounted average payoff of a European call option.

Calculates the Black–Scholes analytical price and prints it alongside the Monte Carlo estimate so you can compare the two.

Model
The stock price evolves according to:

S_{t+dt} = S_t + r * S_t * dt + sigma * S_t * sqrt(dt) * Z

where Z ~ N(0, 1).

The Monte Carlo option price is:

Price = exp(-r * T) * (1/N) * sum( max(S_T - K, 0) )

The Black–Scholes call price is:
C = S0 * N(d1) - K * exp(-r*T) * N(d2)

d1 = [ ln(S0/K) + (r + sigma^2 / 2) * T ] / (sigma * sqrt(T))
d2 = d1 - sigma * sqrt(T)

Parameters
Parameter  	Value   	Description
S0	        100.00	Initial stock price
K          	100.00	Strike price
r          	0.05	Risk-free interest rate (annualized)
sigma      	0.20	Volatility (annualized)
T	          1.00	Time to maturity (years)
steps      	252	Time steps per path
simulation	10000	Number of Monte Carlo paths
All parameters are hard-coded in main() and can be modified directly.

Build & Run
Requirements
A C++11 (or later) compiler (g++, clang++, or MSVC)


Example Output

The option price is : 10.4721
The black scholes price : The call price is : 10.4506
Notes on Implementation
Euler discretization is used for the GBM path (simple and adequate for small dt).

An exact lognormal scheme (S *= exp((r - 0.5σ²)dt + σ√dt·Z)) would be more accurate and avoids negative-price artifacts for large σ or large dt.

The seed uses std::random_device, so results will differ slightly between runs. For reproducible output, replace with a fixed seed:

