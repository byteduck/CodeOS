#ifndef COMMON_H
#define COMMON_H
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;
typedef char *string;

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
int strcmp(string str1,string str2);
void concat(string a, string b, string c);
void concatc(string a, char b, string c);
void remchar(string a, string b);
int toHex(char a);
int strncmp(string a, string b, int l);
int startswith(string a, string b);
void preparedisk(int disk, int addr);
void strcpy(char a[], char b[]);
char tolower(char a);
void strtolower(char a[], char b[]);
void substring(char a[], char b[], int index);
#endif