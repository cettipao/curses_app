#ifndef LOGIN_H
#define LOGIN_H

#include <curses.h>
#include <stdint.h>

#define LOGIN_SUCCESS 1
#define LOGIN_FAILED  0

#define PASSWORD_SIZE 5

uint8_t login(void);

void display_attempts(int);
void input_password(char *);
int pwdcmp(char *, char *);

#endif  // LOGIN_H
