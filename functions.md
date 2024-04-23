memset: Preenche uma região de memória com um valor específico. Exemplo: memset(ptr, value, size);

printf: Imprime texto formatado na saída padrão (normalmente o console). Exemplo: printf("Hello, world!\n");

malloc: Aloca memória dinamicamente no heap. Exemplo: int *ptr = (int *)malloc(sizeof(int));

free: Libera a memória alocada dinamicamente. Exemplo: free(ptr);

write: Escreve dados em um descritor de arquivo. Exemplo: write(fd, buffer, size);

usleep: Pausa a execução do programa por um determinado número de microssegundos. Exemplo: usleep(1000000);

gettimeofday: Obtém o tempo atual em microssegundos desde a época. Exemplo: gettimeofday(&tv, NULL);

pthread_create: Cria uma nova thread. Exemplo: pthread_create(&tid, NULL, start_routine, arg);

pthread_detach: Indica que a thread criada deve ser desanexada após a conclusão. Exemplo: pthread_detach(tid);

pthread_join: Espera a thread especificada terminar sua execução. Exemplo: pthread_join(tid, NULL);

pthread_mutex_init: Inicializa um mutex para controle de concorrência. Exemplo: pthread_mutex_init(&mutex, NULL);

pthread_mutex_destroy: Destroi um mutex previamente inicializado. Exemplo: pthread_mutex_destroy(&mutex);

pthread_mutex_lock: Bloqueia um mutex para acesso exclusivo. Exemplo: pthread_mutex_lock(&mutex);

pthread_mutex_unlock: Libera um mutex previamente bloqueado. Exemplo: pthread_mutex_unlock(&mutex);

Quando detached, recursos de uma thread são liberados imediatamente
em sua conclusão e pthread_join não pode ser usado para sincronização
(espera pelo fim).
• pthread_detach() permite ajustar estado para detached em tempo de
execução.