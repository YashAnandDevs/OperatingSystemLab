#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, time = 0, completed = 0, shortest;
    int at[20], bt[20], rt[20], ct[20], tat[20], wt[20];
    int min_bt;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; // remaining time
    }

    while(completed != n) {
        shortest = -1;
        min_bt = INT_MAX;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min_bt) {
                min_bt = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;

        if(rt[shortest] == 0) {
            completed++;
            ct[shortest] = time + 1;

            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            avg_wt += wt[shortest];
            avg_tat += tat[shortest];
        }

        time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
