#include <stdio.h>
#include <pthread.h>

int arr[10] = {1,2,3,4,5,6,7,8,9,10};

struct ThreadData {
    int first;
    int last;
    int result;
};

void* calculateSum(void* ThData) {
    struct ThreadData* data = (struct ThreadData*)ThData;
    data->result = 0;

    for(int i = data->first; i <= data->last; i++) {
        data->result += arr[i];
    }

    pthread_exit(NULL);
}

int main() {
	pthread_t t1, t2;

    	struct ThreadData data1 = {0, 4, 0};
    	struct ThreadData data2 = {5, 9, 0};

	pthread_create(&t1, NULL, calculateSum, &data1);
    	pthread_create(&t2, NULL, calculateSum, &data2);
    	pthread_join(t1, NULL);
    	pthread_join(t2, NULL);

	int total = data1.result + data2.result;

    	printf("Thread 1: %d\n", data1.result);
    	printf("Thread 2: %d\n", data2.result);
    	printf("Total Sum: %d\n", total);

   	return 0;
}
