#pragma once

#include <stddef.h>
#include <stdint.h>

#define MAX_HEAP_SIZE 1024

typedef struct header
{
    size_t data_size;
    struct header *prev;
    struct header *next;
} header_t;

void *malloc_(size_t);
void free_(void *);
void *realloc_(void *, size_t);
void memset_(void *, uint8_t, size_t);
