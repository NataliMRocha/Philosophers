/* pthread_t *thread: É um ponteiro para uma variável onde o ID da thread criada será armazenado.
const pthread_attr_t *attr: É um ponteiro para uma estrutura de atributos da thread. Você pode passar NULL para usar os atributos padrão.
void *(*start_routine) (void *): É um ponteiro para a função que será executada pela nova thread.
void *arg: É um ponteiro para os argumentos que serão passados para a função start_routine.
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
 */
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    int *value = (int *)arg;
    printf("Thread created. Value passed: %d\n", *value);
    return NULL;
}

int main() {
    pthread_t tid;
    int value[2] = {42, 5};
    int i = 0;

    while (i < 7)
    {
        
        if(i % 2 == 0)
            pthread_create(&tid, NULL, thread_function, &value[0]);
        else
            pthread_create(&tid, NULL, thread_function, &value[1]);
                //perror("pthread_create");
        i++;
    }

    pthread_join(tid, NULL); // Espera a thread criada terminar

    return 0;
}