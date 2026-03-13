#include <stdio.h>

int main() {
    int n, time_quantum;
    char usn;
    printf("Enter your USN:");
    scanf("%s", &usn);
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    int process_id[n], arrival_time[n], burst_time[n];
    int remaining_time[n], completion_time[n];
    int waiting_time[n], turnaround_time[n];

    int current_time = 0, completed = 0;

    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &process_id[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &arrival_time[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &burst_time[i]);

        remaining_time[i] = burst_time[i];
    }

    while(completed < n) {
        int executed = 0;

        for(int i = 0; i < n; i++) {

            if(arrival_time[i] <= current_time && remaining_time[i] > 0) {

                executed = 1;

                if(remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
                else {
                    current_time += remaining_time[i];
                    completion_time[i] = current_time;

                    turnaround_time[i] = completion_time[i] - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];

                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }

        if(executed == 0) {
            current_time++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               process_id[i],
               arrival_time[i],
               burst_time[i],
               completion_time[i],
               waiting_time[i],
               turnaround_time[i]);
    }

    double sum_wt = 0, sum_tat = 0;

    for(int i = 0; i < n; i++) {
        sum_wt += waiting_time[i];
        sum_tat += turnaround_time[i];
    }

    printf("\nAverage Waiting Time: %.2f", sum_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", sum_tat / n);

    return 0;
}
