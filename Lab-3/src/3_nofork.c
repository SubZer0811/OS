#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main (){

	int n=10000000;

	int itr = 0;
	int i=0, num=0, sum=0;

	for(i=0; i<n; i=i+1){
		printf("%d\n", i);
		sum = 0;
		num = i;
		while (num>0)
		{
			int digit = num%10;
			sum += digit*digit*digit;
			num = num/10;	
		}
		if(sum == i)
			printf("%d\n", i);
	}

	return 0;
}