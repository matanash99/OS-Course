#ifndef PAGING_SIM_H
#define PAGING_SIM_H

#include <stdint.h>

#define PAGE_SIZE 256
#define NUM_PAGES 256
#define NUM_FRAMES 128
#define PHYS_MEM_SIZE (NUM_FRAMES * PAGE_SIZE)

typedef struct {
    int frame_number;
    int valid;
} PageTableEntry;

// חתימות הפונקציות למשימות
void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset);
uint32_t calculate_physical_address(uint32_t frame_num, uint32_t offset);
int translate_and_load(uint32_t logical_addr, PageTableEntry *page_table, int *next_free_frame);

#endif