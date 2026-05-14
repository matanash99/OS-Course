#ifndef SCHEDULER_LIB_H
#define SCHEDULER_LIB_H

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;
    int is_completed; // דגל עזר לסימון סיום
} Process;

// חתימות הפונקציות למימוש על ידי הסטודנטים
void simulate_fcfs(Process proc[], int n);
void simulate_sjf(Process proc[], int n);
void simulate_rr(Process proc[], int n, int quantum);
void simulate_srt(Process proc[], int n);

#endif
