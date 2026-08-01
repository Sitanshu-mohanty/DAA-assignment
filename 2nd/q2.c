#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double simulate_coin(int num_tosses, double bias) {
    int heads_count = 0;

    for (int i = 0; i < num_tosses; i++) {
        double random_val = (double)rand() / RAND_MAX;
        
        if (random_val < bias) {
            heads_count++;
        }
    }
    
    return (double)heads_count / num_tosses;
}

int main() {
    srand(time(NULL));

    int num_tosses = 1000000; 

    printf("Starting Coin Toss Simulation with %d trials...\n", num_tosses);

    double fair_bias = 0.50;
    double fair_result = simulate_coin(num_tosses, fair_bias);
    
    printf("Experiment 1: Fair Coin\n");
    printf("  Expected Probability : %.4f\n", fair_bias);
    printf("  Simulated Probability: %.4f\n\n", fair_result);

    double biased_bias_1 = 0.75; 
    double biased_result_1 = simulate_coin(num_tosses, biased_bias_1);
    
    printf("Experiment 2: Biased Coin (Heavy towards Heads)\n");
    printf("  Expected Probability : %.4f\n", biased_bias_1);
    printf("  Simulated Probability: %.4f\n\n", biased_result_1);

    double biased_bias_2 = 0.10; 
    double biased_result_2 = simulate_coin(num_tosses, biased_bias_2);
    
    printf("Experiment 3: Biased Coin (Heavy towards Tails)\n");
    printf("  Expected Probability : %.4f\n", biased_bias_2);
    printf("  Simulated Probability: %.4f\n\n", biased_result_2);

    return 0;
}