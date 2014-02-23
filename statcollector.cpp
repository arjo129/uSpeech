#include "uspeech.h"

statCollector::statCollector(){
    n=0;mean=0;M2=0;M3=0;M4=0;
}
int statCollector::_mean(){
    return mean;
}
int statCollector::stdev(){
    return M2;
}
int statCollector::kurtosis(){
    int kurtosis = (n*M4) / (M2*M2) - 3;
    return kurtosis;
}
int statCollector::skew(){
    int kurtosis = (n*M3) / (M2*M2*M2) - 3;
    return kurtosis;
}
void statCollector::collect(int x) {
    int n1 = n;
    n = n + 1;
    int delta = x - mean;
    int delta_n = delta / n;
    int delta_n2 = delta_n * delta_n;
    int term1 = delta * delta_n * n1;
    mean = mean + delta_n;
    M4 = M4 + term1 * delta_n2 * (n*n - 3*n + 3) + 6 * delta_n2 * M2 - 4 * delta_n * M3;
    M3 = M3 + term1 * delta_n * (n - 2) - 3 * delta_n * M2;
    M2 = M2 + term1;
}