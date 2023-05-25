#include "led.h"

int delay(uint32_t *d) {
  int ch;
  int n = *d;
  while (n) {
    if ((ch = getch()) != ERR) {
      switch (ch) {
        case 0x1B: // ESCDELAY env
        case 'q':
          return LED_QUIT;
        case KEY_UP:
          *d -= 100000;
          n = *d;
          break;
        case KEY_DOWN:
          *d += 100000;
          n = *d;
          break;
        default:
          break;
      }
    }
    --n;
  }
  return LED_CONTINUE;
}

void display(uint8_t data, uint32_t *d, char *name) {
  clear();
  mvprintw(0, 0, "Sequencia: %s", name);
  move(2, 0);
  for (uint8_t mask = 0x80; mask > 0; mask >>= 1) {
    if (data & mask) addch('*');
    else addch('_');
  }
  mvprintw(4, 0, "Delay: %u", *d);
  mvprintw(5, 0, "Presione ESC o q para salir");
  refresh();
}

int crash(uint32_t *d, char *name) {
  uint8_t table[] = {
    0x81, 0x42, 0x24, 0x18,
    0x18, 0x24, 0x42
  };

  int table_size = sizeof(table) / sizeof(table[0]);

  for (int i = 0; i < table_size; ++i) {
    display(table[i], d, name);
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }
  return LED_CONTINUE;
}

int fantastic_car(uint32_t *d, char *name) {
  uint8_t data = 0x80;

  // right shift
  for (int i = 0; i < 8; ++i) {
    display(data, d, name);
    data >>= 1;
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }

  // left shift
  data = 0x02;
  for (int i = 0; i < 6; ++i) {
    display(data, d, name);
    refresh();
    data <<= 1;
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }
  return LED_CONTINUE;
}

int pers(uint32_t *d, char *name) {
  uint8_t table[] = {
    0x81, 0x42, 0x81, 0x42,
    0x24, 0x42, 0x81, 0x42,
    0x24, 0x18, 0x24, 0x42
  };

  int table_size = sizeof(table) / sizeof(table[0]);

  for (int i = 0; i < table_size; ++i) {
    display(table[i], d, name);
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }
  return LED_CONTINUE;
}

int race(uint32_t *d, char *name) {
  uint8_t table[] = {
    0x01, 0x01, 0x02, 0x02,
    0x04, 0x04, 0x08, 0x08,
    0x11, 0x12, 0x24, 0x28,
    0x50, 0x60, 0xC0, 0x80
  };

  int table_size = sizeof(table) / sizeof(table[0]);

  for (int i = 0; i < table_size; ++i) {
    display(table[i], d, name);
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }
  return LED_CONTINUE;
}

int travel(uint32_t *d, char *name) {
  uint8_t data = 0x01;
  for (int i = 0; i < 8; ++i) {
    display(data, d, name);
    data = (data << 1) | data;
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }

  data = 0x7F;
  for (int i = 0; i < 6; ++i) {
    display(data, d, name);
    data = (data >> 1) & data;
    if (delay(d) == LED_QUIT) return LED_QUIT;
  }

  return LED_CONTINUE;
}
