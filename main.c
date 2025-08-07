#include <stdio.h>
#include "allocator.h"

char *receive_input();
char *getMainCommand(char *);
char *getSubCommand(char *);
uint8_t compareStr(const char *, char *);
void outputStr(char *, char);

void led_handler();
void help_handler();

typedef struct map
{
    const char *key;
    void (*handler)(/*char **args, int argc*/); // add (char **args, int argc) logic later
} map_t;

map_t cmds[] = {
    {"led", led_handler},
    {"help", help_handler}};

int main()
{
    char *input = receive_input();
    // char input[] = "led on";
    char *main_command = getMainCommand(input);
    char *sub_command = getSubCommand(input);

    for (uint8_t i = 0; i < sizeof(cmds) / (sizeof(const char *) + sizeof(void (*)(char **))); i++)
    {

        if (compareStr(cmds[i].key, main_command))
        {
            cmds[i].handler();
        }
    }

    return 0;
} // Test phrase: Somebody once told me that world is gonna rule me

void led_handler()
{
    const char *led_params[] = {"on", "off"};
    printf("led\n");
}

void help_handler()
{
    printf("help\n");
}

char *getSubCommand(char *input)
{
    char symbol = *input;
    uint8_t i = 0;
    while (symbol != ' ' && symbol != '\0')
    {
        i++;
        symbol = *(input + i);
    }
    if (symbol == ' ')
    {
        uint8_t buffer_size = 10;
        char *buffer = malloc_(buffer_size);
        uint8_t j = 0;
        i++;
        symbol = *(input + i);
        *(buffer + j) = symbol;
        while (symbol != ' ' && symbol != '\0')
        {
            symbol = *(input + i);
            if (buffer_size >= j)
            {
                buffer_size += 10;
                buffer = realloc_(buffer, buffer_size);
            }
            if (symbol == ' ')
            {
                *(buffer + i) = '\0';
            }
            else
            {
                *(buffer + j) = symbol;
            }
            i++;
            j++;
        }
        return buffer;
    }
    return NULL;
}

char *getMainCommand(char *input)
{
    uint8_t buffer_size = 10;
    char *buffer = malloc_(buffer_size);
    uint8_t i = 0;
    char symbol = *input;
    while (symbol != ' ' && symbol != '\0')
    {
        symbol = *(input + i);
        if (buffer_size >= i)
        {
            buffer_size += 10;
            buffer = realloc_(buffer, buffer_size);
        }
        if (symbol == ' ')
        {
            *(buffer + i) = '\0';
        }
        else
        {
            *(buffer + i) = symbol;
        }
        i++;
    }
    return buffer;
}

char *receive_input()
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
        index++;
    }
    *(RX_data_buffer + index - 1) = '\0';
    // header_t *current_block = (header_t *)((uint8_t *)RX_data_buffer - sizeof(header_t)); // check that allocator is correct
    // printf("%d", current_block->data_size);
    return RX_data_buffer;
}

uint8_t compareStr(const char *command_ptr, char *input_ptr)
{
    uint16_t index = 0;
    uint8_t command_symbol = *command_ptr;
    uint8_t input_symbol = *input_ptr;
    while (command_symbol != '\0' || input_symbol != '\0')
    {
        if (command_symbol != input_symbol)
            return 0;
        index++;
        command_symbol = *(command_ptr + index);
        input_symbol = *(input_ptr + index);
    }
    if (command_symbol != input_symbol)
        return 0;
    return 1;
}

void outputStr(char *ptr, char split_symbol)
{
    uint16_t index = 0;
    while (*(ptr + index) != split_symbol)
    {
        printf("%c - %d\n", *(ptr + index), *(ptr + index));
        index++;
    }
    printf("%c - %d\n", *(ptr + index), *(ptr + index));
    printf("\n");
}