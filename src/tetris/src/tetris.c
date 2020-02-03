#include<stdio.h>
#include "termio.h"
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20 


enum block_type {
    BLOCK_L1, BLOCK_L2, BLOCK_Z1, BLOCK_Z2, BLOCK_I, BLOCK_T, BLOCK_Q, BLOCK_COUNT, BLOCK_NONE
};

typedef enum collision_type {COLLISION_NONE, COLLSION_BLOCK, COLLISION_BOTTOM, COLLISION_BORDER
} collision_type;


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
    int score;
} gamestate;

//returns true on collision
collision_type char_insert(int xoffset, int yoffset, bool del) {
    int x = gamestate.cur_block.x + xoffset;
    int y = gamestate.cur_block.y + yoffset;
    char bc = block_symbols[gamestate.cur_block.kind][gamestate.cur_block.rotation][yoffset][xoffset];

    if(x<0 || x>=BOARD_WIDTH || y < 0) {
        return bc != ' ' ? COLLISION_BORDER : COLLISION_NONE;
    }

    if( y>= BOARD_HEIGHT) {
        return bc != ' ' ? COLLISION_BOTTOM : COLLISION_NONE;
    }
    
    if(gamestate.board[x][y] == ' '){
        if(!del) gamestate.board[x][y] = bc;
        return COLLISION_NONE;
    }
    if(del){
        if(bc != ' ') gamestate.board[x][y] = ' ';
        return COLLISION_NONE;
    }
    return bc != ' ' ? COLLSION_BLOCK : COLLISION_NONE;
}

collision_type block_insert(bool del) {
 
    enum block_type kind = gamestate.cur_block.kind;

    for(int i = 0; i<4; i++) {
        for(int j =0; j<4; j++) {
            collision_type ct = char_insert(i, j, del);
            if(ct){
                assert(!del);
                for(int k = 0; k < i; k++){
                    for(int l = 0; l <  4; l++) char_insert(k, l, true);
                }
                for(int l = 0; l < j; l++) char_insert(i, l, true);
                return ct;
            }
        }
    }
    return COLLISION_NONE;
}

void move(int x, int y, int rot) {
    block_insert(true);
    int rot_prev = gamestate.cur_block.rotation;
    gamestate.cur_block.x += x;
    gamestate.cur_block.y += y;
    gamestate.cur_block.rotation = (gamestate.cur_block.rotation + 4 + rot) % 4;
    
    collision_type ct =block_insert(false);
    
    if(ct) {
        gamestate.cur_block.x -= x;
        gamestate.cur_block.y -= y;
        gamestate.cur_block.rotation = rot_prev;
        block_insert(false);
        if(ct == COLLSION_BLOCK || ct == COLLISION_BOTTOM) {
            gamestate.cur_block.kind = BLOCK_NONE;
        }
    }
}

void render_board() {
    termio_clear_screen();
    for(int i = 0; i< BOARD_WIDTH+2; i++) {
        putchar('@');
    }
    printf("    score: %d", gamestate.score);
    putchar('\n');

    for(int y = 0; y < BOARD_HEIGHT; y++) {
        putchar('@');
        for(int x = 0; x < BOARD_WIDTH; x++) {
            putchar(gamestate.board[x][y]);
        }
        puts("@");
    }

    for(int i = 0; i< BOARD_WIDTH+2; i++) {
        putchar('@');
    }
    putchar('\n');
}



void init_board(){
    for(int x = 0; x<BOARD_WIDTH; x++){
        for(int y = 0; y<BOARD_HEIGHT; y++){
            gamestate.board[x][y] = ' ';
        }
    }
}


void gametick() {   
    char input;

    while(true){
        if(gamestate.cur_block.kind == BLOCK_NONE) {

            for(int y = 0; y < BOARD_HEIGHT; y++) {
                bool line_full = true;
                for(int x = 0; x < BOARD_WIDTH; x++) {
                    if(gamestate.board[x][y] == ' ') {
                        line_full = false;
                        break;
                    }
                }
                if(line_full) {
                    int line_y = y;
                    for(int x = 0; x < BOARD_WIDTH; x++) {
                        //memmove(&gamestate.board[x][y], &gamestate.board[x][y+1], sizeof(char)*y);
                        for(int y = line_y; y >= 1; y--) {
                            gamestate.board[x][y] = gamestate.board[x][y-1];
                        }
                    }
                    for(int x = 0; x< BOARD_WIDTH; x++) {
                        gamestate.board[x][0] = ' ';
                    }
                    gamestate.score += 100;
                }
            }


            gamestate.cur_block.kind= rand() % BLOCK_COUNT;
            gamestate.cur_block.kind = BLOCK_I; //debug
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
        move(0, 1, 0); 
        for(int i = 0; i<10;i++){
            gametick();
            render_board();
            usleep(30000);
        }
       
    }

    termio_fin();
    
}
