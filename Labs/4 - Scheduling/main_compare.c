#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler_lib.h"

// פונקציית עזר להעתקת מערך תהליכים (כדי לא לדרוס נתונים בין הרצות)
void copy_processes(Process dest[], Process src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].remaining_time = src[i].burst_time;
        dest[i].is_completed = 0;
    }
}

// חישוב זמן המתנה ממוצע
float get_avg_wait(Process proc[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) total += proc[i].waiting_time;
    return total / n;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Could not open input.txt");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    Process original[n], temp[n];

    for (int i = 0; i < n; i++) {
        original[i].id = i + 1;
        fscanf(file, "%d %d", &original[i].arrival_time, &original[i].burst_time);
    }
    fclose(file);

    printf("--- Scheduling Comparison (n=%d) ---\n", n);
    printf("%-15s | %-20s\n", "Algorithm", "Avg Waiting Time");
    printf("------------------------------------------\n");

    // FCFS
    copy_processes(temp, original, n);
    simulate_fcfs(temp, n);
    printf("%-15s | %.2f\n", "FCFS", get_avg_wait(temp, n));

    // SJF
    copy_processes(temp, original, n);
    simulate_sjf(temp, n);
    printf("%-15s | %.2f\n", "SJF", get_avg_wait(temp, n));

    // Round Robin (Q=2)
    copy_processes(temp, original, n);
    simulate_rr(temp, n, 2);
    printf("%-15s | %.2f\n", "Round Robin", get_avg_wait(temp, n));

    // SRT
    copy_processes(temp, original, n);
    simulate_srt(temp, n);
    printf("%-15s | %.2f\n", "SRT", get_avg_wait(temp, n));

    printf("------------------------------------------\n");
    return 0;
}
