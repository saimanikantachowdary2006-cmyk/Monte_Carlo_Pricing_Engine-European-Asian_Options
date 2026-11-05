#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

double monte_carlo_asian_price(double S0,double K, double r,double sigma,double T,int steps,
int simulations,unsigned int seed){
    double dt = T/steps;
    double total_payoff = 0.0;
    std::mt19937 gen(seed);
    std::normal_distribution<double> shock(0.0,1.0);
    
    for(int i = 0;i<simulations/2;i++){
        double S1 = S0;
        double S2 = S0;
        double sum_price1 = 0.0;
        double sum_price2 = 0.0;
        for(int j = 0;j<steps;j++){
            double Z = shock(gen);
            S1 = S1+(r*S1*dt)+(sigma*S1*std::sqrt(dt)*Z);
            sum_price1+=S1;
            S2 = S2+(r*S2*dt)+(sigma*S2*std::sqrt(dt)*(-Z));
            sum_price2+=S2;
            
        }
        //double average_price = sum_price/steps;
        double payoff1 = std::max((sum_price1/steps)-K,0.0);
        double payoff2 = std::max((sum_price2/steps)-K,0.0);
        
        total_payoff+=(payoff1+payoff2);
    }
    double average_payoff = total_payoff/simulations;
    double option_price = average_payoff*std::exp(-r*T);
    return option_price;
}

int main(){
    unsigned int fixed_seed = 42;
    double base_price = monte_carlo_asian_price(100, 100, 0.05, 0.20, 1.0, 252, 10000, fixed_seed);
    
    double h = 1.00;
    double price_up = monte_carlo_asian_price(100+h, 100, 0.05, 0.20, 1.0, 252, 10000, fixed_seed);
    double price_down =  monte_carlo_asian_price(100-h, 100, 0.05, 0.20, 1.0, 252, 10000, fixed_seed);
    
    double delta = (price_up-price_down)/(2*h);
    double gamma = (price_up-(2*base_price)+price_down)/(h*h);
    
    double h_sigma = 0.01;
    
    double price_vol_up = monte_carlo_asian_price(100, 100, 0.05, 0.20+h_sigma, 1.0, 252, 10000, fixed_seed);
    double price_vol_down = monte_carlo_asian_price(100, 100, 0.05, 0.20-h_sigma, 1.0, 252, 10000, fixed_seed);
    
    double vega = (price_vol_up - price_vol_down)/(2*h_sigma);
    
    
    std::cout<<"Base price is : "<<base_price<<std::endl;
    std::cout<<"The delta : "<<delta<<std::endl;
    std::cout<<"The gamma : "<<gamma<<std::endl;
    std::cout<<"The vega is : "<<vega<<std::endl;
    return 0;
}
