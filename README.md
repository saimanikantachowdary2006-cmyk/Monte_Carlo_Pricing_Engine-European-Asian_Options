Asian & European Option Pricing (C++):
A C++ implementation that prices two option types in a single program:

An arithmetic-average Asian call option via Monte Carlo simulation.

A European call option via the Black–Scholes closed-form formula.

Both prices are printed side by side so you can compare the effect of averaging (Asian) versus terminal-price payoff (European).

Overview
This program contains both pricers:

Asian (Monte Carlo): Simulates N GBM paths, averages the stock price along each path, and discounts the average payoff max(average_price − K, 0).

European (Black–Scholes): Computes the analytical call price using the closed-form Black–Scholes formula.

Note: These two prices are not directly comparable — they price different payoff structures. Averaging reduces volatility, so the Asian price is typically lower than the European price for the same inputs. The European price is included as a sanity check / reference point, not as a validation target for the Asian Monte Carlo estimate.

Model
1. Asian option (Monte Carlo)
Stock price evolution (Euler discretization of GBM):
S_{t+dt} = S_t + r * S_t * dt + sigma * S_t * sqrt(dt) * Z

where Z ~ N(0, 1).

Arithmetic average and payoff:


A = (1 / steps) * sum_{t=1}^{steps} S_t
payoff = max(A − K, 0)
Asian price = exp(-r * T) * (1 / simulations) * sum(payoffs)
2. European option (Black–Scholes)

C = S0 * N(d1) − K * exp(-r*T) * N(d2)

d1 = [ ln(S0/K) + (r + sigma^2 / 2) * T ] / (sigma * sqrt(T))
d2 = d1 − sigma * sqrt(T)

N(x) = 0.5 * (1 + erf(x / sqrt(2)))
Parameters:
Parameter	  Value	      Description
S0	        100.00	  Initial stock price
K	          100.00	   Strike price
r	          0.05	    Risk-free interest rate (annualized)
sigma	      0.20	    Volatility (annualized)
T	          1.00	    Time to maturity (years)
steps	      252	      Time steps per path (trading days)
simulations	10000	    Number of Monte Carlo paths
All parameters are hard-coded in main() and can be modified directly. The same inputs are shared by both the Asian and European pricers.

Build & Run
Requirements
A C++11 (or later) compiler (g++, clang++, or MSVC)

