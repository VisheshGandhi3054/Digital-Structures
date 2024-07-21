#include <stdio.h>
#include <stdlib.h>

// Struct to store candidate information
typedef struct {
    int candidate;
    int count;
} CandidateCount;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to merge and count candidates proposed by at least 3 zones
int countElectedCandidates(int *zone1, int n1, int *zone2, int n2, int *zone3, int n3, int *zone4, int n4, int *zone5, int n5) {
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;
    int electedCount = 0;
    int candidateCount = 0;
    CandidateCount candidateArray[250000]; // A large array to hold candidate counts (max 250,000 entries)

    while (i1 < n1 || i2 < n2 || i3 < n3 || i4 < n4 || i5 < n5) {
        int minVal = 50001; // Larger than any possible candidate ID

        if (i1 < n1 && zone1[i1] < minVal) minVal = zone1[i1];
        if (i2 < n2 && zone2[i2] < minVal) minVal = zone2[i2];
        if (i3 < n3 && zone3[i3] < minVal) minVal = zone3[i3];
        if (i4 < n4 && zone4[i4] < minVal) minVal = zone4[i4];
        if (i5 < n5 && zone5[i5] < minVal) minVal = zone5[i5];

        int count = 0;
        if (i1 < n1 && zone1[i1] == minVal) { count++; i1++; }
        if (i2 < n2 && zone2[i2] == minVal) { count++; i2++; }
        if (i3 < n3 && zone3[i3] == minVal) { count++; i3++; }
        if (i4 < n4 && zone4[i4] == minVal) { count++; i4++; }
        if (i5 < n5 && zone5[i5] == minVal) { count++; i5++; }

        if (count >= 3) electedCount++;
    }

    return electedCount;
}

int main() {
    int N1, N2, N3, N4, N5;
    scanf("%d %d %d %d %d", &N1, &N2, &N3, &N4, &N5);

    int zone1[N1], zone2[N2], zone3[N3], zone4[N4], zone5[N5];

    for (int i = 0; i < N1; i++) scanf("%d", &zone1[i]);
    for (int i = 0; i < N2; i++) scanf("%d", &zone2[i]);
    for (int i = 0; i < N3; i++) scanf("%d", &zone3[i]);
    for (int i = 0; i < N4; i++) scanf("%d", &zone4[i]);
    for (int i = 0; i < N5; i++) scanf("%d", &zone5[i]);

    // Sort each zone's candidate list
    qsort(zone1, N1, sizeof(int), compare);
    qsort(zone2, N2, sizeof(int), compare);
    qsort(zone3, N3, sizeof(int), compare);
    qsort(zone4, N4, sizeof(int), compare);
    qsort(zone5, N5, sizeof(int), compare);

    // Count elected candidates
    int result = countElectedCandidates(zone1, N1, zone2, N2, zone3, N3, zone4, N4, zone5, N5);

    // Print the result
    printf("%d\n", result);

    return 0;
}
