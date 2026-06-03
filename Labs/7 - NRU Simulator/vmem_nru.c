#include "vmem_nru.h"
#include <stdio.h>

PageTableEntry page_table[NUM_PAGES];
int frames_allocated = 0;

void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset){
    *page_num = (logical_addr / PAGE_SIZE) % NUM_PAGES;
    *offset = logical_addr % PAGE_SIZE;
}

void init_page_table() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
        page_table[i].referenced = 0;
        page_table[i].modified = 0;
    }
    frames_allocated = 0;
}

int access_memory(uint32_t addr, char op, int *is_hit, int *evicted_class, int *disk_write){
    uint32_t page_num = 0;
    uint32_t offset = 0;

    get_page_and_offset(addr, &page_num, &offset);

    //Printed variables from main
    *is_hit = 0;
    *evicted_class = -1;
    *disk_write = 0;

    // Page Hit
    if (page_table[page_num].valid) {
        *is_hit = 1;
        page_table[page_num].referenced = 1;
        if (op == 'W') {
            page_table[page_num].modified = 1;
        }
        return (page_table[page_num].frame_number * PAGE_SIZE) | offset;
    }

    //Page Fault
    int allocated_frame = -1;
    
    if (frames_allocated < NUM_FRAMES) {
        allocated_frame = frames_allocated++;
    } else {
        // NRU Algorithm
        int best_class = 4;
        int out_index = -1;

        for (int i = 0; i < NUM_PAGES; i++) {
            if (page_table[i].valid) {
                int r = page_table[i].referenced;
                int m = page_table[i].modified;
                int current_class = (r << 1) | m; // 00=0, 01=1, 10=2, 11=3

                if (current_class < best_class) {
                    best_class = current_class;
                    out_index = i;
                } else if (current_class == best_class) {
                    if (out_index == -1 || i < out_index) {
                        page_num = i;
                    }
                }
            }
        }

        *evicted_class = best_class;
        allocated_frame = page_table[out_index].frame_number;

        if (page_table[out_index].modified) {
            printf("Evicting dirty page\n");
            *disk_write = 1;
        }

        page_table[out_index].valid = 0;
        page_table[out_index].frame_number = -1;
        page_table[out_index].referenced = 0;
        page_table[out_index].modified = 0;
    }

    page_table[page_num].valid = 1;
    page_table[page_num].frame_number = allocated_frame;
    page_table[page_num].referenced = 1;
    page_table[page_num].modified = (op == 'W') ? 1 : 0;

    return (allocated_frame * PAGE_SIZE) | offset;
}

void clock_interrupt() {
    for (int i = 0; i < NUM_PAGES; i++) {
        if (page_table[i].valid) {
            page_table[i].referenced = 0;
        }
    }
}
