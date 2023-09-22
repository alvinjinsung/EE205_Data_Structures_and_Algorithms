#include <stdio.h>
#include <stdlib.h>

// int compare function(from test.c given)
static int
IntIncreasingOrder(const void *A, const void *B)
{
    const int a = *(int *)A, b = *(int *)B;
    return (a > b) ? 1 : ((a < b) ? -1 : 0);
}

int main(void)
{
    int i, n;
    int *customers;
    long int sum = 0;

    if (scanf("%d ", &n) != 1) {
        fprintf(stderr, "wrong input\n");
        return -1;
    }

    customers = malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        if (scanf("%d", &customers[i]) != 1) {
            fprintf(stderr, "wrong input at %dth customer\n", i+1);
            return -1;
        }
    }
    if (i != n) {
        fprintf(stderr, "input is too short\n");
        free(customers);
        return -1;
    }

    // sort given customers array(using built-in function provided by stdlib)
    qsort(customers, n, sizeof(int), IntIncreasingOrder);

    // variable that indicates the index of median
    int median;

    if (n % 2 == 1) {
        median = (n-1)/2;
    }

    else {
        median = n/2;
    }

    // find and sum all the absolute value of difference between median element and each element given)
    int k;

    for (k=0; k<n; k++) {
        sum = sum + abs(customers[median] - customers[k]);
    }

    // print out the final output 
    printf("%ld\n", sum);
    return 0;
}