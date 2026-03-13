#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process_id[n];
    int arrival_time[n];
    int burst_time[n];
    int priority[n];
    int completion_time[n];
    int turnaround_time[n];
    int waiting_time[n];
    int completed[n];

    int current_time = 0;
    int completed_count = 0;

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

        completed[i] = 0;
    }

    while (completed_count < n) {
        int highest_priority = 9999;
        int selected_process = -1;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && completed[i] == 0) {
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
            int start_time = current_time;

            completion_time[selected_process] =
                start_time + burst_time[selected_process];

            turnaround_time[selected_process] =
                completion_time[selected_process] -
                arrival_time[selected_process];

            waiting_time[selected_process] =
                turnaround_time[selected_process] -
                burst_time[selected_process];

            current_time = completion_time[selected_process];

            completed[selected_process] = 1;
            completed_count++;
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

    for(int i = 0; i < n; i++){
        sum_tat += turnaround_time[i];
        sum_wt += waiting_time[i];
    }

    double avg_tat = sum_tat / n;
    double avg_wt = sum_wt / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}
