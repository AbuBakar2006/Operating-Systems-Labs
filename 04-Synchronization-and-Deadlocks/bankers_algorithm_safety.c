// Banker's Algorithm Code

#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main(void)
{
	int n, m;
	int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
	int finish[MAX] = {0}, safeSeq[MAX], work[MAX];

	printf("Enter number of processes: ");
	scanf("%d", &n);
	printf("Enter number of resources: ");
	scanf("%d", &m);
	max[MAX][MAX], need[MAX][MAX];

	printf("Enter allocation matrix:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &alloc[i][j]);
		}
	}

	printf("Enter maximum matrix:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &max[i][j]);
		}
	}

	printf("Enter available resources:\n");
	for (int j = 0; j < m; j++) {
		scanf("%d", &avail[j]);
		work[j] = avail[j];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	int count = 0;
	while (count < n) {
		bool found = false;

		for (int i = 0; i < n; i++) {
			if (finish[i]) continue;

			int canRun = 1;
			for (int j = 0; j < m; j++) {
				if (need[i][j] > work[j]) {
					canRun = 0;
					break;
				}
			}

			if (canRun) {
				for (int j = 0; j < m; j++) {
					work[j] += alloc[i][j];
				}
				safeSeq[count++] = i;
				finish[i] = 1;
				found = true;
			}
		}

		if (!found) break;
	}

	if (count == n) {
		printf("System is SAFE. Safe sequence: ");
		for (int i = 0; i < n; i++) {
			printf("P%d", safeSeq[i]);
			if (i < n - 1) printf(" -> ");
		}
		printf("\n");
	} else {
		printf("System is in DEADLOCK/UNSAFE state.\n");
	}
	return 0;
}