#include <stdio.h>
#include "allocator.h"

int main()
{

    uint16_t RX_data_buffer_size = 10;
    char *RX_data_buffer = malloc_(RX_data_buffer_size);
    uint16_t index = 0;
    char DR;
    while (DR != '\n')
    {
        if (index >= RX_data_buffer_size)
        {
            RX_data_buffer_size += 10;
            // printf("\n Pointer before: \t%p\n", RX_data_buffer);
            RX_data_buffer = realloc_(RX_data_buffer, RX_data_buffer_size);
            // printf(" Pointer after: \t%p\n\n", RX_data_buffer);
        }
        scanf("%c", &DR); // Data Register
        *(RX_data_buffer + index) = DR;
        printf("%c", *(RX_data_buffer + index));
        index++;
    }
    return 0;
} // Test phrase: Somebody once told me that world is gonna rule me