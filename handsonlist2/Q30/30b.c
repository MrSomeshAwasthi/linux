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
#include <sys/shm.h>
#include <sys/ipc.h>

int main(){
        key_t key = ftok(".",'e');
        printf("%d\n",key);
        int r = shmget(key, 1024, IPC_CREAT|0744);
        printf("%d\n",r);
        if(r<0){
                perror("Error while creating shared memory: ");
                return 0;
        }

        char* data = shmat(r, 0, SHM_RDONLY);
        //printf("%d\n",ret);

        printf("Data from shared memory: %s\n",data);

	int ret = shmdt(data);
	if(ret<0){
		perror("Shared Memory couldn't be detached: ");
		return 0;
	}

	printf("Shared memory detached with return value: %d",ret);

	printf("Data from shared memory: %s\n",data);

}