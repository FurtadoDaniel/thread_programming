#include <semaphore.h>
#include <pthread.h>

struct elf {
	pthread_t thread;
	struct elf *next;
};

int elves_counter = 0;
int reindeer_counter = 0;
sem_t santa_clock;
sem_t elves_counter_sem;
sem_t reindeer_counter_sem;
sem_t sleigh_sem;
sem_t elves_wait;

void hireElves (struct elf *first) {}	

void getHitched () {}

void getHelp () {}

void helpElves () {}

void prepareSleigh() {}

void sleep () {
	for (;;) {
		sem_wait (&santa_clock);
		sem_wait (&reindeer_counter_sem);
		if (reindeer_counter == 9) {
			prepareSleigh ();
			sem_post (&sleigh_sem);
		}
		sem_post (&reindeer_counter_sem);
		sem_wait (&elves_counter_sem);
		if (elves_counter == 3) {
			helpElves ();
		}
		sem_post (&elves_counter_sem);
	}
}

void goVacation () {
	//routine
	sem_wait (&reindeer_counter_sem);
	reindeer_counter++;
	if (reindeer_counter == 9) {
		sem_post (&santa_clock);
		sem_wait (&sleigh_sem);
		getHitched ();
		reindeer_counter = 0;
	}
}

void work () {
	//routine
	sem_wait (&elves_wait);
	sem_wait (&elves_counter_sem);
	elves_counter++;
	if (elves_counter == 3) {
		sem_post (&santa_clock);
	} else { 
		sem_post (&elves_wait);
	}
	sem_post (&elves_counter_sem);
	getHelp ();

	sem_wait (&elves_counter_sem);
	elves_counter--;
	if (elves_counter == 0) {
		sem_post (&elves_wait);
	}
	sem_post (&elves_counter_sem);
}

int main () {
	
	pthread_t santa;
	pthread_t reindeer [9];
	struct elf *elves = NULL;

	sem_init (&santa_clock, 0, -1);
	sem_init (&elves_counter_sem, 0, 0);
	sem_init (&elves_counter_sem, 0, 0);
	sem_init (&sleigh_sem, 0, -1);
	sem_init (&elves_wait, 0, 0);

	pthread_create (&santa, NULL, &sleep, NULL);
	for (int i = 0; i<9; i++) {
		pthread_create (&reindeer[i], NULL, &goVacation, NULL);
	}
	hireElves (elves);
	for (struct elf *aux = elves; aux != NULL; aux = aux->next) {
		pthread_create (&aux->thread, NULL, &work, NULL);
	}
	pthread_join (&santa, NULL);
}