#include "app.h"

void curses_app() {
  initscr(); // initialize curses
  cbreak(); // disables line buffering
  keypad(stdscr, TRUE); // enables keypad
  noecho();
  // raw(); // no generate signal
  if (login() == LOGIN_FAILED) curses_end();

  curs_set(0); // no cursor
  nodelay(stdscr, TRUE); // non-blocking getch()

  char *choices[] = {
    "Auto fantastico",
    "Carrera",
    "Choque",
    "Personal",
    "Viaje",
    "Exit"
  };
  uint32_t delays[] = {500000, 500000, 500000, 500000, 500000};
  uint32_t *delayptr = NULL;
  char *name = NULL;

  while (1) {
    MenuOption choice = menu(choices);

    sequence_fn sequence;
    switch (choice) {
      case FANTASTIC_CAR:
        sequence = &fantastic_car;
        delayptr = &delays[FANTASTIC_CAR];
        name = choices[FANTASTIC_CAR];
        break;
      case RACE:
        sequence = &race;
        delayptr = &delays[RACE];
        name = choices[RACE];
        break;
      case CRASH:
        sequence = &crash;
        delayptr = &delays[CRASH];
        name = choices[CRASH];
        break;
      case PERS:
        sequence = &pers;
        delayptr = &delays[PERS];
        name = choices[PERS];
        break;
      case TRAVEL:
        sequence = &travel;
        delayptr = &delays[TRAVEL];
        name = choices[TRAVEL];
        break;
      case EXIT:
        curses_end();
        break;
    }

    while (1) {
      if (sequence(delayptr, name) == LED_QUIT) break;
    }
  }
}

void curses_end() {
  endwin();
  exit(0);
}

MenuOption menu(char *choices[]) {
  clear();

  // int n_choices = sizeof(*choices);
  int n_choices = 6;
  ITEM **items = calloc(n_choices + 1, sizeof(ITEM *));
  items[n_choices] = NULL;
  for (int i = 0; i < n_choices; ++i) items[i] = new_item(choices[i], "");
  MENU *menu = new_menu(items);
  post_menu(menu);
  refresh();

  MenuOption choice;
  ITEM *cur_item;
  int ch;
  int is_selected = 0;
  while (!is_selected) {
    ch = getch();
    switch (ch) {
      case KEY_DOWN:
        menu_driver(menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(menu, REQ_UP_ITEM);
        break;
      case KEY_ENTER:
      case '\n':
        cur_item = current_item(menu);
        choice = cur_item->index;
        is_selected = 1;
        break;
    }
  }

  for (int i = 0; i < n_choices + 1; ++i) free_item(items[i]);
  free_menu(menu);
  return choice;
}
