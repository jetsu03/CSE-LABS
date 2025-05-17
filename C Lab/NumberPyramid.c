#include <stdio.h>
int main() {
    int n, i, j;
    printf("Enter the number of rows: ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++) { //Points at each row
        for (j = 1; j <= n - i; j++) { //n-i to decrease distance with start 
            printf("  "); // two spaces for better alignment
        }
        for (j = 1; j <= i; j++) { //Print all numbers asc after space
            printf("%d ", j);
        }
        for (j = i - 1; j >= 1; j--) { //Print all numbers desc after asc
            printf("%d ", j);
        }
        printf("\n"); //After 1 full row printed, goes to next line
    }
    return 0;
}
