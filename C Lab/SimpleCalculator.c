#include<stdio.h>
int main() {
    char operator;
    double num1, num2, result;
    printf("Simple Calculator Simulation\n");
    printf("----------------------------\n");
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator); //% Indicates format specifier
    printf("Enter first number: ");
    scanf("%lf", &num1); //lf is long float or double 
    printf("Enter second number: ");
    scanf("%lf", &num2);
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result: %.2lf + %.2lf = %.2lf\n", num1, num2, result); //print 2 numbers after decimal 
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else {
                printf("Error: Division by zero is not allowed.\n");
                return 1;
            }
            printf("Result: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
            break;
        default:
            printf("Invalid operator.\n");
    }
    return 0;
}
