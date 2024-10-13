#ifndef SAFE_STR_H
#define SAFE_STR_H

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>

#define uninit(x) free(x)

typedef unsigned int u32;
typedef unsigned short int u16;
typedef unsigned char u8;

typedef struct s_string
{
    u32 count;
    char data[0];
} String;

u32 length(const char *);
String *init(const char *);
String *concat(String *, char *);

#endif // !SAFE_STR_H