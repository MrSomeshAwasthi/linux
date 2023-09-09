/*
====================================================================================
Name : 29.c
Author : Somesh Awasthi
Description :Write a program to get scheduling policy and modify the scheduling 
policy (SCHED_FIFO, SCHED_RR).
Date: 28th Aug, 2023.
====================================================================================
*/
#include<sched.h>
#include<stdio.h>
#include<unistd.h>
void getPolicy(int policy)
{

        switch(policy)
        {
                case SCHED_FIFO:
                {
                        printf("FIFO\n");
                        break;
                }
                case SCHED_RR:
                {
                        printf("Round Robin\n");
                        break;
                }
                case SCHED_OTHER:
                {
                        printf("Other\n");
                        break;
                }
                default:
                {
                        printf("Unknown\n");
                        break;
                }          
        }
        return;
}

int main()
{
	struct sched_param sc;
	int pid = getpid();
	int get_policy = sched_getscheduler(pid);
	printf("current scheduling policy: ");
        getPolicy(get_policy);
	sc.sched_priority = 99;
	get_policy = SCHED_RR;	
	printf("new scheduling policy:");
        getPolicy(get_policy);
	return 0;
}