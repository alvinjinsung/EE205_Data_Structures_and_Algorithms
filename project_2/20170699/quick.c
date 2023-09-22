#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUM_INPUT 10000000

// global variable to keep track of number of comparisons
long long int count_comparison;

// function to choose the pivot from a given array
// pivot_choice can have four values: 1,2,3,4
// 1: first element, 2: last element, 3: random element, 4: median-of-three
// returns the index of the pivot element
int ChoosePivot(int *array, int start_position, int end_position, int pivot_choice) {

    int pivot_position;
    int middle_position = (start_position + end_position)/2;

    if (pivot_choice == 1) {
        pivot_position = start_position;
    }

    if (pivot_choice == 2) {
        pivot_position = end_position;
    }

    if (pivot_choice == 3) {
        srand((unsigned int)time(NULL));
        int num = rand();
        pivot_position = start_position + num%(end_position-start_position+1);
    }

    // increment count_comparison every time comparison is made
    if (pivot_choice == 4) {
        // if the array only have two elements, choose first element as pivot
        if (middle_position == start_position) {
                pivot_position = start_position;
        }

        // if the array have more than two elements
        else{
            if (array[start_position] > array[middle_position]) {
                count_comparison++;
                if (array[end_position] > array[middle_position]) {
                    count_comparison++;
                    if (array[start_position] > array[end_position]) {
                        count_comparison++;
                        // first element > last element > middle element
                        pivot_position = end_position;
                    }
                    else {
                        count_comparison++;
                        // last element > first element > middle element
                        pivot_position = start_position;
                    }
                }
                else {
                    count_comparison++;
                    // first element > middle element > last element
                    pivot_position = middle_position;
                }
            }

            else {
                count_comparison++;
                if (array[end_position] > array[start_position]) {
                    count_comparison++;
                    if (array[middle_position] > array[end_position]) {
                        count_comparison++;
                        // middle element > last element > first element
                        pivot_position = end_position;
                    }
                    else {
                        count_comparison++;
                        // last element > middle element > first element
                        pivot_position = middle_position;
                    }
                }
                else {
                    count_comparison++;
                    // middle element > first element > last element
                    pivot_position = start_position;
                }
            }
        }

    }

    return pivot_position;
}

// function to swap two element
void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;

    return;
}

// function to partition given array based on the pivot
// returns final position of the pivot element
int Partition(int *array, int start_position, int end_position) {
    int pivot_value = array[start_position];

    int i = start_position + 1;
    int j;

    for (j=start_position+1; j<end_position+1; j++) {
        if (array[j] < pivot_value) {
            swap(&array[j], &array[i]);
            i++;
        }
    }

    swap(&array[start_position], &array[i-1]);

    return i-1;
}

// function to sort the given array
void QuickSort(int *array, int start_position, int end_position, int pivot_choice) {

    // if the array length is less or equal to 1, return(base case)
    if (start_position >= end_position) {
        return;
    }

    else {
        // find the index of the pivot element based on the pivot choice
        int pivot_position = ChoosePivot(array, start_position, end_position, pivot_choice);

        // swap the first element with the pivot element
        swap(&array[start_position], &array[pivot_position]);

        // partition the given array based on the pivot
        int pivot_result = Partition(array, start_position, end_position);
        // every time partition is made for length m array, increment count_comparison by m-1
        count_comparison += end_position - start_position;

        // recursively call QuickSort on two partitioned array
        QuickSort(array, start_position, pivot_result-1, pivot_choice);
        QuickSort(array, pivot_result+1, end_position, pivot_choice);

        return;
    }
}


int main(void) {
    // input integer can be represented as signed 32-bit integer
    // -2^31 to 2^31 which is 11 characters most
    char input_value[11];
    int *input_array = malloc(sizeof(int)*MAX_NUM_INPUT);
    int i = 0;

    // reading inputs until EOF and putting it in the input_array at appropriate index using atoi function
    while(fgets(input_value, sizeof(input_value), stdin))
    {
        input_array[i]=atoi(input_value);
        i++;
    }

    // total number of input integers
    int num_input = i;

    // copy of the input array to use for different pivot choices
    int *input_array_cpy = malloc(num_input*sizeof(int));

    // compute number of comparisons for using first element as pivot
    count_comparison = 0;
    memcpy(input_array_cpy, input_array, num_input*sizeof(int));
    QuickSort(input_array_cpy, 0, num_input-1, 1);
    printf("First: %lld\n", count_comparison);

    // compute number of comparisons for using last element as pivot
    count_comparison = 0;
    memcpy(input_array_cpy, input_array, num_input*sizeof(int));
    QuickSort(input_array_cpy, 0, num_input-1, 2);
    printf("Last: %lld\n", count_comparison);

    // compute number of comparisons for using random element as pivot
    // run 10 times and compute the mean
    count_comparison = 0;
    for(int i=0; i<10; i++) {
        memcpy(input_array_cpy, input_array, num_input*sizeof(int));
        QuickSort(input_array_cpy, 0, num_input-1, 3);
    }
    printf("Random: %lld\n", count_comparison/10);

    // compute number of comparisons for using median-of-three element as pivot
    count_comparison = 0;
    memcpy(input_array_cpy, input_array, num_input*sizeof(int));
    QuickSort(input_array_cpy, 0, num_input-1, 4);
    printf("Median-of-three: %lld\n", count_comparison);

    free(input_array_cpy);
    free(input_array);

    return 0;

}

