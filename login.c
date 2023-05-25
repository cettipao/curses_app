#include "login.h"

void display_attempts(int tries) {
  clear();
  mvprintw(0, 0, "Password no valida");
  mvprintw(1, 0, "Intentos disponibles: %d", tries);
  mvprintw(2, 0, "Presione cualquier tecla para continuar");
  refresh();
  getch();
}

uint8_t login() {
  char password[] = "abcde";
  char input[PASSWORD_SIZE];
  for (int tries = 3; tries > 0;) {
    input_password(input);
    if (pwdcmp(password, input)) return LOGIN_SUCCESS;
    --tries;
    display_attempts(tries);
  }
  return LOGIN_FAILED;
}

void input_password(char *input) {
  clear();
  mvprintw(0, 0, "Ingrese su password de 5 digitos: ");
  for (int i = 0; i < PASSWORD_SIZE; ++i) {
    input[i] = getch();
    addch('*');
    refresh();
  }
}

int pwdcmp(char *password, char *input) {
  for (int i = 0; i < 5; ++i) {
    if (password[i] != input[i]) return LOGIN_FAILED;
  }
  return LOGIN_SUCCESS;
}
