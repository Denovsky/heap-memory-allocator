#include <stdio.h>
#include "cmdhandler.h"

/*----------*/
/* main command processing funcs: */
void led_handler(char **);
void help_handler(char **);
void echo_handler(char **);
/*----------*/

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
