#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process_id[n], arrival_time[n], burst_time[n], priority[n];
    int remaining_time[n], completion_time[n];
    int turnaround_time[n], waiting_time[n];

    int current_time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Enter Process ID: ");
        scanf("%d", &process_id[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &arrival_time[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &burst_time[i]);

        printf("Enter Priority (lower number = higher priority): ");
        scanf("%d", &priority[i]);

        remaining_time[i] = burst_time[i];
    }

    while (completed < n) {
        int highest_priority = 9999;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1) {
            current_time++;
        }
        else {
            remaining_time[selected_process]--;
            current_time++;

            if (remaining_time[selected_process] == 0) {
                completion_time[selected_process] = current_time;

                turnaround_time[selected_process] =
                    completion_time[selected_process] -
                    arrival_time[selected_process];

                waiting_time[selected_process] =
                    turnaround_time[selected_process] -
                    burst_time[selected_process];

                completed++;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               process_id[i],
               arrival_time[i],
               burst_time[i],
               priority[i],
               waiting_time[i],
               turnaround_time[i]);
    }

    double sum_wt = 0, sum_tat = 0;

    for (int i = 0; i < n; i++) {
        sum_wt += waiting_time[i];
        sum_tat += turnaround_time[i];
    }

    double avg_wt = sum_wt / n;
    double avg_tat = sum_tat / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
