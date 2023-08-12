//this code is for creating an infinite background loop

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	pid_t pid=fork();//pid_t is a data type use for used to store pid in it.
	if (pid<0)
	{
		perror("fork failed.\n");
		return 1;
	}
	if (pid==0)
	{	//child process will run for inf
		while(1)
		{

		}
	}
	else
	{
		system("ls -d /proc/[0-9]*");
		return 0;
	}
	return 0;
}
