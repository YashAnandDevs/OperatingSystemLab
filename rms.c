#include <stdio.h>

#define MAX_TASKS 10

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int calculate_hyperperiod(int periods[], int n) {
    int hp = periods[0];
    for (int i = 1; i < n; i++) {
        hp = lcm(hp, periods[i]);
    }
    return hp;
}

typedef struct {
    int id;
    int Ci; // Burst
    int Pi; // Period
    int Di; // Deadline
    int remaining_time;
} Task;

void sort_tasks(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].Pi > tasks[j].Pi) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Task tasks[MAX_TASKS];

    printf("Enter the USN: 1BF24CS335\n");

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;

        printf("Enter computation time (C%d): ", i + 1);
        scanf("%d", &tasks[i].Ci);

        printf("Enter period (P%d): ", i + 1);
        scanf("%d", &tasks[i].Pi);

        tasks[i].Di = tasks[i].Pi; // Deadline = Period
        tasks[i].remaining_time = 0;
    }

    sort_tasks(tasks, n);

    // Print table like in image
    printf("\nPID   Burst   Deadline   Period\n");
    for (int i = 0; i < n; i++) {
        printf("%d     %d        %d         %d\n",
               tasks[i].id,
               tasks[i].Ci,
               tasks[i].Di,
               tasks[i].Pi);
    }

    int periods[MAX_TASKS];
    for (int i = 0; i < n; i++) {
        periods[i] = tasks[i].Pi;
    }

    int hyperperiod = calculate_hyperperiod(periods, n);

    printf("\nScheduling occurs for %d ms\n\n", hyperperiod);

    for (int time = 0; time < hyperperiod; time++) {

        // Release jobs
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].Pi == 0) {
                tasks[i].remaining_time = tasks[i].Ci;
            }
        }

        int executed = -1;

        // Pick highest priority (shortest period)
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                executed = i;
                break;
            }
        }

        if (executed != -1) {
            printf("%dms : Task %d is running.\n", time, tasks[executed].id);
            tasks[executed].remaining_time--;
        } else {
            printf("%dms : CPU is idle.\n", time);
        }
    }

    return 0;
}
