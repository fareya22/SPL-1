#include <stdio.h>

int factorial(int n) {//count factorial
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int sumOfSquares(int n) {   /*count factorization*/
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result += i * i;
    }
    return result;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    int fact = factorial(n);
    int sum = sumOfSquares(n);

    printf("The factorial of %d is %d\n", n, fact);
    printf("The sum of squares of first %d numbers is %d\n", n, sum);

    int i = 1;
    while (i <= n) {
        int square = i * i;
        if (square > n) {
            break;
        }
        printf("%d\n", square);
        i++;
    }

    return 0;
}

