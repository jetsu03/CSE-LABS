#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define TERMS 10
double toRadians(double degree) {
    return degree * PI / 180.0;
}
double factorial(int n) {
    double fact = 1;
    for (int i = 2; i <= n; i++)
        fact *= i;
    return fact;
}
double sinTaylor(double x) { // Taylor series for sin(x)
    double result = 0;
    for (int i = 0; i < TERMS; i++) {
        double term = pow(-1, i) * pow(x, 2*i + 1) / factorial(2*i + 1);
        result += term;
    }
    return result;
}
double cosTaylor(double x) { // Taylor series for cos(x)
    double result = 0;
    for (int i = 0; i < TERMS; i++) {
        double term = pow(-1, i) * pow(x, 2*i) / factorial(2*i);
        result += term;
    }
    return result;
}
int main() {
    double degree;
    printf("Enter angle in degrees: ");
    scanf("%lf", &degree);
    double x = toRadians(degree);
    double sinx = sinTaylor(x);
    double cosx = cosTaylor(x);
    if (fabs(cosx) < 1e-6) { //Edge case if absolute value of cosx is close to 1x10^-6
        printf("Cosine is too close to zero, result may be undefined or infinite.\n");
    } else {
        double approx = sinx / cosx;
        double builtin = tan(x);
        printf("\nUsing Taylor Series approximation:\n");
        printf("sin(x)/cos(x) ≈ %.10f\n", approx);
        printf("\nUsing built-in tan(x):\n");
        printf("tan(x) = %.10f\n", builtin);
        printf("\nInference:\n");
        printf("Difference = %.10f\n", fabs(approx - builtin));
        if (fabs(approx - builtin) < 0.001) //fabs() is absolute value
            printf("The approximation is accurate.\n");
        else
            printf("The approximation deviates slightly. Increase TERMS for better accuracy.\n");
    }
    return 0;
}
