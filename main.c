#include <stdio.h>
#include "allocator.h"

char *RXData();      // receive symbol by symbol from UART/USART
void TXData(char *); // transmit symbol by symbol by UART/USART

/*----------*/
/* main command validation funcs: */
char *getMainCommand(char *);
char *getSubCommand(char *);
uint8_t compareStr(const char *, char *);
/*----------*/
/* main command processing funcs: */
void led_handler(char **);
void help_handler(char **);
void echo_handler(char **);
/*----------*/

typedef struct map
{
    const char *key;
    void (*handler)(char **args /*, int argc*/); // add (char **args, int argc) logic later
} map_t;

map_t cmds[] = {
    {"led", led_handler},
    {"help", help_handler},
    {"echo", echo_handler}};

int main()
{
    uint8_t cmds_size = sizeof(cmds) / (sizeof(const char *) + sizeof(void (*)(char **)));
    while (1)
    {
        char *input = RXData();
        // char input[] = "led on";
        char *main_command = getMainCommand(input);
        char *sub_command = getSubCommand(input);

        uint8_t isWork = 0;
        for (uint8_t i = 0; i < cmds_size; i++)
        {
            if (compareStr(cmds[i].key, main_command))
            {
                char *args[] = {"", &cmds_size, sub_command};
                isWork = 1;
                cmds[i].handler(args);
            }
        }
        if (!isWork)
        {
            TXData("No such command");
        }
    }
    return 0;
} // Test phrase: Somebody once told me that world is gonna rule me

void led_handler(char **args)
{
    const char *params[] = {"on", "off"};
    TXData("There is no working leds.");
}

void help_handler(char **args)
{
    // const char *params[] = NULL; // no params because of cmds list is params
    TXData("There is no escape!");
}

void echo_handler(char **args)
{
    if (args[2] != NULL)
    {
        TXData(args[2]);
    }
    else
    {
        TXData("Nothin to print");
    }
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
        while (/* symbol != ' ' && */ symbol != '\0')
        {
            symbol = *(input + i);
            if (buffer_size >= j)
            {
                buffer_size += 10;
                buffer = realloc_(buffer, buffer_size);
            }
            // if (symbol == ' ')
            // {
            //     *(buffer + j) = '\0';
            // }
            // else
            // {
            //     *(buffer + j) = symbol;
            // }
            *(buffer + j) = symbol;
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

char *RXData()
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
    if (*(RX_data_buffer + index - 1) == '\n')
        *(RX_data_buffer + index - 1) = '\0';
    // header_t *current_block = (header_t *)((uint8_t *)RX_data_buffer - sizeof(header_t)); // check that allocator is correct
    // printf("%d", current_block->data_size);
    return RX_data_buffer;
}

void TXData(char *ptr)
{
    uint16_t index = 0;
    char symbol = *ptr;
    while (symbol != '\0')
    {
        printf("%c", symbol, symbol); // Data Register
        index++;
        symbol = *(ptr + index);
    }
    printf("\n"); // Data Register
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
