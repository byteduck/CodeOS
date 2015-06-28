#ifndef VGA_H
#define VGA_H
#include "common.h"

void clear_screen(u8int color);

void putchar(char c, u8int color);

void printf(char *c, u8int color);

void move_cursor();

void scroll(u8int color);

void printInt(int i, u8int color);

void center_print(char *c, u8int color);

int getX();

int getY();

int getPos();

#endif