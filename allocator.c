#include <stdio.h>
#include <stdint.h>

#define MAX_HEAP_SIZE 1024

typedef struct header
{
    size_t data_size;
    struct header *prev;
    struct header *next;
} header_t;

void *malloc(size_t);
void *realloc(void *, size_t);
void free(void *);

uint8_t heap[MAX_HEAP_SIZE];
uint16_t heap_top = 0;

int main()
{
    header_t *unit1 = (header_t *)&heap[heap_top];
    (*unit1).data_size = 10;
    heap_top += sizeof(header_t);
    printf("First block\n");

    header_t *unit2 = (header_t *)&heap[heap_top];
    (*unit2).data_size = 12;
    (*unit2).prev = unit1;
    (*unit1).next = unit2;
    heap_top += sizeof(header_t);
    printf("Second block\n");

    header_t *unit3 = (header_t *)&heap[heap_top];
    (*unit3).data_size = 24;
    (*unit3).prev = unit2;
    (*unit2).next = unit3;
    heap_top += sizeof(header_t);
    printf("Third block\n");

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < (sizeof(header_t) / 8); j++)
        {
            printf("i=%d j=%d : ", i, j);
            for (uint8_t k = 0; k < (sizeof(header_t) / 3); k++)
            {
                // printf("%d ", sizeof(header_t) * i + (sizeof(header_t) / 3) * j + k);
                printf("%d ", heap[sizeof(header_t) * i + (sizeof(header_t) / 3) * j + k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}

// void *malloc(size_t data_size)
// {
// }