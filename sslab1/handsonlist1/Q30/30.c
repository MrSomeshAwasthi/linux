/*
========================================================================================
Name : 30.c
Author : Somesh Awasthi
Description :Write a program to run a script at a specific time using a Daemon process.
Date: 28th Aug, 2023.
========================================================================================
*/
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include<sys/stat.h>
#include<time.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
	
	if(argc == 1){
		perror("input error");
		return 0;
	}

	int dpid = fork();
	printf("%d\n",dpid);
	if(dpid==0){
		setsid();
		chdir("/");
		umask(0);
		int i=0;
		while(1){
			time_t now = time(NULL);
	        	struct tm *tm_struct = localtime(&now);
        		int hour = tm_struct->tm_hour;
        		int min = tm_struct->tm_min;
			int h = atoi(argv[1]);
			int m=-1;
			if(argc>2) m = atoi(argv[2]);
			if(hour == h && m!=-1 && min==m){
				printf("Hello, my friend\n");
				break;
			}
			else if(m==-1 && hour==h){
				printf("Hello, my friend\n");
				break;
			}
		}
	}
	else{
		exit(0);
	}

}