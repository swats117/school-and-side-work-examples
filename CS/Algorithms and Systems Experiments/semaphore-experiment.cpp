#include <mutex>
#include <pthread.h>

class v_semaphore{
private:
	pthread_mutex_t mux;
	int ammount;
	pthread_cond_t full_buffer, empty_buffer;
	int max_allowable;
public:
	v_semaphore(int max_allowable): ammount(0), max_allowable(max_allowable){}
	// ~v_semaphore();
	void post(int increase){
		pthread_mutex_lock(&mux);
			while(ammount + increase > max_allowable)
				pthread_cond_wait(&full_buffer, &mux);
			ammount += increase;
			pthread_cond_broadcast(&empty_buffer);
		pthread_mutex_unlock(&mux);
	}
	void wait(int decrease){
		pthread_mutex_lock(&mux);
			ammount -= decrease;
			while(ammount == 0)
				pthread_cond_wait(&empty_buffer, &mux);
			pthread_cond_broadcast(&full_buffer);
		pthread_mutex_unlock(&mux);
	}
	int get_ammount(){
		return ammount;
	}
};

#include <cstdio>

int main(){

	int some_number;
	v_semaphore sem(10);

	sem.post(5);
	printf("ammount in sem: %d\n",sem.get_ammount());
	sem.wait(3);
	printf("ammount in sem: %d\n",sem.get_ammount());

	return 0;
}