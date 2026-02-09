#include <stdio.h>

int main() {
    char operator;
    double num1, num2, result;

    // Display menu
    printf("Basic Arithmetic Calculator\n");
    printf("===========================\n");
    printf("Available operations:\n");
    printf("+ : Addition\n");
    printf("- : Subtraction\n");
    printf("* : Multiplication\n");
    printf("/ : Division\n");
    printf("===========================\n\n");

    // Get input from user
    printf("Enter first number: ");
    scanf("%lf", &num1);
    
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);  // Space before %c to consume any leftover newline
    
    printf("Enter second number: ");
    scanf("%lf", &num2);

    // Perform calculation based on operator
    switch(operator) {
        case '+':
            result = num1 + num2;
            printf("\nResult: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;

        case '-':
            result = num1 - num2;
            printf("\nResult: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;

        case '*':
            result = num1 * num2;
            printf("\nResult: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;

        case '/':
            // Check for division by zero
            if(num2 != 0) {
                result = num1 / num2;
                printf("\nResult: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
            } else {
                printf("\nError: Division by zero is not allowed!\n");
                return 1;  // Return error code
            }
            break;

        default:
            printf("\nError: Invalid operator '%c'!\n", operator);
            printf("Please use one of: +, -, *, /\n");
            return 1;  // Return error code
    }

    return 0;
}