#include <stdio.h>

int main(){
int num;
printf("Enter Num: ");

scanf("%d",&num);

if(num%2 == 0){
	printf("Num is Even\n");
} else{
	printf("Num is Odd\n");
}
}
