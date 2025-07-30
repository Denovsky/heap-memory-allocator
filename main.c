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
            RX_data_buffer = realloc_(RX_data_buffer, RX_data_buffer_size);
        }
        scanf("%c", &DR); // Data Register
        *(RX_data_buffer + index) = DR;
        printf("%c", *(RX_data_buffer + index));
        index++;
    }
    return 0;
}