#include "scheduler_lib.h"

void simulate_fcfs(Process proc[], int n){
    if (!proc || n <= 0) return;

    int current_time = 0;
    for (int i = 0; i < n; i++){
        if (current_time < proc[i].arrival_time){
            current_time += proc[i].arrival_time - current_time;
        }
        proc[i].waiting_time = current_time - proc[i].arrival_time;
        current_time += proc[i].burst_time;
        proc[i].finish_time = current_time;
    }
}

int get_shortest(Process proc[], int n, int current_time){
    if (!proc || n <= 0) return -1;

    int min_index = -1;
    int min_remaining = 99999;

    for (int i = 0; i < n; i++){
        if (proc[i].arrival_time <= current_time && proc[i].is_completed == 0){
            if (proc[i].remaining_time < min_remaining){ 
                min_remaining = proc[i].remaining_time;
                min_index = i;
            }
        }
    }
    return min_index;
}

void simulate_sjf(Process proc[], int n){
    if (!proc || n <= 0) return;

    int current_time = 0;
    int completed = 0;

    while (completed < n){
        int min_index = get_shortest(proc, n, current_time);

        if (min_index == -1){
            current_time++;
        }
        else{
            proc[min_index].waiting_time = current_time - proc[min_index].arrival_time;
            current_time += proc[min_index].burst_time;
            proc[min_index].finish_time = current_time;
            proc[min_index].is_completed = 1;
            completed++;
        }
    }
}

void simulate_rr(Process proc[], int n, int quantum){
    if (!proc || n <= 0) return;

    int current_time = 0;
    int completed = 0;
    
    while (completed < n){
        int finished = 1;
        for (int i = 0; i < n; i++){
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0){
                finished = 0;
                if (proc[i].remaining_time > quantum){
                    current_time += quantum;
                    proc[i].remaining_time -= quantum;
                }
                else{
                    current_time += proc[i].remaining_time;
                    proc[i].waiting_time = current_time - proc[i].arrival_time - proc[i].burst_time;
                    proc[i].finish_time = current_time;
                    proc[i].remaining_time = 0;
                    completed++;
                }
            }
        }
        if (finished){
            current_time++;
        }
    }
}

void simulate_srt(Process proc[], int n){
    if (!proc || n <= 0) return;

    int current_time = 0;
    int completed = 0;

    while (completed < n){
        int min_index = get_shortest(proc, n, current_time);

        if (min_index == -1){
            current_time++;
        }
        else{
            proc[min_index].remaining_time--;
            if (proc[min_index].remaining_time == 0){
                proc[min_index].finish_time = current_time + 1;
                proc[min_index].waiting_time = proc[min_index].finish_time - proc[min_index].arrival_time - proc[min_index].burst_time;
                proc[min_index].is_completed = 1;
                completed++;
            }
            current_time++;
        }
    }
}