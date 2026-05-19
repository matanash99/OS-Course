#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"

void process_command(char *line, Segment **head) {
    char cmd[20];
    int id, size;

    if (sscanf(line, "%s", cmd) <= 0) return;

    if (strcmp(cmd, "alloc_ff") == 0) {
        sscanf(line, "%*s %d %d", &id, &size);
        printf(">> Allocating %d units for Process %d (First Fit)...\n", size, id);
        
        /* TODO: YOUR CODE HERE - Task 2 */
        allocate_first_fit(*head, id, size);
        
    } else if (strcmp(cmd, "alloc_bf") == 0) {
        sscanf(line, "%*s %d %d", &id, &size);
        printf(">> Allocating %d units for Process %d (Best Fit)...\n", size, id);
        
        /* TODO: YOUR CODE HERE - Task 3 */
        allocate_best_fit(*head, id, size);

    } else if (strcmp(cmd, "free") == 0) {
        sscanf(line, "%*s %d", &id);
        printf(">> Freeing Process %d...\n", id);
        
        /* TODO: YOUR CODE HERE - Task 4 */
        deallocate_mem(*head, id);

    } else if (strcmp(cmd, "print") == 0) {
		
        /* TODO: YOUR CODE HERE - Task 1 */
		/* Should print Memory & Memory Statistics */
        print_memory(*head);
        print_stats(*head);

    } else if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }
}

int main(int argc, char *argv[]) {
   
    
	
    /* TODO: YOUR CODE HERE - Task 1 (Initialization) */
    Segment *memory_head = init_memory(1024);

    if (argc > 1) {
        // מצב קריאה מקובץ
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            process_command(line, &memory_head);
        }
        fclose(file);
    } else {
        // מצב אינטראקטיבי
        char line[100];
        printf("Memory Simulator Ready. Commands: alloc_ff, alloc_bf, free, print, exit\n");
        while (1) {
            printf("> ");
            if (!fgets(line, sizeof(line), stdin)) break;
            process_command(line, &memory_head);
        }
    }

    return 0;
}
