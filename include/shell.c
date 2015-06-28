#include "shell.h"
string buffer = "\0                                  ";

u8int maincolor = 0x0f;
int cBlock = 0;
int cDirLength = 0;

void shell_enterpressed(){
	printchar('\n');
	shell();
}

void shell_addchar(char c){
	concatc(buffer,c,buffer);
}

void shell_backspace(){
	remchar(buffer,buffer);
}

int shell_can_backspace(){
	if(strlen(buffer) > 0)
		return 1;
	return 0;
}

void init_shell(){
	setcolor(maincolor);
	cBlock = getRoot(0);
	cDirLength = (getRootEntries(0)*32)/512;
	print("CodeOS>");
}

void shell(){
	findCommand(buffer);
	buffer[0] = '\0';
	setcolor(maincolor);
	if(getY() == 0)
		print("CodeOS>");
	else
		print("\nCodeOS>");
}

void findCommand(string command){
    if(strcmp(command,"ping")){
		setcolor(0xf0);
		print("pong!");
		setcolor(0x0f);
	}else if(strcmp(command,"who is the best")){
		print("Well, of course it's Aaron.");
	}else if(strcmp(command,"cls")){
		cls();
	}else if(startswith(command,"setcolor")){
		int a = toHex(command[11]);
		int b = toHex(command[12]);
		if(startswith(command, "setcolor 0x") && strlen(command) == 13 && a != -1 && b != -1){
			maincolor = (a * 16)+b;
			setcolor(maincolor);
			colorRestOfScreen();
			print("color set to 0x");
			printchar(command[11]);
			printchar(command[12]);
		}else{
			setcolor(0x04);
			print("Please specify a color.");
		}
	}else if(strcmp(command,"ls")){
		listFiles(0,cBlock,cDirLength);
	}else if(startswith(command,"cd")){
		if(startswith(command, "cd ") && strlen(command) > strlen("cd ")){
			substring(command,command,3);
			if(isDir(0,cBlock,cDirLength,command)){
				int block = getFile(0,cBlock,cDirLength,command);
				if(block == getRoot(0)){
					cDirLength = (getRootEntries(0)*32)/512;
				}else{
					cDirLength = getDirLength(0,block);
				}
				cBlock = block;
			}else if(strcmp("\\",command)){
				cDirLength = (getRootEntries(0)*32)/512;
				cBlock = getRoot(0);
			}else{
				setcolor(0x04);
				print("\"");
				print(command);
				print("\" is not a directory!");
			}
		}else{
			setcolor(0x04);
			print("Please specify a directory.");
		}
	}else if(strcmp(command,"test")){
		printnum(getDirLength(0,cBlock));
	}else if(strcmp(command,"diskinfo")){
		println("DISK 0:");
		println("  PARTITION 0:");
		print("    LOCATION: ");
		printhex(getFirstPart(0));
		print("\n    ROOT LOCATION: ");
		printhex(getRoot(0));
		print("\n    SECTORS PER CLUSTER: ");
		printhex(getClusterSize(0));
		print("\n    ROOT ENTRIES: ");
		printhex(getRootEntries(0));
	}else if(strcmp(command,"help")){
		println("Commands:");
		println("ping: Says pong.");
		println("cls: Clears the screen.");
		println("setcolor 0x##: Set the attribute byte of the screen.");
		println("who is the best: Try it.");
	}else{
		int bg = maincolor/16;
		if(bg == 0x4)
			setcolor((bg*16)+0xf);
		else
			setcolor((bg*16)+0x4);
		print("No such command ");
		print(command);
		print(".");
	}
}