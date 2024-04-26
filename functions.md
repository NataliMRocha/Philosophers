memset: Preenche uma região de memória com um valor específico. Exemplo: memset(ptr, value, size);

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
em sua conclusão e pthread_join não pode ser usado para sincronização (espera pelo fim).
• pthread_detach() permite ajustar estado para detached em tempo de execução.

# Threads

Cada processo é composto por 1 ou mais threads.
Threads ajudam a criar programas mais rápidos, se a gente splita a thread de execução (a main), podemos encaixar ela em todos os núcleos disponíveis.

# Concorrência
Refere-se à capacidade de diferentes partes de um programa serem executadas em sobreposição no tempo. Isso não significa necessariamente que as partes do programa estão sendo executadas ao mesmo tempo, mas sim que parecem estar progredindo simultaneamente para o usuário. A concorrência é frequentemente usada para lidar com múltiplas tarefas de forma eficiente, especialmente em sistemas onde a comunicação e a coordenação entre as tarefas são essenciais.

* ex:uma thread que tem um sleep durante a execução. Quando uma thread chama a função sleep, ela entra em um estado de dormência, o que significa que ela libera o processador para que outras threads possam ser executadas. Durante esse período de dormência, o sistema operacional pode escolher executar outra thread que esteja pronta para ser executada.

# Paralelismo
Envolve a execução simultânea real de múltiplas tarefas em diferentes unidades de processamento. Em um sistema multi-core, por exemplo, várias instruções podem ser executadas ao mesmo tempo, aproveitando os núcleos de processamento independentes. O paralelismo geralmente é utilizado para acelerar a execução de programas, dividindo as tarefas entre os recursos de processamento disponíveis.

* IMPORTANTE: Em sistemas de 1 único núcleo, embora apenas uma thread possa ser executada em um determinado momento, a rápida alternância entre as threads dá a impressão de que várias operações estão ocorrendo simultaneamente. Isso é chamado de paralelismo a nível de tarefa. Além disso, há também o conceito de paralelismo de instrução, onde uma única CPU executa múltiplas instruções de forma paralela dentro de um pipeline de execução. Isso é uma forma de paralelismo em nível de instrução, onde diferentes estágios de execução de uma instrução são sobrepostos para melhorar o desempenho.

Mutex (MUTualEXclusion) encapsula um pedaço de código para que possamos travar recursos para cada thread individualmente. Fazemos isso para lidar com a disputa de dados e evitar que as variáveis se atropelem.
Race conditions ocorrem dentro dos processos e não entre processos.
Só a thread que trancou o trecho pode destrancá-lo
ex: 

void update_nb(void *data)
{
	t_data *info = (t_data)data;

	//lock
	pthread_mutex_lock(info->mutex);
	data->i += 1;
	//unlock
	pthread_mutex_unlock(info->mutex);
	return (NULL);
}

onde info->mutex = pthread_mutex_t mutex

FLAG -fsanitize=thread: Detecta problemas de concorrência.

When you call pthread_join(tid, &result), the calling thread will be blocked until the thread with ID tid completes its execution.

Recuperando stack memory: cada thread tem sua própria stack memory, que é usada para armazenar variáveis locais, informações de chamada de função e muito mais. Quando a thread terminar, essa memória poderá ser recuperada, mas o sistema não fará isso até que outra thread reconheça o encerramento dessa thread. pthread_join() cumpre essa função.
Liberando recursos internos: A biblioteca pthreads pode alocar outros recursos internos para gerenciamento de threads. Chamar pthread_join() garante que esses recursos também sejam liberados.