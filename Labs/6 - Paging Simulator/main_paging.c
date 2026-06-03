#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "paging_sim.h"

void run_simulation(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening addresses file");
        exit(1);
    }

    // אתחול טבלת הדפים (משימה 2)
    PageTableEntry page_table[NUM_PAGES];
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
    }

    int next_free_frame = 0;
    int total_accesses = 0;
    int total_page_faults = 0;

    char line[50];
    uint32_t logical_addr;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n' || line[0] == '#') continue;

        logical_addr = (uint32_t)strtoul(line, NULL, 10);
        total_accesses++;

                
        uint32_t page_num = 0, offset = 0;
        get_page_and_offset(logical_addr, &page_num, &offset);

        int is_fault = 0; 
        if (page_table[page_num].valid == 0) { total_page_faults++; is_fault = 1; }

        int physical_addr = 0;
        physical_addr = translate_and_load(logical_addr, page_table, &next_free_frame);


        if (physical_addr == -1) {
            printf("Logical Addr: %05u | Page: %3u | Offset: %3u | Physical: ----- | Status: OS_ERROR\n", 
                   logical_addr, page_num, offset);
        } else {
            printf("Logical Addr: %05u | Page: %3u | Offset: %3u | Physical: %05d | Status: %s\n", 
                   logical_addr, page_num, offset, physical_addr, is_fault ? "FAULT" : "HIT");
        }
    }

    fclose(file);

    double fault_rate = (total_accesses > 0) ? ((double)total_page_faults / total_accesses) * 100.0 : 0.0;
    printf("\n=====================================\n");
    printf("Paging Simulation Summary\n");
    printf("=====================================\n");
    printf("Total Addresses Accessed:  %d\n", total_accesses);
    printf("Total Page Faults:         %d\n", total_page_faults);
    printf("Page Fault Rate:           %.3f%%\n", fault_rate);
    printf("=====================================\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <addresses_file.txt>\n", argv[0]);
        return 1;
    }
    run_simulation(argv[1]);
    return 0;
}