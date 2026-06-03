/*
 * Lab 6: Virtual Memory Management - NRU
 * Author: Matan Ashkenazi
 */

#include <stdio.h>
#include <stdlib.h>
#include "vmem_nru.h"

int main() {
    FILE *file = fopen("memory_accesses.txt", "r");
    if (!file) {
        printf("Error: Could not open memory_accesses.txt\n");
        return 1;
    }

    init_page_table();

    uint32_t addr;
    char op;
    
    int access_count = 0;
    int total_faults = 0;
    int total_disk_writes = 0;

    while (fscanf(file, "%u %c", &addr, &op) == 2) {
        access_count++;

        int is_hit = 0;
        int evicted_class = -1;
        int disk_write = 0;
        
        uint32_t page_num;
        uint32_t offset;
        get_page_and_offset(addr, &page_num, &offset);

        access_memory(addr, op, &is_hit, &evicted_class, &disk_write);

        if (!is_hit) {
            total_faults++;
        }
        if (disk_write) {
            total_disk_writes++;
        }

        int frame = page_table[page_num].frame_number;
        const char* status = is_hit ? "HIT" : "FAULT";

        if (evicted_class != -1) {
            printf("Addr:%u|Page:%u|Op:%c|Frame:%d|Status:%s|NRU_Class:%d\n", 
                   addr, page_num, op, frame, status, evicted_class);
        } else {
            printf("Addr:%u|Page:%u|Op:%c|Frame:%d|Status:%s|NRU_Class:N/A\n", 
                   addr, page_num, op, frame, status);
        }

        if (access_count % CLOCK_INTERVAL == 0) {
            printf("CLOCK INTERRUPT: Resetting R bits\n");
            clock_interrupt();
        }
    }

    fclose(file);

    // דוח סטטיסטי מסכם
    printf("\n--- Simulation Summary ---\n");
    printf("Total Accesses: %d\n", access_count);
    printf("Total Faults: %d\n", total_faults);
    printf("Total Disk Writes: %d\n", total_disk_writes);

    return 0;
}