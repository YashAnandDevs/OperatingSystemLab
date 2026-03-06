#include <stdio.h>

int main() {
    int n, i, j;
    int at[20], bt[20], ct[20], tat[20], wt[20], pid[20];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival times:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &at[i]);
        pid[i] = i + 1;
    }

    printf("\nEnter burst times:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    /* Sorting by Burst Time (SJF) */
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(bt[i] > bt[j]) {
                int temp;

                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
            }
        }
    }

    /* Calculate CT */
    ct[0] = at[0] + bt[0];
    for(i = 1; i < n; i++) {
        ct[i] = ct[i-1] + bt[i];
    }

    /* Calculate TAT and WT */
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_tat += tat[i];
        avg_wt += wt[i];
    }

    printf("\nSJF scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage turnaround time: %fms", avg_tat/n);
    printf("\nAverage waiting time: %fms\n", avg_wt/n);

    return 0;
}
