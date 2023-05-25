#ifndef APP_H
#define APP_H

#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#include "led.h"
#include "login.h"

#define KEY_ESC 0x1B

typedef enum {
  FANTASTIC_CAR,
  RACE,
  CRASH,
  PERS,
  TRAVEL,
  EXIT
} MenuOption;

typedef int (*sequence_fn)(uint32_t *, char *);

void curses_app(void);
void curses_end(void);

MenuOption menu(char *choices[]);

#endif  // APP_H
