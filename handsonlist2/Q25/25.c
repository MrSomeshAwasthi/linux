/*
==================================================================================================
Name : 25.c
Author : Somesh Awasthi
Description : Write a program to print a message queue's  (use msqid_ds and ipc_perm structures)
                a. access permission   
                b. uid, gid   
                c. time of last message sent and received       
                d. time of last change in the message queue    
                e. size of the queue    
                f. number of messages in the queue     
                g. maximum number of bytes allowed     
                h. pid of the msgsnd and msgrcv 
Date: 1st oct, 2023.
==================================================================================================
*/
#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
int main()
{
    key_t key=ftok(".",'s');
    int a=msgget(key,IPC_CREAT | 0766);
    struct msqid_ds msg_q_id;
    int q_detail=msgctl(a,IPC_STAT,&msg_q_id);
    printf("a. access permission :%o\n",msg_q_id.msg_perm.mode);
    printf("b. uid :%d\n   gid :%d\n",msg_q_id.msg_perm.uid,msg_q_id.msg_perm.gid);
    printf("c. time of last message sent :%ld and received :%ld\n",msg_q_id.msg_stime,msg_q_id.msg_rtime);
    printf("e. size of the queue :%ld\n",msg_q_id.__msg_cbytes);
    printf("f. number of messages in the queue :%ld\n",msg_q_id.msg_qnum);
    printf("g. maximum number of bytes allowed :%ld\n",msg_q_id.msg_qbytes);
    printf("h. pid of the msgsnd :%d\n  \t msgrcv :%d\n",msg_q_id.msg_lspid,msg_q_id.msg_lrpid);
    return 0;
}