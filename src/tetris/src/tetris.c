#include<stdio.h>
#include "termio.h"
#include <stdlib.h>
#include <unistd.h>
#define BOARD_WIDTH  10
#define BOARD_HEIGHT 24 


enum block_type {
    BLOCK_L1, BLOCK_L2, BLOCK_Z1, BLOCK_Z2, BLOCK_I, BLOCK_T, BLOCK_Q, BLOCK_COUNT, NONE
};


//TODO add missing blocks
char* block_symbols[BLOCK_COUNT][4][4] = {
[BLOCK_I] = {{"    ", "    ", "IIII", "    "}, 
             {"  I ", "  I ", "  I ", "  I "}, 
             {"    ", "    ", "IIII", "    "}, 
             {"  I ", "  I ", "  I ", "  I "}},
[BLOCK_L1] = {"IIII", "    "},
[BLOCK_L2] = {"IIII", "    "},
[BLOCK_Z1] = {"IIII", "    "},
[BLOCK_Z2] = {"IIII", "    "},
[BLOCK_T] = {"IIII", "    "},
[BLOCK_Q] = {"IIII", "    "}
};


typedef struct block {
        enum block_type kind;
        int rotation;
        int x, y;
} block;

struct board {
    char grid[BOARD_WIDTH][BOARD_HEIGHT];
};

struct gamestate {
    struct board board;
    //TODO Block quene
    block cur_block;
} gamestate;

//returns true on collision
bool char_insert(int x, int y, char ic, bool del) {
    if(x<0 || x>=BOARD_WIDTH || y>= BOARD_HEIGHT || y < 0) {
        if(del) return false;
        return ic != ' ';
    }

    if(!del && gamestate.board.grid[x][y] != ' ') return true;
    gamestate.board.grid[x][y] = del?' ':ic;
    return false;
}

bool block_insert(bool del) {
    bool collission = false;
    int x = gamestate.cur_block.x;
    int y = gamestate.cur_block.y;
    
    enum block_type kind = gamestate.cur_block.kind;


    for(int i = 0; i<4; i++) {
        for(int j =0; j<4; j++) {
            collission = char_insert(x+i, y+j, block_symbols[BLOCK_I][gamestate.cur_block.rotation][j][i], del);
            if(collission) return collission;
        }
    }
    return false;
}


void render_board() {
    termio_clear_screen();

    for(int y = 0; y < BOARD_HEIGHT; y++) {
        for(int x = 0; x < BOARD_WIDTH; x++) {
            putchar(gamestate.board.grid[x][y]);
        }
        putchar('\n');
    }
    block_insert(true);
}

void move(int x, int y) {
    gamestate.cur_block.x += x;
    gamestate.cur_block.y += y;
    if(block_insert(false)) {
        block_insert(true);
        gamestate.cur_block.x -= x;
        gamestate.cur_block.y -= y;
        block_insert(false);
        gamestate.cur_block.kind = NONE;
    }
}


void gametick() {
    move(0,1);    
    if(gamestate.cur_block.kind == NONE) {
        gamestate.cur_block.kind=rand() % BLOCK_COUNT;

        gamestate.cur_block.y = 0;
        gamestate.cur_block.x = BOARD_WIDTH/2;

        gamestate.cur_block.rotation = rand() % 4;
    }


    char input;

    while(termio_getch(&input)) {
        switch(input) {
            case 'a':
                if(gamestate.cur_block.x == 0) break;
                gamestate.cur_block.x--;//TODO collission check
                break;
            
            case 's':
                if(gamestate.cur_block.y == BOARD_HEIGHT-1) break;
                gamestate.cur_block.y++; //TODO collission check
                break;

            case 'd':
                if(gamestate.cur_block.x == BOARD_WIDTH-1) break;
                gamestate.cur_block.x++;//TODO collission check
                break;

            case 'q':
                gamestate.cur_block.rotation = (gamestate.cur_block.rotation +1) % 4;
                break;

            case 'e':
                gamestate.cur_block.rotation = (gamestate.cur_block.rotation +3) % 4;
                break;
        }
    }

}


int main() {

    termio_init();

    while (true)
    {
        gametick();
        render_board();
        usleep(50000);
    }

    termio_fin();
    
}
