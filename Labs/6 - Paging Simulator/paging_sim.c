#include "paging_sim.h"

void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset){
    *page_num = logical_addr / PAGE_SIZE;
    *offset = logical_addr % PAGE_SIZE;
}

uint32_t calculate_physical_address(uint32_t frame_num, uint32_t offset){
    return (frame_num * PAGE_SIZE) + offset;
}

int translate_and_load(uint32_t logical_addr, PageTableEntry *page_table, int *next_free_frame){
    uint32_t page_num = 0;
    uint32_t offset = 0;

    get_page_and_offset(logical_addr, &page_num, &offset);

    if (page_table[page_num].valid == 1){
        return calculate_physical_address(page_table[page_num].frame_number, offset);
    }
    else { //Page Fault
        if (*next_free_frame < NUM_FRAMES){
            page_table[page_num].frame_number = *next_free_frame;
            page_table[page_num].valid = 1;

            uint32_t phys_addr = calculate_physical_address(*next_free_frame, offset);
            (*next_free_frame)++;

            return phys_addr;
        }
        else {
            return -1;
        }

    }

}
