#include <semaphore.h>

struct elve {
	pthread_t thread;
	struct lista *next;
};

int elves_counter = 0;
int reindeer_counter = 0;
sem_t santa_clock;
sem_t elves_counter_sem;
sem_t reindeer_counter_sem;

void hire_elves (struct elve *first);

void sleep () {
	while (true) {
		sem_wait (&santa_clock);
		sem_wait (&reindeer_counter_sem);
		if (reindeer_counter == 9) {

		}
		sem_post (&reindeer_counter_sem);
		sem_wait (&elves_counter_sem);
		if (elves_counter == 3) {

		}
		sem_post (&elves_counter_sem);
	}
}

int main () {
	
	pthread_t Santa;
	pthread_t [9] Reindeer;
	struct elve *elves = NULL;

	sem_init(&santa_clock, 0, -1);
	sem_init(&elves_counter_sem, 0, 0);
	sem_init(&elves_counter_sem, 0, 0);

	pthread_create(&Santa, NULL, &sleep, NULL);
	for (int i = 0; i<9; i++) pthread_create(&Reindeer[i], NULL, &GoVacation, NULL);
	hire_elves(elves);
	for (struct elve *aux = elves; aux != NULL; aux = aux->next) pthread_create(&aux->thread, NULL, &work, NULL);
}