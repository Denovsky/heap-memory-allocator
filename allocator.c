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

header_t *create_block(size_t);

void *my_malloc(size_t);
void *my_realloc(void *, size_t);
void my_free(void *);

uint8_t heap[MAX_HEAP_SIZE];
size_t heap_top = 0;
header_t *first_block = NULL;
header_t *past_block = NULL;

int main()
{
    void *ptrs[4];
    void *ptr = NULL;

    for (uint8_t i = 1; i <= 4; i++)
    {
        printf("---------\n");
        ptr = my_malloc(5 * i);
        ptrs[i - 1] = ptr;
        printf("%d cycle\n", i);
        printf("---------\n\n");
    }
    for (uint8_t i = 1; i <= 4; i++)
    {
        header_t *ptr_header = (header_t *)((uint8_t *)ptrs[i - 1] - sizeof(header_t));
        printf("Ptr%d info:\n", i);
        // printf("Ptr address: \t\t%p\n", ptrs[i]);
        printf("Header address: \t%p\n", ptr_header);
        printf("Ptr%d data size: \t%d\n", i, ptr_header->data_size);
        printf("Ptr%d prev block: \t%p\n", i, ptr_header->prev);
        printf("Ptr%d next block: \t%p\n\n", i, ptr_header->next);
    }

    my_free(ptrs[2]); // 15 byte
    void *new_ptr = my_realloc(ptrs[1], 26);
    if (new_ptr)
    {
        printf("\n\nYes\n\n");
        ptrs[1] = new_ptr;
    }

    for (uint8_t i = 1; i <= 4; i++)
    {
        header_t *ptr_header = (header_t *)((uint8_t *)ptrs[i - 1] - sizeof(header_t));
        printf("Ptr%d info:\n", i);
        // printf("Ptr address: \t\t%p\n", ptrs[i]);
        printf("Header address: \t%p\n", ptr_header);
        printf("Ptr%d data size: \t%d\n", i, ptr_header->data_size);
        printf("Ptr%d prev block: \t%p\n", i, ptr_header->prev);
        printf("Ptr%d next block: \t%p\n\n", i, ptr_header->next);
    }
    return 0;
}

header_t *create_block(size_t data_size)
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

void *my_malloc(size_t data_size)
{
    void *data_section = NULL;
    if (first_block == NULL)
    {
        first_block = (header_t *)create_block(data_size);
        data_section = ((uint8_t *)first_block + sizeof(header_t));
    }
    else
    {
        header_t *temp_block = first_block;
        heap_top = sizeof(header_t) + temp_block->data_size;
        while (temp_block->next)
        {
            size_t diff = (uintptr_t)temp_block->next - ((uintptr_t)temp_block + sizeof(header_t) + temp_block->data_size);
            printf("Diff: %d", diff);
            if (diff >= data_size + sizeof(header_t))
            {
                printf("It fit!\n");
                data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
                return data_section;
            }
            else
            {
                printf("Na-h...\n");
                printf("\ndif : %d\n", sizeof(header_t) + (temp_block->next)->data_size);
                heap_top += sizeof(header_t) + (temp_block->next)->data_size + diff; // offset heap_top point on top of the next block
                temp_block = temp_block->next;
            }
        }

        if (heap_top + sizeof(header_t) + data_size > MAX_HEAP_SIZE)
            return data_section;

        data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
    }
    return data_section;
}

void *my_realloc(void *ptr, size_t block_size)
{
    if (ptr == NULL)
        return my_malloc(block_size);
    void *new_ptr = NULL;

    header_t *current_block = (header_t *)((uint8_t *)ptr - sizeof(header_t));

    if ((uintptr_t)current_block->next - (uintptr_t)ptr < block_size)
    {
        new_ptr = my_malloc(block_size);
        if (new_ptr)
        {
            for (size_t i = 0; i < current_block->data_size && i < block_size; i++)
            {
                *((uint8_t *)new_ptr + i) = *((uint8_t *)ptr + i);
            }
            my_free(ptr);
            return new_ptr;
        }
        return NULL;
    }
    current_block->data_size = block_size;
    return ptr;
}

void my_free(void *ptr)
{
    header_t *current_block = (header_t *)((uint8_t *)ptr - sizeof(header_t));
    if (current_block == first_block)
        first_block = current_block->next;
    header_t *prev_block = current_block->prev;
    header_t *next_block = current_block->next;
    prev_block->next = next_block;
    next_block->prev = prev_block;
    memset(current_block, 0, current_block->data_size + sizeof(header_t));
}