#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// structure to store Fi/Ki values and index of the given job
struct FidivKi_index {
    int index;
    float input_array_FidivKi;
};

// compare function for struct FidivKi_index based on Fi/Ki values(decreasing  order)
int Compare_FidivKi(const void *a, const void *b) {
    const struct FidivKi_index *pa = (const struct FidivKi_index *)a;
    const struct FidivKi_index *pb = (const struct FidivKi_index *)b;

    if ((pa->input_array_FidivKi) > (pb->input_array_FidivKi)) {
        return -1;
    }

    else if ((pa->input_array_FidivKi) < (pb->input_array_FidivKi)) {
        return 1;
    }

    else {
        if ((pa->index) > (pb->index)) {
            return 1;
        }

        else if ((pa->index) < (pb->index)) {
            return -1;
        }

        else {
            return 0;
        }
    }
}

int main(void) {
    // variable to store the information of first line of the input
    char first_value[4];
    int num_jobs;

    // fgets the value of the first line of the input stream: total number of jobs
    fgets(first_value, sizeof(first_value), stdin);
    num_jobs=atoi(first_value);

    // array to store the information of Ki and Fi value of each job
    int *input_array_Ki = malloc(sizeof(int)*num_jobs);
    int *input_array_Fi = malloc(sizeof(int)*num_jobs);

    char input_value[10];
    char *input_value_Ki;
    char *input_value_Fi;

    int i = 0;

    // store Ki value in order in the input_array_Ki, and store Fi value in order in the input_array_Fi
    while(fgets(input_value, sizeof(input_value), stdin))
    {
        input_value_Ki = strtok_r(input_value, " ", &input_value_Fi);

        input_array_Ki[i] = atoi(input_value_Ki);
        input_array_Fi[i] = atoi(input_value_Fi);

        i++;
    }

    // variable to store the sum of all fine
    int fine = 0;
    int j;

    // Calculate the sum of all fine
    for (j=0; j<num_jobs; j++) {
        fine += input_array_Fi[j];
    }

    // create structure FidivKi_index for given input
    struct FidivKi_index FidivKi_index[num_jobs];

    for (j=0; j<num_jobs; j++) {
        FidivKi_index[j].index = j+1;
        FidivKi_index[j].input_array_FidivKi = ((float)input_array_Fi[j])/((float)input_array_Ki[j]);
    }

    // sort FidivKi_index based on the Fi/ki value in decreasing order
    qsort(FidivKi_index, num_jobs, sizeof(struct FidivKi_index), Compare_FidivKi);

    // array to store the calculated order of jobs to be executed
    int job_order[num_jobs];
    int total_fine = 0;

    // calculate the fine needed to be purchased
    for (j=0; j<num_jobs; j++) {
        job_order[j] = FidivKi_index[j].index;
        total_fine += input_array_Ki[FidivKi_index[j].index - 1] * (fine - input_array_Fi[FidivKi_index[j].index -1]);

        fine -= input_array_Fi[FidivKi_index[j].index -1];
    }

    // print the result
    for (j=0; j<num_jobs; j++) {
        printf("%d ", job_order[j]);
    }

    printf("\nTotal fine: %d\n", total_fine);

    return 0;

}

