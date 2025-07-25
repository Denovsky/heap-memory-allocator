#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_HEAP_SIZE 1024

typedef struct header
{
    size_t data_size;
    struct header *prev;
    struct header *next;
} header_t;

void *create_block(size_t);

void *malloc(size_t);
void *realloc(void *, size_t);
void free(void *);

uint8_t heap[MAX_HEAP_SIZE];
size_t heap_top = 0;
header_t *first_block = NULL;
header_t *past_block = NULL;

int main()
{

    void *ptr = malloc(10);

    // header_t *ptr_header = (header_t *)((uint8_t *)ptr - sizeof(header_t));
    printf("\nPtr address: %p\n\n", ptr);

    // printf("Ptr1 info:\n");
    // printf("Header address: %p\n", ptr_header);
    // printf("Ptr1 data size: %d\n", ptr_header->data_size);
    // printf("Ptr1 next block: %p\n", ptr_header->next);
    // printf("Ptr1 past block: %p\n", ptr_header->prev);
    return 0;
}

void *create_block(size_t data_size)
{
    header_t *current_block = (header_t *)&heap[heap_top];
    current_block->data_size = data_size;
    current_block->prev = past_block;
    current_block->next = NULL;
    if (past_block)
        past_block->next = current_block;
    past_block = current_block;
    return current_block;
}

void *malloc(size_t data_size)
{
    void *data_section = NULL;

    if (!first_block)
    {
        first_block = create_block(data_size);

        // printf("First block size: %d\n", first_block->data_size);
        // printf("First block next block: %p\n", first_block->next);
        // printf("First block past block: %p\n", first_block->prev);

        // printf("First block address: %p\n", first_block);
        data_section = ((uint8_t *)first_block + sizeof(header_t));
        // printf("First data section address: %p\n", data_section);
        // printf("First block size: %d\n", ((uint8_t *)data_section + data_size) - (uint8_t *)first_block);
    }
    else
    {
        header_t *temp_block = first_block;
        heap_top = sizeof(header_t) + temp_block->data_size;
        while (temp_block->next)
        {
            printf("Heap top: %d\n", heap_top);
            if (((uint8_t *)temp_block->next) - ((uint8_t *)temp_block + sizeof(header_t) + temp_block->data_size) >= data_size + sizeof(header_t))
            {
                printf("It fit!\n");
                data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
                return data_section;
            }
            else
            {
                printf("Na-h...\n");
                heap_top += (uint8_t *)temp_block->next - (uint8_t *)temp_block - sizeof(header_t) - temp_block->data_size;
                temp_block = temp_block->next;
            }
        }
        printf("Heap top: %d\n", heap_top);

        if (heap_top + sizeof(header_t) + data_size > MAX_HEAP_SIZE)
            return NULL;

        data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
    }
    return data_section;
}