#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// just some constants
// if this is new to you, think of it as "int FOOO = 17;"
#define MAP_WIDTH 80
#define MAP_HEIGHT 30
#define MAX_ENEMIES 10
#define EMPTY_FIELD ' '
#define PLAYER_SYMBOL '@'
#define WALL_SYMBOL '#'

// the x and y positions start in the upper left corner with (x = 0, y = 0)
typedef struct player {
    int x_pos;
    int y_pos;
    char symbol;
} player;

enum enemy_type {
    EMEPY_TYPE_SPIDER, // unused and just for demonstration purposes,
    EMEPY_TYPE_GOBLIN, // you get creative here
    // ... well as creative as a single ascii character can get ;)
};
typedef struct enemy {
    // ccan be used to differentiate between different enemies that might
    // behave differently
    enum enemy_type type;
    int x_pos;
    int y_pos;
    char symbol;
    int hp;
} enemy;

typedef struct gamestate {
    // used for the output
    char env[MAP_WIDTH][MAP_HEIGHT];
    player player;
    // the number of slots filled in the enemy array. must be smaller than
    // MAX_ENEMIES
    int enemy_count;
    enemy enemies[MAX_ENEMIES];
} gamestate;

// clears the terminal screen by sending a magic number to the terminal
// that tells it to clear itself
void clearScreen()
{
    printf("\e[1;1H\e[2J");
}

// called when something goes horribly wrong, prints a status message and exits
void panic(char* msg)
{
    clearScreen();
    perror(msg);
    exit(EXIT_FAILURE);
}

// get a single input char reliably even for control character.
// You really don't need to understand this code right now,
// it's some fairly low level operating system stuff that probably
// doesn't work or even compile for windows cmd. We tested on msys2 though :).
char getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) panic("tcsetattr failed");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) panic("tcsetattr ICANON failed");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) panic("tcsetattr ~ICANON failed");
    return (buf);
}

// check if a certain game field is occupied
bool is_occupied(gamestate* gamestate, int x, int y)
{
    if (x == 0 || x == MAP_WIDTH || y == 0 || y == MAP_HEIGHT) return true;
    if (gamestate->env[x][y] != EMPTY_FIELD) return true;
    return false;
}

void draw(gamestate* gamestate)
{
    clearScreen();

    // place all dynamic entities in env
    gamestate->env[gamestate->player.x_pos][gamestate->player.y_pos] =
        gamestate->player.symbol;

    for (int e = 0; e < gamestate->enemy_count; e++) {
        gamestate
            ->env[gamestate->enemies[e].x_pos][gamestate->enemies[e].y_pos] =
            gamestate->enemies[e].symbol;
    }

    // draw env
    puts("Cancertales 0.1. Move With WASD or the Arrow keys, exit with Q");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            putchar(gamestate->env[x][y]);
        }
        putchar('\n');
    }

    // remove all dynamic entities from env
    gamestate->env[gamestate->player.x_pos][gamestate->player.y_pos] =
        EMPTY_FIELD;

    for (int e = 0; e < gamestate->enemy_count; e++) {
        gamestate
            ->env[gamestate->enemies[e].x_pos][gamestate->enemies[e].y_pos] =
            EMPTY_FIELD;
    }
}

// create an empty game with walls on the outsides
void initGame(gamestate* gamestate)
{
    // clear everything
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            gamestate->env[x][y] = EMPTY_FIELD;
        }
    }
    // place walls
    for (int y = 0; y < MAP_HEIGHT; y++) {
        gamestate->env[0][y] = WALL_SYMBOL;
        gamestate->env[MAP_WIDTH - 1][y] = WALL_SYMBOL;
    }
    for (int x = 0; x < MAP_WIDTH; x++) {
        gamestate->env[x][0] = WALL_SYMBOL;
        gamestate->env[x][MAP_HEIGHT - 1] = WALL_SYMBOL;
    }

    // initialize the player in the middle
    gamestate->player.symbol = PLAYER_SYMBOL;
    gamestate->player.x_pos = MAP_WIDTH / 2;
    gamestate->player.y_pos = MAP_HEIGHT / 2;

    // we have no entities yet
    gamestate->enemy_count = 0;
}

int main()
{
    gamestate gamestate;
    initGame(&gamestate);
    while (1) {
        draw(&gamestate);
        int x = getch();
        if (x == 0x1b) {
            x = (x << 8) | getch();
            if (x == 0x1b5b) x = (x << 8) | getch();
        }
        bool action = true;
        int mov_x = 0;
        int mov_y = 0;
        switch (x) {
            case 'w':
            case 'W':
            // up arrow
            case 0x1B5B41: {
                mov_y = -1;
            } break;

            case 'a':
            case 'A':
            // left arrow
            case 0x1B5B44: {
                mov_x = -1;
            } break;

            case 's':
            case 'S':
            // down arrow
            case 0x1B5B42: {
                mov_y = 1;
            } break;

            case 'd':
            case 'D':
            // right arrow
            case 0x1B5B43: {
                mov_x = 1;
            } break;

            case 'q':
            case 'Q': {
                return 0;
            }

            default: {
                action = false;
            } break;
        }
        if (action) {
            if (!is_occupied(
                    &gamestate, gamestate.player.x_pos + mov_x,
                    gamestate.player.y_pos + mov_y)) {
                gamestate.player.x_pos += mov_x;
                gamestate.player.y_pos += mov_y;
            }
        }
    }
}
