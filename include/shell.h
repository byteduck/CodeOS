#ifndef SHELL_H
#define SHELL_H
#define MAX_COMMANDS 100
#include "screencontroller.h"
#include "kbd.h"
#include "fat.h"

void init_shell();
void shell();
void shell_addchar(char c);
void shell_enterpressed();
void shell_backspace();
void findCommand(string command);
int shell_can_backspace();
#endif