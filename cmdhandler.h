#ifndef CMDHANDLER_H
#define CMDHANDLER_H

#include "allocator.h"

typedef struct map
{
    const char *key;
    void (*handler)(char **args /*, int argc*/); // add (char **args, int argc) logic later
} map_t;

char *RXData();      // receive symbol by symbol from UART/USART
void TXData(char *); // transmit symbol by symbol by UART/USART

/*----------*/
/* main command validation funcs: */
char *getMainCommand(char *);
char *getSubCommand(char *);
uint8_t compareStr(const char *, char *);
/*----------*/

#endif