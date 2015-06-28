#include "fat.h"
void listFiles(int disk, int addr, int len){
	int listed = 0;
	for(int s = 0; s < len; s++){
		preparedisk(disk,addr+s);
		unsigned char sect[512];
		for(int i = 0; i < 255; i++){
			u16int tmpword = (u16int)inw(0x1F0);
			sect[i*2] = ((unsigned char)(tmpword));
			sect[i*2+1] = ((unsigned char)(tmpword >> 8));
		}
		for(int i = 0; i < 512; i+=32){
			if(sect[i+11] != 0x0f && sect[i] != 0xe5 && sect[i+11] != 0x08 && sect[i] != 0){
				if(listed == 23){
					println("Press any key to continue...");
					pause();
					listed = 0;
				}
				listed++;
				for(int j = 0; j < 11; j++){
					if(sect[i+j] != 0x20){
						printchar(sect[i+j]);
					}
					if(j == 7 && (sect[i+11] >> 4) != 0x1){
						printchar('.');
					}
				}
				if((sect[i+11] >> 4) == 0x1){
					print(" <DIR>");
				}
				println("");
			}
		}
	}
}

int isDir(int disk, int addr, int len, string name){
	string namebuf = "             ";
	for(int s = 0; s < len; s++){
		preparedisk(disk,addr+s);
		unsigned char sect[512];
		for(int i = 0; i < 255; i++){
			u16int tmpword = (u16int)inw(0x1F0);
			sect[i*2] = ((unsigned char)(tmpword));
			sect[i*2+1] = ((unsigned char)(tmpword >> 8));
		}
		for(int i = 0; i < 512; i+=32){
			if(sect[i+11] != 0x0f && sect[i] != 0xe5 && sect[i+11] != 0x08){
				int k = 0;
				for(int j = 0; j < 11; j++){
					if(sect[i+j] != 0x20){
						namebuf[k] = sect[i+j];
						k++;
					}
					if(j == 7 && (sect[i+11] >> 4) != 0x1){
						namebuf[k] = '.';
						k++;
					}
				}
				namebuf[k] = '\0';
				strtolower(name,name);
				strtolower(namebuf,namebuf);
				if(strcmp(namebuf,name) && (sect[i+11] >> 4) == 0x1){
					return 1;
				}
			}
		}
	}
	return 0;
}

int getFile(int disk, int addr, int len, string name){
	int spc = getClusterSize(disk);
	int re = getRootEntries(disk);
	int root = getRoot(disk);
	string namebuf = "             ";
	for(int s = 0; s < len; s++){
		preparedisk(disk,addr+s);
		unsigned char sect[512];
		for(int i = 0; i < 255; i++){
			u16int tmpword = (u16int)inw(0x1F0);
			sect[i*2] = ((unsigned char)(tmpword));
			sect[i*2+1] = ((unsigned char)(tmpword >> 8));
		}
		for(int i = 0; i < 512; i+=32){
			if(sect[i+11] != 0x0f && sect[i] != 0xe5 && sect[i+11] != 0x08){
				int k = 0;
				for(int j = 0; j < 11; j++){
					if(sect[i+j] != 0x20){
						namebuf[k] = sect[i+j];
						k++;
					}
					if(j == 7 && (sect[i+11] >> 4) != 0x1){
						namebuf[k] = '.';
						k++;
					}
				}
				namebuf[k] = '\0';
				strtolower(name,name);
				strtolower(namebuf,namebuf);
				if(strcmp(name,namebuf)){
					int cluster = (((int)sect[i+27] << 8)+sect[i+26])-2;
					if(cluster < 0){
						return getRoot(disk);
					}
					return (spc*cluster)+root+((re*32)/512);
				}
			}
		}
	}
	return -1;
}

int getRoot(int disk){
	int pos = getFirstPart(disk);
	preparedisk(0,pos);
	int rsects = 0;
	int fats = 0;
	int size = 0;
	for(int i = 0; i < 255; i++){
		u16int tmpword = (u16int)inw(0x1F0);
		if(i == 0x7){
			rsects = (char)(tmpword);
		}
		if(i == 0x8){
			fats = (char)(tmpword);
		}
		if(i == 0xb){
			size = tmpword;
		}
	}
	return fats*size+rsects+pos;
}

int getFirstPart(int disk){
	preparedisk(disk,0);
	u16int pos = 0;
	for(int i = 0; i <= 255; i++){
		u16int tmpword = (u16int)inw(0x1F0);
		if(i == 227){
			pos = tmpword;
		}
	}
	return pos;
}

int getClusterSize(int disk){
	preparedisk(disk,getFirstPart(disk));
	for(int i = 0; i < 255; i++){
		u16int tmpword = (u16int)inw(0x1F0);
		if(i == 0x6){
			return (unsigned char)tmpword;
		}
	}
	return -1;
}

int getRootEntries(int disk){
	preparedisk(disk,getFirstPart(disk));
	int a = 0;
	int b = 0;
	for(int i = 0; i < 255; i++){
		u16int tmpword = (u16int)inw(0x1F0);
		if(i == 0x8){
			a = tmpword >> 8;
		}
		if(i == 0x9){
			b = tmpword << 8;
		}
	}
	return a+b;
}

int getDirLength(int disk, int addr){
	int len = 1;
	while(1 == 1){
		preparedisk(disk,addr+len);
		unsigned char sect[512];
		for(int i = 0; i < 255; i++){
			u16int tmpword = (u16int)inw(0x1F0);
			sect[i*2] = ((unsigned char)(tmpword));
			sect[i*2+1] = ((unsigned char)(tmpword >> 8));
		}
		int entriesGood = 16;
		int allzero = 0;
		for(int i = 0; i < 512; i+=32){
			if(i > 0 && sect[i] == (unsigned char)'.' && sect[i+11] == 0x10){
				return len;
			}
			if(sect[i+11] != 0x0f){
				if(((sect[i+11] & ( 1 << 6 )) >> 6) == 1){
					entriesGood--;
				}
			}
			if(sect[i+11] == (unsigned char)0){
				if(sect[i+12] != (unsigned char)0 && sect[i+10] != (unsigned char)0){
					entriesGood--;
				}
				else if(sect[i+12] == (unsigned char)0 && sect[i+10] == (unsigned char)0){
					allzero++;	
				}
			}
		}
		if(entriesGood < 16){
			return len;
		}
		if(allzero >= 15){
			return len;
		}
		len++;
	}
	return len;
}