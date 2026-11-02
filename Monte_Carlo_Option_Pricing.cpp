#include <iostream>
#include <vector>
#include <cmath>
#include <random>
double norm_cdf(double x) {
    
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}
int main(){
    double S0 = 100.00;
    double K = 100.00;
    double r =0.05;
    double sigma = 0.20;
    double T = 1.00;
    int steps = 252;
    int simulation = 10000;
    double dt = T/steps;
    double total_payoff =0.0;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> shock(0.0,1.0);
    
    for(int i=0;i<simulation;i++){
        double S = S0;
        for(int t=0;t<steps;t++){
            double Z = shock(gen);
            S = S+(r*S*dt)+(sigma*S*std::sqrt(dt)*Z);
        }
        double payout = std::max(S-K,0.0);
        total_payoff+=payout;
    }
    double average_payout = total_payoff/simulation;
    double option_price = average_payout*exp(-r*T);
    std::cout<<"The option price is : "<<option_price<<std::endl;
    
    std::cout<<"The black scholes price :";
    double d1 = (std::log(S0/K) + (r + 0.5*sigma*sigma)*T) / (sigma*std::sqrt(T));
    double d2 = d1 - sigma*std::sqrt(T);
    double callprice = (S0*norm_cdf(d1)) - (K*std::exp(-r*T)*norm_cdf(d2));
    std::cout<<"The call price is : "<<callprice<<std::endl;
    
}
