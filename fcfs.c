#include <stdio.h>

int main(){
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n];
    int ct[n], tat[n], wt[n];

    for(i = 0; i<n; i++){
        pid[i] = i + 1;

        printf("Process [%d]\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    int current_time = 0;

    for(i = 0; i < n; i++) {

        if(current_time < at[i]) {
            current_time = at[i];
        }

        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        current_time = ct[i];
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    double sum_wt = 0, sum_tat = 0;

    for(i = 0; i < n; i++){
        sum_tat += tat[i];
        sum_wt += wt[i];
    }

    double avg_tat = sum_tat / n;
    double avg_wt = sum_wt / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}
