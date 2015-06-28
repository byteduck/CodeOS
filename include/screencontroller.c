#include "screencontroller.h"
u8int color = 0x0f;

void setcolor(u8int c){
	color = c;
}

void print(string s){
	printf(s,color);
}

void println(string s){
	printf(s,color);
	printf("\n",color);
}

void printnum(int num){
	printInt(num,color);
}

void cls(){
	clear_screen(color);
}

void printchar(char c){
	putchar(c,color);
}

void colorRestOfScreen(){
	char *vidmem = (char *)0xb8000;
	int position = getPos();
	while(position < 80*25*2){
		position++;
		vidmem[position] = color;
		position++;
	}
}

void printhex(int n){
	s32int tmp;

    print("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            printchar(tmp-0xA+'a');
        }
        else
        {
            noZeroes = 0;
            printchar(tmp+'0');
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        printchar(tmp-0xA+'a');
    }
    else
    {
        printchar(tmp+'0');
    }

}