#include "timer.h"
int timer_ticks = 0;
void timer_handler(struct regs *r){
    /* Increment our 'tick count' */
    timer_ticks++;

    //ONE SECOND = 18 TICKS
}