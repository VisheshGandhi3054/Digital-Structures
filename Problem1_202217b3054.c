#include <stdio.h>
#include <stdlib.h>

// Struct to store job information
typedef struct {
    int index; // Job index
    int time;  // Time to complete the job
    int fine;  // Fine per day of delay
} Job;

// Comparison function for sorting
int compareJobs(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;

    long long ratioA = (long long)jobA->fine * jobB->time;
    long long ratioB = (long long)jobB->fine * jobA->time;

    if (ratioA != ratioB) {
        return (ratioA > ratioB) - (ratioA < ratioB);
    }
    return jobA->index - jobB->index;
}

int main() {
    int N;
    scanf("%d", &N);

    Job jobs[N];

    // Reading input
    for (int i = 0; i < N; i++) {
        jobs[i].index = i + 1; // Store the 1-based index
        scanf("%d %d", &jobs[i].time, &jobs[i].fine);
    }

    // Sorting the jobs based on the ratios and indices
    qsort(jobs, N, sizeof(Job), compareJobs);

    // Printing the sorted job indices
    for (int i = 0; i < N; i++) {
        printf("%d\n", jobs[i].index);
    }

    return 0;
}
