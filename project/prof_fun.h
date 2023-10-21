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

            struct courses c;
            int fd = open("data/course.txt",O_RDONLY);


            for (int i = 0; i < 5; i++) 
            {   
                if(f.course[i]=="\0")
                    break;

                if(c.status==0)
                    continue;

                send(client_socket,"\n",sizeof("\n"),0); 
                sleep(0.01);
                send(client_socket, f.course[i], sizeof(f.course[i]), 0);
                sleep(0.01);
            }               
            break; 
        }
    }
    close(fd); 
    return;
}


void add_course(int client_socket)
{
    struct faculty f;
    int fd1 = open("data/faculty.txt",O_RDWR);
    if (fd1 == -1)
    {
        perror("Error opening file");
        return;
    }

    lseek(fd1,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd1, &f, sizeof(struct faculty)) > 0)
    {
        if (strcmp(f.username, username) == 0)
        {
            int count=0;
            for (int i = 0; i < 5; i++) 
            {   
                if(!strcmp(f.course[i], "\0"))
                    {
                        break;
                    }
                count++;
            }    
            if  (count==5)
            {
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "sorry you have offered more than 5 course");
                send(client_socket, buf, strlen(buf), 0);
                break;
            }

            lseek(fd1,-1*sizeof(struct faculty),SEEK_CUR);
            //printf("op : %ld\n",);
            struct courses c;
            int fd = open("data/course.txt",O_RDWR|O_APPEND);
            
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
        
            //f.course[count].strcpy(f.course[count],c.cid);
            strcpy(f.course[count], c.cid);
            write(fd,&c,sizeof(c));
            write(fd1,&f,sizeof(f));
            // printf("coursev: %ld\n",write(fd,&c,sizeof(c)));   
            // printf("fac: %ld\n",write(fd1,&f,sizeof(f)));    
            // perror("gfbh");
            //write(fd1,&f,sizeof(f));
            return;


        }
    }
}


void course_status(int client_socket)
{
    struct courses c;
    int pass=0;
    int fd = open("data/course.txt",O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    struct faculty f;
    int fd1 = open("data/faculty.txt",O_RDONLY);

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the course status you want to change : \n");
    send(client_socket, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(buf));
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    char cid[6];
    strcpy(cid,buf);
    cid[bytes_received-1]='\0';

    while (read(fd1, &f, sizeof(struct faculty)) > 0)
    {
        if (strcmp(f.username, username) == 0)
        {
            for (int k=0;k<5;k++)
            {
                if(strcmp(cid,f.course[k])==0)
                {
                    pass=1;
                    break;
                }
            }
        }
    }

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
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &c, sizeof(struct courses)) > 0)
        {
            if (strcmp(c.cid, cid) == 0)
            {
                if(pass)
                {
                    lseek(fd,-1*sizeof(struct courses),SEEK_CUR);
                    strcpy(buf, "Enter the status of course {1. Activate (1) 2. Deactivate (0)}:\n");
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
                    write(fd,&c,sizeof(c));  
                    break;
                }
                else
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"not your subject\n");
                    send(client_socket,buf,strlen(buf),0);
                    break;
                }
            }
        }
    }
}


void update_course(int client_socket)
{
    struct courses c;
    int fd = open("data/course.txt",O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the course ID you want to change : \n");
    send(client_socket, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(buf));
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    char cid[6];
    strcpy(cid,buf);
    cid[bytes_received-1]='\0';

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
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &c, sizeof(struct courses)) > 0)
        {
            if (strcmp(c.cid, cid) == 0)
            {
                lseek(fd,-1*sizeof(struct courses),SEEK_CUR);

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


                write(fd,&c,sizeof(c)); 
                break;
            }
        }
    }
}


void change_pw(int client_socket)
{
    int fd = open("data/faculty.txt",O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    
    struct faculty f;
    lseek(fd,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd, &f, sizeof(struct faculty)) > 0)
    {
        if (strcmp(f.username, username) == 0)
        {
            lseek(fd,-1*sizeof(struct faculty),SEEK_CUR);
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Enter new password:\n");
            send(client_socket, buf, strlen(buf), 0);
            memset(buf,0,sizeof(buf));
            int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
            if(bytes_received<1)
            {
                memset(buf, 0, sizeof(buf));
                strcpy(buf,"Error\n");
                send(client_socket,buf,strlen(buf),0);
            }
            strcpy(f.password,buf);
            f.password[strlen(f.password)-1]='\0';

            write(fd,&f,sizeof(f));            
            break; 
        }
        
    }

    close(fd); 
}


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
