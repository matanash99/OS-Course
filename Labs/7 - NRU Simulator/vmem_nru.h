#ifndef VNEM_NRU_H
#define VNEM_NRU_H

#include <stdint.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 16
#define NUM_FRAMES 4
#define CLOCK_INTERVAL 10


typedef struct {
    int frame_number;
    int valid;
    int referenced;
    int modified;
} PageTableEntry;

extern PageTableEntry page_table[NUM_PAGES];

//Functions
void init_page_table();
int access_memory(uint32_t addr, char op, int *is_hit, int *evicted_class, int *disk_write);
void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset);
void clock_interrupt();





#endif //VNEM_NRU_H