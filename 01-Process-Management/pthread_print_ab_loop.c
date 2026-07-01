#include <stdio.h>
#include <pthread.h>
void* printA(void* arg) {
while(1) {
printf("A");
}
return NULL;
}
void* printB(void* arg) {
while(1) {
printf("B");
}
return NULL;
}
int main() {
pthread_t t1, t2;
pthread_create(&t1, NULL, printA, NULL);
pthread_create(&t2, NULL, printB, NULL);
pthread_join(t1, NULL);
pthread_join(t2, NULL);

return 0;
}
