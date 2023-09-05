/*
20. Find out the priority of your running program. Modify the priority with nice command.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/resource.h>
int main()
{
    int prio=getpriority(PRIO_PROCESS,0);
    printf("current priority: %d\n",prio);
    int nic=nice(-4);
    printf("modifed priority: %d\n",getpriority(PRIO_PROCESS,0));
    return 0;
}