#include<stdio.h>
#include "termio.h"
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#define BOARD_WIDTH  30
#define BOARD_HEIGHT 24 


enum block_type {
    BLOCK_L1, BLOCK_L2, BLOCK_Z1, BLOCK_Z2, BLOCK_I, BLOCK_T, BLOCK_Q, BLOCK_COUNT, BLOCK_NONE
};


//TODO add missing blocks
char* block_symbols[BLOCK_COUNT][4][4] = {
    [BLOCK_L1] = {
        {"#   ", "### ", "    ", "    "},
        {" ## ", " #  ", " #  ", "    "},
        {"    ", "### ", "  # ", "    "},
        {" #  ", " #  ", "##  ", "    "},
    },
    [BLOCK_L2] = {
        {"  # ", "### ", "    ", "    "},
        {" #  ", " #  ", " ## ", "    "},
        {"    ", "### ", "#   ", "    "},
        {"##  ", " #  ", " #  ", "    "},
    },
    [BLOCK_Z1] = {
        {" ## ", "##  ", "    ", "    "},
        {" #  ", " ## ", "  # ", "    "},
        {"    ", " ## ", "##  ", "    "},
        {"#   ", "##  ", " #  ", "    "},
    },
    [BLOCK_Z2] = {
        {"##  ", " ## ", "    ", "    "},
        {"  # ", " ## ", " #  ", "    "},
        {"    ", "##  ", " ## ", "    "},
        {" #  ", "##  ", "#   ", "    "},
    },
    [BLOCK_I] = {
        {"    ", "####", "    ", "    "},
        {" #  ", " #  ", " #  ", " #  "},
        {"    ", "####", "    ", "    "},
        {"  # ", "  # ", "  # ", "  # "},
    },
    [BLOCK_T] = {
        {" #  ", "### ", "    ", "    "},
        {" #  ", " ## ", " #  ", "    "},
        {"    ", "### ", " #  ", "    "},
        {" #  ", "##  ", " #  ", "    "},
    },
    [BLOCK_Q] = {
        {"    ", " ## ", " ## ", "    "},
        {"    ", " ## ", " ## ", "    "},
        {"    ", " ## ", " ## ", "    "},
        {"    ", " ## ", " ## ", "    "},
    },
};


typedef struct block {
    enum block_type kind;
    int rotation;
    int x, y;
} block;

struct gamestate {
    char board[BOARD_WIDTH][BOARD_HEIGHT];
    //TODO Block quene
    block cur_block;
} gamestate;

//returns true on collision
bool char_insert(int xoffset, int yoffset, bool del) {
    int x = gamestate.cur_block.x + xoffset;
    int y = gamestate.cur_block.y + yoffset;
    char bc = block_symbols[gamestate.cur_block.kind][gamestate.cur_block.rotation][yoffset][xoffset];

    if(x<0 || x>=BOARD_WIDTH || y>= BOARD_HEIGHT || y < 0) {
        return bc != ' ';
    }

    if(gamestate.board[x][y] == ' '){
        if(!del) gamestate.board[x][y] = bc;
        return false;
    }
    if(del){
        if(bc != ' ') gamestate.board[x][y] = ' ';
        return false;
    }
    return bc != ' ';
}

bool block_insert(bool del) {
 
    enum block_type kind = gamestate.cur_block.kind;

    for(int i = 0; i<4; i++) {
        for(int j =0; j<4; j++) {
            if(char_insert(i, j, del)){
                assert(!del);
                for(int k = 0; k < i; k++){
                    for(int l = 0; l <  4; l++) char_insert(k, l, true);
                }
                for(int l = 0; l < j; l++) char_insert(i, l, true);
                return true;
            }
        }
    }
    return false;
}

void move(int x, int y, int rot) {
    block_insert(true);
    int rot_prev = gamestate.cur_block.rotation;
    gamestate.cur_block.x += x;
    gamestate.cur_block.y += y;
    gamestate.cur_block.rotation = (gamestate.cur_block.rotation + 4 + rot) % 4;
    if(block_insert(false)) {
        gamestate.cur_block.x -= x;
        gamestate.cur_block.y -= y;
        gamestate.cur_block.rotation = rot_prev;
        block_insert(false);
        gamestate.cur_block.kind = BLOCK_NONE;
    }
}

void render_board() {
    termio_clear_screen();
    printf("x: %i, y: %i, rot: %i, kind: %i\n",
        gamestate.cur_block.x,gamestate.cur_block.y,gamestate.cur_block.rotation,gamestate.cur_block.kind
    );
    for(int y = 0; y < BOARD_HEIGHT; y++) {
        for(int x = 0; x < BOARD_WIDTH; x++) {
            putchar(gamestate.board[x][y]);
        }
        putchar('\n');
    }
}



void init_board(){
    for(int x = 0; x<BOARD_WIDTH; x++){
        for(int y = 0; y<BOARD_HEIGHT; y++){
            gamestate.board[x][y] = ' ';
        }
    }
}


void gametick() {
    move(0, 1, 0);    

    char input;

    while(true){
        if(gamestate.cur_block.kind == BLOCK_NONE) {
            gamestate.cur_block.kind= rand() % BLOCK_COUNT;

            gamestate.cur_block.y = 0;
            gamestate.cur_block.x = BOARD_WIDTH/2;

            gamestate.cur_block.rotation = rand() % 4;
            block_insert(false);
        }
        if(!termio_getch(&input))break;
        switch(input) {
            case 'a':
                move(-1, 0, 0);
                break;
            
            case 's':
                move(0, 1, 0);
                break;

            case 'd':
                move(1, 0, 0);
                break;

            case 'q':
                 move(0, 0, 1);
                break;

            case 'e':
                 move(0, 0, -1);
                break;
        } 
    }

}


int main() {
    
    termio_init();
    init_board();
    while (true)
    {
        gametick();
        render_board();
        usleep(500000);
    }

    termio_fin();
    
}
