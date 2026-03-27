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
    int Ci;
    int Pi;
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
        tasks[i].remaining_time = 0;
    }

    sort_tasks(tasks, n);

    int periods[MAX_TASKS];
    for (int i = 0; i < n; i++) {
        periods[i] = tasks[i].Pi;
    }

    int hyperperiod = calculate_hyperperiod(periods, n);

    printf("\nHyperperiod: %d\n", hyperperiod);
    printf("\nSchedule:\n");

    for (int time = 0; time < hyperperiod; time++) {

        for (int i = 0; i < n; i++) {
            if (time % tasks[i].Pi == 0) {
                tasks[i].remaining_time = tasks[i].Ci;
            }
        }

        int executed = -1;

        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                executed = i;
                break;
            }
        }

        if (executed != -1) {
            printf("Time %2d: Task %d\n", time, tasks[executed].id);
            tasks[executed].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }

    return 0;
}
