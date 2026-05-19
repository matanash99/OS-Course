#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>

Segment* init_memory(int total_size)
{
    Segment *head = (Segment *)malloc(sizeof(Segment));
    head->size = total_size;
    head->is_process = 0;
    head->start_address = 0;
    head->process_id = -1;
    head->next = NULL;

    return head;
}

void print_memory(Segment *head)
{   
    Segment *curr = head;
    while (curr) {
        if (curr->is_process) {
            printf("[P%d, Addr:%d, Size:%d] -> ", curr->process_id, curr->start_address, curr->size);
        } else {
            printf("[H, Addr:%d, Size:%d] -> ", curr->start_address, curr->size);
        }
        curr = curr->next;
    }
    printf("NULL\n");
}

void print_stats(Segment *head)
{
    int total = 0, used = 0, free_mem = 0, count = 0;
    int proc_count = 0, hole_count = 0;
    
    Segment *curr = head;
    while (curr) {
        total += curr->size;
        if (curr->is_process) {
            used += curr->size;
            proc_count++;
        } else {
            free_mem += curr->size;
            hole_count++;
        }
        count++;
        curr = curr->next;
    }
    
    float used_percent = total > 0 ? ((float)used * 100.0) / total : 0;
    float free_percent = total > 0 ? ((float)free_mem * 100.0) / total : 0;

    printf("Total Memory: %d\nUsed Memory: %d (%f)\nFree Memory: %d (%f)\nNumber of Segments: %d (%d processes, %d holes)\n", 
           total, used, used_percent, free_mem, free_percent, count, proc_count, hole_count);
}

Segment *allocate_first_fit(Segment *head, int process_id, int size)
{
    Segment *curr = head;
    
    while (curr) {
        if (!curr->is_process && curr->size >= size) {
            if (curr->size > size) {
                //Found first fit
                Segment *new_hole = (Segment *)malloc(sizeof(Segment));
                new_hole->is_process = 0;
                new_hole->process_id = -1;
                new_hole->start_address = curr->start_address + size;
                new_hole->size = curr->size - size;
                new_hole->next = curr->next;

                curr->is_process = 1;
                curr->process_id = process_id;
                curr->size = size;
                curr->next = new_hole;
            } else {
                curr->is_process = 1;
                curr->process_id = process_id;
            }
            return head;
        }
        curr = curr->next;
    }
    
    fprintf(stderr, "Out of Memory.\n");
    return head; 
}

Segment *allocate_best_fit(Segment *head, int process_id, int size)
{
    Segment *curr = head;
    Segment *best = NULL;

    //Find best
    while (curr) {
        if (!curr->is_process && curr->size >= size) {
            if (best == NULL || curr->size < best->size) {
                best = curr;
            }
        }
        curr = curr->next;
    }

    //Allocate best
    if (best != NULL) {
        if (best->size > size) {
            Segment *new_hole = (Segment *)malloc(sizeof(Segment));
            new_hole->is_process = 0;
            new_hole->process_id = -1;
            new_hole->start_address = best->start_address + size;
            new_hole->size = best->size - size;
            new_hole->next = best->next;

            best->is_process = 1;
            best->process_id = process_id;
            best->size = size;
            best->next = new_hole;
        } else {
            best->is_process = 1;
            best->process_id = process_id;
        }
        return head;
    }

    fprintf(stderr, "Out of Memory.\n");
    return head;
}

Segment *deallocate_mem(Segment *head, int process_id)
{
    Segment *curr = head;
    Segment *prev = NULL;

    while (curr) {
        if (curr->is_process && curr->process_id == process_id) {
            
            curr->is_process = 0;
            curr->process_id = -1;

            if (curr->next && !curr->next->is_process) {
                Segment *temp = curr->next;
                curr->size += temp->size;
                curr->next = temp->next;
                free(temp);
            }

            if (prev && !prev->is_process) {
                prev->size += curr->size;
                prev->next = curr->next;
                free(curr);
            }

            return head; // Return original head after modifying
        }
        prev = curr;
        curr = curr->next;
    }

    return head;
}