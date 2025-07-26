#include <allocator.h>

int main()
{
    void *ptrs[4];
    void *ptr = NULL;

    for (uint8_t i = 1; i <= 4; i++)
    {
        printf("---------\n");
        ptr = malloc_(5 * i);
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

    free_(ptrs[2]); // 15 byte
    void *new_ptr = realloc_(ptrs[1], 26);
    if (new_ptr)
    {
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