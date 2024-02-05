#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[NUM_PHILOSOPHERS];
pthread_mutex_t m;
pthread_mutex_t s[NUM_PHILOSOPHERS];

void* philosopher(void* arg);
void grab_forks(int i);
void put_away_forks(int i);
void test(int i);

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];

    pthread_mutex_init(&m, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&s[i], NULL);
        pthread_mutex_lock(&s[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void*)i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&m);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&s[i]);
    }

    return 0;
}

void* philosopher(void* arg) {
    int i = (int)arg;
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", i);
        usleep(1000000); // Simulate thinking time

        grab_forks(i);

        // Eating
        printf("Philosopher %d is eating.\n", i);
        usleep(2000000); // Simulate eating time

        put_away_forks(i);
    }
    return NULL;
}

void grab_forks(int i) {
    pthread_mutex_lock(&m);
    state[i] = HUNGRY;
    test(i);
    pthread_mutex_unlock(&m);
    pthread_mutex_lock(&s[i]);
}

void put_away_forks(int i) {
    pthread_mutex_lock(&m);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&m);
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        pthread_mutex_unlock(&s[i]);
    }
}
