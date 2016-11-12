#include <pthread.h>
#include <stdio.h>

//structure for a list of threads
struct list {
	pthread_t thread;
	struct lista *next;
};

void* saymyname(int * name) {

    pthread_t id = pthread_self();//get the ID of a thread
    printf("\nThread%d reporting for duty, my PID its %u", name, id);
    
    return NULL;
}

int main() {

    int i = 0;
    struct list *first = NULL;
    struct list *aux= NULL;

    printf("Quantas thread deseja criar: ");
    scanf("%d", &i);

    //create a thread and pu in the list
    for (int j=0; j<i; j++) {
    	aux = (struct list *) malloc (sizeof (struct list));
        pthread_create(&(aux->thread), NULL, &saymyname, j);
        aux->next = first;
        first = aux;
    }

    //run the list taking back the thread and removing from the list
    while(first != NULL) {
    	pthread_join( first->thread, NULL);
    	aux=first;
    	first=first->next;
    	free(aux);
    }
    
    printf("\n");
    return 0;
}