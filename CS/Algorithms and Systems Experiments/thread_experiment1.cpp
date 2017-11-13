#include <thread>
#include <pthread.h>
#include <cstdio>
#include <unistd.h>

pthread_mutex_t Tim_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Tim = PTHREAD_COND_INITIALIZER;

void thread_fun(int my_var){

	pthread_mutex_lock(&Tim_lock);
		pthread_cond_wait(&Tim, &Tim_lock);
	pthread_mutex_unlock(&Tim_lock);
}

void* thread_fun2(void* x){

	pthread_mutex_lock(&Tim_lock);
		pthread_cond_wait(&Tim, &Tim_lock);
	pthread_mutex_unlock(&Tim_lock);
	printf("not waiting\n");
	return NULL;
}

int main(){
	// pthread_cond_init(&Tim,NULL);

	printf("Creating C++ thread\n");

	std::thread t1 (thread_fun, 9);
	t1.join();

	printf("Creating p_thread\n");

	pthread_t* t = (pthread_t *) malloc(sizeof(pthread_t));
	pthread_create(t, NULL, thread_fun2, NULL);		

	usleep(3000000);

	pthread_join(*t,NULL);

	return 0;
}