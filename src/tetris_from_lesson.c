#include<pthread.h>
#include<stdio.h>

#define BOARD_WIDTH  10
#define BOARD_HEIGHT 24 


enum block_type {
    BLOCK_L1, BLOCK_L2, BLOCK_Z1, BLOCK_Z2, BLOCK_I, BLOCK_T, BLOCK_Q 
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
    pthread_mutex_t mut;
    struct board board;
    //TODO Block quene
    block cur_block;
} gamestate;

void* handle_user_input(void* ignore) {
    while(1) {
    

    }

}

void render_board() {
    for(int x = 0; x < BOARD_WIDTH; x++) {
        for(int y = 0; y < BOARD_HEIGHT; y++) {
            putchar(gamestate.board.grid[x][y]);
        }
    }
}

int main() {
    pthread_t user_input_thread;

    pthread_create(&user_input_thread, NULL, handle_user_input, NULL);
}