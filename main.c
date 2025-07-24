#include <stdio.h>
#include <stdint.h>

#define MAX_HEAP_SIZE 1024
#define MAX_HEAP_TABLE_SIZE MAX_HEAP_SIZE / 8

// struct allocator_unit
// {
//     uint8_t size;
//     uint8_t *header;
// };

uint8_t compareStr(char *, char *);
void outputStr(char *);

uint8_t heap_area[MAX_HEAP_SIZE];
uint8_t heap_memory_allocation_table[MAX_HEAP_TABLE_SIZE] = {0};
uint8_t heap_top = 0;
uint8_t error = 0;

void *malloc(uint8_t);
void *realloc(void *, uint8_t);
void free(void *);

int main()
{
    uint8_t *ptr_top = malloc(10);
    uint8_t *next_test_ptr = malloc(12);
    for (uint8_t i = 0; i < 4; i++)
    {
        printf("%d ", heap_memory_allocation_table[i]);
    }
    return 0;
}

void *malloc(uint8_t size)
{
    if (heap_top >= MAX_HEAP_SIZE - 1 || heap_top + size >= MAX_HEAP_SIZE - 1 || size == 0)
    {
        return NULL;
    }
    // struct allocator_unit unit;

    uint8_t *header = &heap_area[heap_top];
    void *ptr = &heap_area[heap_top + 1];
    size_t temp_size = size + 1;
    int8_t current_table_unit = 0;
    int8_t offset = 7;
    uint8_t table_unit = 0;
    while (current_table_unit < MAX_HEAP_TABLE_SIZE)
    {
        table_unit = heap_memory_allocation_table[current_table_unit];
        offset = 7;
        // printf("%d - cur\n", current_table_unit);
        while (offset >= 0)
        {
            // printf("%d - offset\n", offset);
            // printf("%d", ((table_unit >> offset) & 1));
            if (((table_unit >> offset) & 1))
            {
                ptr = NULL;
                header = NULL;
                temp_size = size + 1;
            }
            else
            {
                if (ptr == NULL && temp_size == size)
                {
                    header = &heap_area[current_table_unit * 8 + (7 - offset)];
                    ptr = &heap_area[current_table_unit * 8 + (7 - offset) + 1];
                }
                temp_size--;
            }
            // printf("%d - temp_size\n", temp_size);
            if (temp_size <= 0)
            {
                break;
            }
            offset--;
        }
        if (temp_size <= 0)
        {
            break;
        }
        current_table_unit++;
    }
    temp_size = size + 1;
    if (ptr == NULL)
        return NULL;
    (*header) = size;
    // printf("\n");
    // printf("%d - cur\n", current_table_unit);

    while (current_table_unit >= 0)
    {
        // printf("%d - cur\n", current_table_unit);
        while (offset < 8)
        {
            heap_memory_allocation_table[current_table_unit] |= (0b1 << offset);
            temp_size--;
            if (temp_size <= 0)
            {
                break;
            }
            offset++;
        }
        offset = 0;
        if (temp_size <= 0)
        {
            break;
        }
        current_table_unit--;
    }
    return ptr;
}

void *realloc(void *, uint8_t)
{
}

void free(void *ptr)
{
}

uint8_t compareStr(char *char1, char *char2)
{
    uint16_t index = 0;
    while (*(char1 + index) != '\n' || *(char2 + index) != '\0')
    {
        printf("%d - Array\n", *(char1 + index));
        printf("%d - String\n", *(char2 + index));
        if (*(char1 + index) == *(char2 + index))
        {
            index++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

void outputStr(char *ptr)
{
    uint16_t index = 0;
    while (*(ptr + index) != '\n')
    {
        printf("%c", *(ptr + index));
        index++;
    }
    printf("\n");
}