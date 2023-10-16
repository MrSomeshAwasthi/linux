/*
    AUTHOR : SOMESH AWASTHI
    FILE DESCRIPTION : 
*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
    1. View Offering Courses
    2. Add New Course
    3. Remove Course
    4. Update Course Details
    5. Change Password
    6. Logout and Exit
*/


char buf[1024];

void view_course(int client_socket)
{ 
    int fd = open("data/faculty.txt",O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the courseID of course you want to view: \n");
    send(client_socket, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(buf));
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);

    if (bytes_received < 1)
    {
        // Handle error if no data received from the client
        memset(buf, 0, sizeof(buf));
        strcpy(buf, "Error receiving data from client\n");
        send(client_socket, buf, strlen(buf), 0);
        exit(1);
    }
    else
    {
        struct faculty f;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &f, sizeof(struct faculty)) > 0)
        {
            if (strcmp(f.username, username) == 0)
            {
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "course :\n");
                send(client_socket, buf, strlen(buf), 0);

                for (int i = 0; i < 5; i++) 
                {   
                    if(f.course[i]=="\0")
                        break;

                    send(client_socket, f.course[i], sizeof(f.course[i]), 0);
                    sleep(0.01);
                }                
                break; 
            }

        }
    }

    close(fd); 
}


void add_course(int client_socket)
{
    struct courses c;
    int fd = open("data/course.txt",O_RDWR);
    
    // name
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "1. Enter course name:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,1024);
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(c.name,buf);
    c.name[strlen(c.name)-1]='\0';


    // course id
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "2. Enter course id:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(c.cid,buf);
    c.cid[strlen(c.cid)-1]='\0';


    // department
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "3. Enter department:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(c.dept,buf);
    c.dept[strlen(c.dept)-1]='\0';

    // course offered by
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "4. Enter instructor name:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(c.teacher,buf);
    c.teacher[strlen(c.teacher)-1]='\0';

    // total no of seats for course

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "5. Enter total seats :\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    c.seat=atoi(buf);

    // credit

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "6. Enter credit :\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    c.credit=atoi(buf);

    // avail
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "7. Enter available seat :\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    c.avail=atoi(buf);


    // course status
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "8. Enter course status :\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    c.status=atoi(buf);
 
    
    write(fd,&f,sizeof(f));    

    return;

}


void course_status(int client_socket)
{
    struct courses c;
    int fd = open("data/course.txt",O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the course status you want to change : \n");
    send(client_socket, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(buf));
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);

    if (bytes_received < 1)
    {
        // Handle error if no data received from the client
        memset(buf, 0, sizeof(buf));
        strcpy(buf, "Error receiving data from client\n");
        send(client_socket, buf, strlen(buf), 0);
        exit(1);
    }
    else
    {
        // Copy the received username to the search query
        strncpy(username_to_find, buf, sizeof(username_to_find));
        username_to_find[9]='\0';
        struct course c;
        int student_found = 0;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &s, sizeof(struct student)) > 0)
        {
            //printf("namee%sfind%s\n",s.username,username_to_find);
            if (strcmp(s.username, username_to_find) == 0)
            {
                lseek(fd,-1*sizeof(struct student),SEEK_CUR);
                c.status=0;
                send(client_socket,"done\n",strlen("done\n"),0);
                write(fd,&s,sizeof(s));  
                break;
            }
        }
    }
}


void update_course(int client_socket)
{}


void change_pw(int client_socket)
{}


void funp(int client_socket,struct sockaddr_in client_address,int choice)
{
    switch (choice)
    {
        case 1:
            view_course(client_socket);
            break;

        case 2:
            add_course(client_socket);
            break;

        case 3:
            course_status(client_socket);
            break;

        case 4:
            update_course(client_socket);
            break;

        case 5:
            change_pw(client_socket);
            break;

        default:
            break;
    }
}
