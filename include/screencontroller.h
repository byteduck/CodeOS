#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H
#include "vga.h"
void setcolor(u8int c);
void print(string s);
void println(string s);
void cls();
void printnum(int num);
void printchar(char c);
void colorRestOfScreen();
void printhex(int n);
#endif