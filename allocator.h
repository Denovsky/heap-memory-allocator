#define MAX_HEAP_SIZE 1024
#define MAX_HEAP_TABLE_SIZE MAX_HEAP_SIZE / 8

uint8_t heap_area[MAX_HEAP_SIZE];
uint8_t heap_memory_allocation_table[MAX_HEAP_TABLE_SIZE] = {0};
uint8_t heap_top = 0;
uint8_t error = 0;