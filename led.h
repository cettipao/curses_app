#ifndef LED_H
#define LED_H

#include <curses.h>
#include <stdint.h>

#define LED_QUIT 0
#define LED_CONTINUE 1

int delay(uint32_t *);
void display(uint8_t, uint32_t *, char *name);

int crash(uint32_t *, char *);
int fantastic_car(uint32_t *, char *);
int pers(uint32_t *, char *);
int race(uint32_t *, char *);
int travel(uint32_t *, char *);

#endif  // LED_H
