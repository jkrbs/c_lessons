#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int question_count = 10;

int score = 0;
bool should_exit = false;
bool got_answer;
int expected_answer;
pthread_mutex_t mutex;

void* check_answer(void* context)
{
    while (true) {
        bool exit = false;
        int res;
        char buffer[80];
        char* e = fgets(buffer, sizeof(buffer), stdin);
        pthread_mutex_lock(&mutex);
        exit = should_exit;
        if (!got_answer) { // to avoid double answering / scoring
            if (e != buffer || sscanf(buffer, "%i", &res) != 1) {
                printf("invalid input! ");
            }
            else if (!got_answer && res != expected_answer) {
                printf("incorrect! ");
            }
            else if (!got_answer) {
                printf("correct! ");
                score++;
            }
            got_answer = true;
        }
        exit = should_exit;
        pthread_mutex_unlock(&mutex);
        if (should_exit) break;
    }
    pthread_exit(NULL);
}

int main(void)
{
    time_t t;
    srand(time(&t)); // seed PRNG

    pthread_mutex_init(&mutex, NULL);
    pthread_t check_answer_thread;

    // lock before starting the thread to prevent answers before questions
    pthread_mutex_lock(&mutex);
    pthread_create(&check_answer_thread, NULL, check_answer, NULL);

    for (int i = 1; i <= question_count; i++) {
        int lhs = rand() % 10;
        int rhs = rand() % 10;
        expected_answer = lhs + rhs;
        got_answer = false;
        printf("Question %i: What is %i + %i?\n", i, lhs, rhs);
        if (i == question_count) should_exit = true;
        pthread_mutex_unlock(&mutex); // unlock so the answer thread can check

        sleep(3);

        pthread_mutex_lock(&mutex);
        // see if the answer thread got us sommething
        if (!got_answer) {
            printf("too slow! ");
            // to avoid a trailing incorrect etc. message :)
            if (i == question_count) expected_answer = -23457809;
        }
    }
    pthread_mutex_unlock(&mutex); // we still held the lock within the loop
    pthread_mutex_destroy(&mutex);

    // score
    if (score < question_count / 2) {
        printf("You only got %i points, better luck next time :)\n", score);
    }
    else if (score < question_count) {
        printf("You got %i points, not bad :)\n", score);
    }
    else {
        printf("All questions correct, incredible :)\n");
    }

    // wait for the other thread
    pthread_cancel(check_answer_thread); // to avoid waiting for input
    pthread_join(check_answer_thread, NULL);
    return 0;
}
