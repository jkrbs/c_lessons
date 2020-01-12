#include "termio.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef __unix__

#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
struct termios prev_term_state = {0};
int termio_init()
{
    if (tcgetattr(0, &prev_term_state) < 0) return EXIT_FAILURE;
    prev_term_state.c_lflag &= ~ICANON;
    prev_term_state.c_lflag &= ~ECHO;
    prev_term_state.c_cc[VMIN] = 1;
    prev_term_state.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &prev_term_state) < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void termio_fin()
{
    prev_term_state.c_lflag |= ICANON;
    prev_term_state.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &prev_term_state);
}

int termio_clear_screen()
{
    if (fputs("\e[1;1H\e[2J", stdout) < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

bool termio_getch(char* c)
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    if (select(1, &fds, NULL, NULL, &tv) != 1) return false;
    int r = read(0, c, sizeof(char));
    if (r < 0) return false;
    return c;
}

#elif defined(_WIN32) || defined(WIN32)
#include <conio.h>
int termio_init()
{
    return EXIT_SUCCESS;
}

void termio_fin()
{
}

int termio_clear_screen()
{
    clrscr();
    return EXIT_SUCCESS;
}

bool termio_getch(char* c)
{
    if (!kbhit()) return false;
    int chr = getch();
    if (chr < 0) return false;
    *c = (char)chr;
    return true;
}

#else
#error unsupported os
#endif
