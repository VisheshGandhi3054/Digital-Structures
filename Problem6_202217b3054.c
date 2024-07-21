#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000

int main() {
    int N;
    scanf("%d", &N);
    int a[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    int best[MAXN];
    for (int i = 0; i < N; i++) {
        best[i] = 1;
    }

    int max_length = 1;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] % a[i] == 0 && best[j] + 1 > best[i]) {
                best[i] = best[j] + 1;
            }
        }
        if (best[i] > max_length) {
            max_length = best[i];
        }
    }

    printf("%d\n", max_length);
    return 0;
}
