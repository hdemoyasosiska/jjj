#include <iostream>
#include <functional>
#include <cmath>
#include <vector>


double trapezoidalIntegral(double a, double b, int n_steps, const std::function<double (double)> &f) {
    const double width = (b-a) / n_steps;

    double trapezoidal_integral = 0;
    for(int step = 0; step < n_steps; step++) {
        const double x1 = a + step*width;
        const double x2 = a + (step+1)*width;

        trapezoidal_integral += 0.5*(x2-x1)*(f(x1) + f(x2));
    }

    return trapezoidal_integral;
}


double f_x(const std::function<double (double)> &f, double x){
    return f(x);
}

double integrateDP(std::function<double(double)> f, double a, double b, int numSteps, int accuracy) {
    std::vector<double> dp(numSteps + 1, 0.0);
    double trapezoidal_integral = 0;
    double stepSize = (b - a) / numSteps;
    dp[0] = f(0);
    for (int i = 1; i <= numSteps; ++i) {
        double x = a + i * stepSize;
        dp[i] = f(x);
        trapezoidal_integral += (dp[i-1] + dp[i]) / 2.0 * stepSize;
    }
    int okr = pow(10, accuracy);
    return std::round(trapezoidal_integral * okr) / okr;
}

int main() {
    std::function<double (double)> f = [](double x) { return std::sin(x) + std::pow(std::cos(x), 2); };
    double x = 0.87;
    std::cout << "f(" << x << ") = " << f_x(f, x) << std::endl;
    double a = 0;
    double b = 3.14159265359;
    int n = 1000;
    std::cout << trapezoidalIntegral(a, b, n, f) << std::endl;
    int accuracy = 4;
    std::cout << integrateDP(f, a, b, n, accuracy);
    return 0;
}
