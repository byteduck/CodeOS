#include "kbd.h"
unsigned char kbdus[256] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
	'\b', '\t',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
	'\"', '~', 0, '|',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	'<', '>', '?', 0, '*',
	0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0
	
};

int shift = 0;

void pause(){
	int i = 0;
	while(i < 100000000){
		i++;
	}
	while(inb(0x60) & 0x80){
		
	};
}
void keyboard_handler(struct regs *r){
    unsigned char scancode;
	
    scancode = inb(0x60);
	
    if (scancode & 0x80)
    {
		if(scancode == 0xAA)
			shift = 0;
    }
    else
    {
		if(scancode == 0x2a){shift = 1;return;}
		if(scancode == 0x1c){shell_enterpressed();return;}
		if(scancode == 0x0e){
			if(shell_can_backspace()){
				printchar(kbdus[scancode]);
			}
			shell_backspace();
			return;
		}
		if(shift){
			printchar(kbdus[scancode+90]);
			shell_addchar(kbdus[scancode+90]);
		}else{
			printchar(kbdus[scancode]);
			shell_addchar(kbdus[scancode]);
		}
    }
}