/*
==================================================================================================
Name : 30.c
Author : Somesh Awasthi
Description : Write a program to create a shared memory.    
                a. write some data to the shared memory    
                b. attach with O_RDONLY and check whether you are able to overwrite.    
                c. detach the shared memory    
                d. remove the shared memory  
Date: 1st oct, 2023.
==================================================================================================
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(){
	key_t key = ftok(".",'e');
	printf("%d\n",key);
	int r = shmget(key, 1024, IPC_CREAT|0744);
	printf("%d\n",r);
	if(r<0){
		perror("Error while creating shared memory: ");
		return 0;
	}

	char* data = shmat(r, 0,0);
	
	printf("Enter a message: ");
    fgets(data,sizeof(data),stdin);
	
	
	int ret = shmctl(r, IPC_RMID, NULL);
	if(ret<0){
		printf("Shared memory couldn't be removed\n");
		return 0;
	}
	printf("Shared memory removed with return value: %d\n",ret);

}