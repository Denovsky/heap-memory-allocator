#include <allocator.h>

uint8_t heap[MAX_HEAP_SIZE];
size_t heap_top = 0;
header_t *first_block = NULL;
header_t *past_block = NULL;

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

void *malloc_(size_t data_size)
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
            if (diff >= data_size + sizeof(header_t))
            {
                data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
                return data_section;
            }
            else
            {
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

void *realloc_(void *ptr, size_t block_size)
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

void free_(void *ptr)
{
    header_t *current_block = (header_t *)((uint8_t *)ptr - sizeof(header_t));
    if (current_block == first_block)
        first_block = current_block->next;
    header_t *prev_block = current_block->prev;
    header_t *next_block = current_block->next;
    prev_block->next = next_block;
    next_block->prev = prev_block;
    memset_(current_block, 0, current_block->data_size + sizeof(header_t));
}

void memset_(void *ptr, uint8_t value, size_t num)
{
    if (ptr)
    {
        uint8_t *p = ptr;
        while (num--)
            *p++ = (uint8_t)value;
    }
}
