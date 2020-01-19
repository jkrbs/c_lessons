#pragma once

#include <stdbool.h>

int termio_init(); // non 0 indicates error
void termio_fin();

int termio_clear_screen(); // non 0 indicates error
bool termio_getch(char* c); // true when we got a char, false otherwise
