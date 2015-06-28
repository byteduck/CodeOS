#include "common.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
   u8int ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16int inw(u16int port)
{
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

int strcmp(string str1,string str2){
    int i=0,flag=0;
   
    while(str1[i]!='\0' && str2[i]!='\0'){
         if(str1[i]!=str2[i]){
             flag=1;
             break;
         }
         i++;
    }

    if (flag==0 && str1[i]=='\0' && str2[i]=='\0')
         return 1;
    else
         return 0;

}

void concat(string a, string b, string c){
	int len = strlen(a)+strlen(b);
	int i = 0;
	while(i < strlen(a)){
		c[i] = a[i];
		i++;
	}
	i = 0;
	while(i < strlen(b)){
		c[i+strlen(a)] = b[i];
		i++;
	}
	c[len] = '\0';
}

void concatc(string a, char b, string c){
	int len = strlen(a)+1;
	int i = 0;
	while(i < strlen(a)){
		c[i] = a[i];
		i++;
	}
	c[i] = b;
	c[len] = '\0';
}

void remchar(string a, string b){
	int i = 0;
	while(i < strlen(a)-1){
		b[i] = a[i];
		i++;
	}
	b[i] = '\0';
}

int toHex(char c){
	if(c == '0'){
		return 0x0;
	}if(c == '1'){
		return 0x1;
	}if(c == '2'){
		return 0x2;
	}if(c == '3'){
		return 0x3;
	}if(c == '4'){
		return 0x4;
	}if(c == '5'){
		return 0x5;
	}if(c == '6'){
		return 0x6;
	}if(c == '7'){
		return 0x7;
	}if(c == '8'){
		return 0x8;
	}if(c == '9'){
		return 0x9;
	}if(c == 'a' || c == 'A'){
		return 0xa;
	}if(c == 'b' || c == 'B'){
		return 0xb;
	}if(c == 'c' || c == 'C'){
		return 0xc;
	}if(c == 'd' || c == 'D'){
		return 0xd;
	}if(c == 'e' || c == 'E'){
		return 0xe;
	}if(c == 'f' || c == 'F'){
		return 0xf;
	}
	return -1;
}

int strncmp(string a, string b, int l){
   int c = 0;
   
   while (a[c] == b[c] && c < l) {
      c++;
   }
 
   if (c == l)
      return 1;
   else
      return 0;
}

int startswith(string a, string b){
	return strncmp(a,b,strlen(b));
}

void preparedisk(int disk, int addr){
	outb(0x1F1,0x00);
	outb(0x1F2,0x01);
	outb(0x1F3,(unsigned char)addr);
	outb(0x1F4,(unsigned char)(addr >> 8));
	outb(0x1F5,(unsigned char)(addr >> 16));
	outb(0x1F6,0xE0 | (disk << 4) | ((addr >> 24) & 0x0F));
	outb(0x1F7,0x20);
	while (!(inb(0x1F7) & 0x08)) {}
}

void strcpy(char a[], char b[]){
	for(int i = 0; i < strlen(a); i++){
		b[i] = a[i];
	}
}

char tolower(char a){
	if(a >= 'A' && a <= 'Z')
		return a+32;
	return a;
}

void strtolower(char a[], char b[]){
	for(int i = 0; i < strlen(a); i++){
		b[i] = tolower(a[i]);
	}
}

void substring(char a[], char b[], int index){
	int i = index;
	while(i < strlen(a)){
		b[i-index] = a[i];
		i++;
	}
	b[i-index] = '\0';
}