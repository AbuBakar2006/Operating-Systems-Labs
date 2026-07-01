#include <stdio.h>

int main(){

int num1,num2,num3;
printf("Enter 3 Numbers: ");
scanf("%d %d %d",&num1,&num2,&num3);

int lar = num1;

if(num2>lar){
lar =num2;
}

if(num3>lar){
lar = num3;
}

printf("Largest Number is: %d",lar);
}
