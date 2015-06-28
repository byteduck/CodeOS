#include "vga.h"
u8int cursor_x = 0;
u8int cursor_y = 0;
char *vidmem = (char *)0xb8000;

void clear_screen(u8int color){
   int i;
   for(i = 0; i < 80*25*2; i++){
	   vidmem[i++] = ' ';
	   vidmem[i] = color;
   }
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
}

void move_cursor()
{
   u16int cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void putchar(char c, u8int color){
	u16int location;
	if(c == 0x08 && cursor_x){
		cursor_x--;
		location = (cursor_y * 80 + cursor_x)*2;
		vidmem[location] = ' ';
		vidmem[location+1] = 0x0f;
	}else if(c == 0x09){
		cursor_x = (cursor_x+8) & ~(8-1);
	}else if(c == '\r'){
		cursor_x = 0;
	}else if(c == '\n'){
		cursor_x = 0;
		cursor_y++;
	}else if(c >= ' '){
		location = (cursor_y * 80 + cursor_x)*2;
		vidmem[location] = c;
		vidmem[location + 1] = color;
		cursor_x++;
	}
	
	if(cursor_x >= 80){
		cursor_x = 0;
		cursor_y++;
	}
	scroll(color);
	move_cursor();
}

void printf(char *c, u8int color){
	int i = 0;
	while(c[i]){
		putchar(c[i++], color);
	}
}

void printInt(int n, u8int color){
	if(n == 0){
		printf("0",color);
		return;
	}
	char buffer[50];
	int i = 0;

	int isNeg = n<0;

	unsigned int n1 = isNeg ? -n : n;

	while(n1!=0)
	{
		buffer[i++] = n1%10+'0';
		n1=n1/10;
	}

	if(isNeg)
		buffer[i++] = '-';

	buffer[i] = '\0';

	for(int t = 0; t < i/2; t++)
	{
		buffer[t] ^= buffer[i-t-1];
		buffer[i-t-1] ^= buffer[t];
		buffer[t] ^= buffer[i-t-1];
	}
	
	printf(buffer, color);
}

void scroll(u8int color){
   if(cursor_y >= 25){
       	int i = 80*2;
		while(i < 80*25*2){
			vidmem[i-(80*2)] = vidmem[i];
			i++;
		}
		i = 80*2*24;
		while(i < 80*25*2){
			vidmem[i++] = ' ';
			vidmem[i++] = 0x07;
		}
		cursor_y--;
   }
}

void center_print(char *c, u8int color){
	if(cursor_x > 0){
		printf("\n",color);
	}
	int i = 0;
	while(c[i]){
		i++;
	}
	if(i > 80){
		printf(c,color);
	}else{
		if(i % 2 == 0){
			int h = (80-i)/2;
			int j = 0;
			while(j < h){
				putchar(' ', color);
				j++;
			}
			printf(c,color);
			j = 0;
			while(j < h){
				putchar(' ', color);
				j++;
			}
		}else{
			int h = (80-i)/2;
			int j = 0;
			while(j < h){
				putchar(' ', color);
				j++;
			}
			printf(c,color);
			j = 0;
			h--;
			while(j < h+2){
				putchar(' ', color);
				j++;
			}
		}
	}
}

int getY(){
	return cursor_y;
}

int getX(){
	return cursor_x;
}

int getPos(){
	return ((cursor_y*80)+cursor_x)*2;
}