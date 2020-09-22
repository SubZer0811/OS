#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main (){

    int arr[] = {3, 1, 5, 2, 5, 2, 6, 4, 7, 9, 5, 3, 5}, n = sizeof(arr)/sizeof(int);

    printf("Original Array:        ");
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = vfork();

    if(pid == 0){

        for(int i=0; i<n; i++){
            for(int j=1; j<n-i; j++){
                if(arr[j] < arr[j-1]){
                    arr[j] += arr[j-1];
                    arr[j-1] = arr[j] - arr[j-1];
                    arr[j] -= arr[j-1];
                }
            }
        }

        printf("Ascending Array:       ");
        for(int i=0; i<n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        exit(0);
    }
    else{

        for(int i=0; i<n; i++){
            for(int j=1; j<n-i; j++){
                if(arr[j] > arr[j-1]){
                    arr[j] += arr[j-1];
                    arr[j-1] = arr[j] - arr[j-1];
                    arr[j] -= arr[j-1];
                }
            }
        }

        printf("Descending Array:      ");
        for(int i=0; i<n; i++)
            printf("%d ", arr[i]);
        printf("\n");

    }

    return 0;
}