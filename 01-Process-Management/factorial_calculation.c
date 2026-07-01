#include <stdio.h>

int main(){
	int num=0;
	printf("Enter A Number: ");
	scanf("%d",&num);

	int fact=1;
	for(int i=1;i<=num;i++){
		fact = fact*i;
	}

	printf("Factorial of %d is %d\n",num,fact);
	return 0;
}
