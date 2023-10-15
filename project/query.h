/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>



#include "authen.h"
#include "admin_fun.h"
#include "prof_fun.h"
#include "stud_fun.h"




void query(int client_socket,struct sockaddr_in client_address) 
{   
    char read_buf[1024],tmp[1024];
    int choice;

    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, "\n..............Welcome Back To Academia :: Course Registration..............\n\nPlease select your login type\n\n1. Admin\n2. Faculty\n3. Student\n4. Exit\nEnter Login Type : \n");
    send(client_socket,tmp,strlen(tmp),0);
    memset(read_buf,0,1024);
    int bytes_received = recv(client_socket, read_buf, sizeof(read_buf), 0);
    choice=atoi(&read_buf[0]);
    if (choice < 1 || choice > 4)
    { 
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "invalid input\n");
        send(client_socket,tmp,sizeof(tmp),0);
        return;
    }
    else if(choice==4)
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "invalid input\n");
        send(client_socket,"BYE\n",sizeof("BYE\n"),0);
        return;
    }


    // authentication
    if (authen(client_socket,client_address,choice))
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "Authentication successful\n");
        send(client_socket, tmp, sizeof(tmp), 0);
    } 
    
    else 
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, "Authentication failed\n");
        send(client_socket,tmp, sizeof(tmp), 0);
        return;
    }
    int pd,ch;
    switch (choice)
    {
    case 1:
        /* show menu*/
        while (1)
        {
            memset(tmp, 0, 1024);
            strcpy(tmp, ".......... Welcome to Admin Menu ..........\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n7. Modify Student Details\n8. Modify Faculty Details\n9. Logout and Exit\n");
            pd=send(client_socket,tmp,strlen(tmp),0);
            bytes_received = recv(client_socket, read_buf, sizeof(read_buf), 0);
            ch=atoi(&read_buf[0]);
            if (ch < 1 || ch > 9)
            { 
                memset(tmp, 0, sizeof(tmp));
                strcpy(tmp, "invalid input\n");
                send(client_socket,tmp,sizeof(tmp),0);
                return;
            }
            if (ch==9)
            {
                memset(tmp, 0, 1024);
                strcpy(tmp, "logout success\n");
                pd=send(client_socket,tmp,strlen(tmp),0);
                exit(1);
            }
            
            fun(client_socket,client_address,ch);
        }
            break;
        




    case 2:
        /* show menu*/
        while (1)
        {
            memset(tmp, 0, 1024);
            strcpy(tmp, ".......... Welcome to Faculty Menu ..........\n1. View Offering Courses\n2. Add New Course\n3. Remove Course\n4. Update CourseDetails\n5. Change Password\n6. Logout and Exit\n");
            pd=send(client_socket,tmp,strlen(tmp),0);
            bytes_received = recv(client_socket, read_buf, sizeof(read_buf), 0);
            ch=atoi(&read_buf[0]);
            if (ch < 1 || ch > 6)
            { 
                memset(tmp, 0, sizeof(tmp));
                strcpy(tmp, "invalid input\n");
                send(client_socket,tmp,sizeof(tmp),0);
                return;
            }
            if (ch==6)
            {
                memset(tmp, 0, 1024);
                strcpy(tmp, "logout success\n");
                pd=send(client_socket,tmp,strlen(tmp),0);
                exit(1);
            }
            
            fun(client_socket,client_address,ch);
        }
        break;





    case 3:
        /* show menu*/
        while (1)
        {
            memset(tmp, 0, 1024);
            strcpy(tmp, ".......... Welcome to Student Menu ..........\n1. View All Courses\n2. Enroll New Course\n3. Drop Course\n4. View Enrolled Course Details\n5. Change Password\n6. Logout and Exit\n");
            pd=send(client_socket,tmp,strlen(tmp),0);
            bytes_received = recv(client_socket, read_buf, sizeof(read_buf), 0);
            ch=atoi(&read_buf[0]);
            if (ch < 1 || ch > 6)
            { 
                memset(tmp, 0, sizeof(tmp));
                strcpy(tmp, "invalid input\n");
                send(client_socket,tmp,sizeof(tmp),0);
                return;
            }
            if (ch==6)
            {
                memset(tmp, 0, 1024);
                strcpy(tmp, "logout success\n");
                pd=send(client_socket,tmp,strlen(tmp),0);
                exit(1);
            }
            
            fun(client_socket,client_address,ch);
        }
        break;

    default:
        break;
    }
    return;
}