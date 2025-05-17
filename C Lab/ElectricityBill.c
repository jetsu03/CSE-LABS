#include <stdio.h>
#include <string.h>
int main() {
    char name[50];
    int units;
    float amount = 0, surcharge = 0, total = 0;

    printf("Enter user name: ");
    scanf("%s", name);
    printf("Enter units consumed: ");
    scanf("%d", &units);
    if (units <= 200) {
        amount = units * 0.80;
    } else if (units <= 300) {
        amount = 200 * 0.80 + (units - 200) * 0.90;
    } else {
        amount = 200 * 0.80 + 100 * 0.90 + (units - 300) * 1.00;
    }
    total = amount + 100;
    if (total > 400) {
        surcharge = total * 0.15;
        total += surcharge;
    }
    printf("\nElectricity Bill\n");
    printf("----------------------\n");
    printf("Name           : %s\n", name);
    printf("Units Consumed : %d\n", units);
    printf("Base Amount    : ₹%.2f\n", amount);
    printf("Meter Charge   : ₹100.00\n");
    if (surcharge > 0) {
        printf("Surcharge (15%%): ₹%.2f\n", surcharge);
    }
    printf("Total Amount   : ₹%.2f\n", total);
    return 0;
}
