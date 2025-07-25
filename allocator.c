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

    header_t *unit1 = (header_t *)create_block(10);
    heap_top += sizeof(header_t) + 10;
    heap_top += 33;
    header_t *unit2 = (header_t *)create_block(13);
    heap_top += sizeof(header_t) + 13;
    heap_top += 34;
    header_t *unit3 = (header_t *)create_block(22);
    heap_top += sizeof(header_t) + 22;
    header_t *unit4 = (header_t *)create_block(4);
    heap_top += sizeof(header_t) + 4;

    printf("Unit1 info:\n");
    printf("Unit1 pointer: %p\n", unit1);
    printf("Data size: %d\n", unit1->data_size);
    printf("Prev pointer: %p\n", unit1->prev);
    printf("Next pointer: %p\n", unit1->next);
    printf("\n");

    printf("Unit2 info:\n");
    printf("Unit2 pointer: %p\n", unit2);
    printf("Data size: %d\n", unit2->data_size);
    printf("Prev pointer: %p\n", unit2->prev);
    printf("Next pointer: %p\n", unit2->next);
    printf("\n");

    printf("Unit3 info:\n");
    printf("Unit3 pointer: %p\n", unit3);
    printf("Data size: %d\n", unit3->data_size);
    printf("Prev pointer: %p\n", unit3->prev);
    printf("Next pointer: %p\n", unit3->next);
    printf("\n");

    size_t data_size = 10;
    first_block = unit1;

    void *data_section = NULL;
    header_t *temp_block = first_block;
    heap_top = 0;
    while (temp_block->next)
    {
        heap_top += sizeof(header_t) + temp_block->data_size;
        printf("Heap top: %d\n", heap_top);
        if (((uint8_t *)temp_block->next) - ((uint8_t *)temp_block + sizeof(header_t) + temp_block->data_size) >= data_size + sizeof(header_t))
        {
            printf("It fit!\n");
            data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
            break;
        }
        else
        {
            printf("Na-h...\n");
            heap_top += (uint8_t *)temp_block->next - (uint8_t *)temp_block - sizeof(header_t) - temp_block->data_size;
            temp_block = temp_block->next;
        }
    }

    if (heap_top + sizeof(header_t) + data_size > MAX_HEAP_SIZE)
        return NULL;

    data_section = ((uint8_t *)create_block(data_size) + sizeof(header_t));
    return data_section;

    // for (uint8_t i = 0; i < 3; i++)
    // {
    //     printf("\n");
    //     printf("\n");
    //     printf("Data size: ");
    //     for (uint8_t k = 0; k < sizeof(size_t); k++)
    //     {
    //         printf("%d ", heap[sizeof(header_t) * i + k]);
    //     }
    //     printf("\n");

    //     printf("Previous block pointer: ");
    //     for (uint8_t k = 0; k < (sizeof(header_t) / 3); k++)
    //     {
    //         printf("%d ", heap[sizeof(header_t) * i + sizeof(size_t) + k]);
    //     }
    //     printf("\n");

    //     printf("Next block pointer: ");
    //     for (uint8_t k = 0; k < (sizeof(header_t) / 3); k++)
    //     {
    //         printf("%d ", heap[sizeof(header_t) * i + sizeof(size_t) + sizeof(struct uint8_t *) + k]);
    //     }
    // }
    // printf("\n");

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

// void *malloc(size_t data_size)
// {
//     if (!first_block)
//     {
//         first_block = create_block(data_size);
//         return first_block;
//     }
//     else
//     {
//         header_t *temp_block = first_block;
//         while (1)
//         {
//             if ((uint8_t *)temp_block->next - ((uint8_t *)temp_block + sizeof(header_t) + temp_block->data_size) >= data_size + sizeof(header_t))
//             {
//             }
//             else
//             {
//                 temp_block = temp_block->next;
//             }
//         }
//     }
// }