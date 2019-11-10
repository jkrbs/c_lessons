#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 30
#define MAX_ENEMIES 10
#define EMPTY_FIELD ' '
#define DEFAULT_PLAYER_SYMBOL '@'
#define WALL_SYMBOL '#'

typedef struct player {
  int x_pos;
  int y_pos;
  char symbol;
} player;

typedef struct enemy {
  int x_pos;
  int y_pos;
  char symbol;
  int hp;
} enemy;

typedef struct gamestate {
  char env[MAP_WIDTH][MAP_HEIGHT];
  player player;
  int enemycount;
  enemy enemy[MAX_ENEMIES];
} gamestate;

char getch() {
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  return (buf);
}

void clearScreen() { printf("\e[1;1H\e[2J"); }

bool collision(gamestate *gamestate, int x, int y) {
  if (x == 0 || x == MAP_WIDTH || y == 0 || y == MAP_HEIGHT)
    return true;
  if (gamestate->env[x][y] != EMPTY_FIELD)
    return true;
  return false;
}
void draw(gamestate *gamestate) {
  clearScreen();

  gamestate->env[gamestate->player.x_pos][gamestate->player.y_pos] =
      gamestate->player.symbol;

  for (int e = 0; e < gamestate->enemycount; e++) {
    gamestate->env[gamestate->enemy[e].x_pos][gamestate->enemy[e].y_pos] =
        gamestate->enemy[e].symbol;
  }

  puts("Cancertales 0.1. Move With WASD, exit with Q");
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      putchar(gamestate->env[x][y]);
    }
    putchar('\n');
  }

  gamestate->env[gamestate->player.x_pos][gamestate->player.y_pos] =
      EMPTY_FIELD;

  for (int e = 0; e < gamestate->enemycount; e++) {
    gamestate->env[gamestate->enemy[e].x_pos][gamestate->enemy[e].y_pos] =
        EMPTY_FIELD;
  }
}

void initGame(gamestate *gamestate) {

  for (int y = 0; y < MAP_HEIGHT; y++) {

    for (int x = 0; x < MAP_WIDTH; x++) {
      gamestate->env[x][y] = ' ';
    }
  }
  for (int y = 0; y < MAP_HEIGHT; y++) {
    gamestate->env[0][y] = WALL_SYMBOL;
    gamestate->env[MAP_WIDTH - 1][y] = WALL_SYMBOL;
  }
  for (int x = 0; x < MAP_WIDTH; x++) {
    gamestate->env[x][0] = WALL_SYMBOL;
    gamestate->env[x][MAP_HEIGHT - 1] = WALL_SYMBOL;
  }
  gamestate->player.x_pos = MAP_WIDTH / 2;
  gamestate->player.y_pos = MAP_HEIGHT / 2;
  gamestate->player.symbol = DEFAULT_PLAYER_SYMBOL;
  gamestate->enemycount = 0;
}

int main() {
    gamestate gamestate;
    initGame(&gamestate);

    while (1) {
	draw(&gamestate);
	switch (getch()) {
	    case 'w':
	      if (!collision(&gamestate, gamestate.player.x_pos,
		     gamestate.player.y_pos - 1))
	    gamestate.player.y_pos -= 1;
	      break;
	    case 'a':
	      if (!collision(&gamestate, gamestate.player.x_pos - 1,
		     gamestate.player.y_pos))
	    gamestate.player.x_pos -= 1;
	      break;
	    case 's':
	      if (!collision(&gamestate, gamestate.player.x_pos,
		     gamestate.player.y_pos + 1))
	    gamestate.player.y_pos += 1;
	      break;
	    case 'd':
	      if (!collision(&gamestate, gamestate.player.x_pos + 1,
		     gamestate.player.y_pos))
		    gamestate.player.x_pos += 1;
	      break;
	    case 'q':
		    return 0;
	}
    }
}
