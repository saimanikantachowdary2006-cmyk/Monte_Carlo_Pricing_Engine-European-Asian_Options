#include <iostream>
#include <cmath>
#include <random>

double norm_cdf(double x) {
    
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

int main(){
    
    double S0 = 100.00;
    double K = 100.00;
    double r = 0.05;
    double sigma = 0.20;
    double T = 1.00;
    int steps = 252;
    int simulations = 10000;
    double dt = T / steps;
    

    double total_payoff = 0.0; 
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> shock(0.0, 1.0);
    
    
    for(int i = 0; i < simulations; i++){
        double S = S0;             
        double sum_price = 0.0;    
        
        
        for(int j = 0; j < steps; j++){
            double Z = shock(gen);
            S = S + (r * S * dt) + (sigma * S * std::sqrt(dt) * Z);
            sum_price += S;
        }
        
   
        double average_price = sum_price / steps;
        
     
        double payoff = std::max(average_price - K, 0.0);
        
        
        total_payoff += payoff;
    }
    
    
    double average_payoff = total_payoff / simulations;
    double asian_option_price = average_payoff * std::exp(-r * T);
    
    double d1 = (std::log(S0 / K) + (r + (sigma * sigma) / 2.0) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma*std::sqrt(T);
    double bs_price = (S0*norm_cdf(d1)) - (K*std::exp(-r*T)*norm_cdf(d2));
    
    
    std::cout << "Asian Option Price (MC): " << asian_option_price << std::endl;
    std::cout << "European Option Price (BS): " << bs_price << std::endl;

    return 0;
}
