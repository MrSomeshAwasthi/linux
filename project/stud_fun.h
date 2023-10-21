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
    1. View All Courses
    2. Enroll New Course
    3. Drop Course
    4. View Enrolled Course Details
    5. Change Password
    6. Logout and Exit
 */




char buf[1024];

void view_all_course(int client_socket)
{ 
    int fd = open("data/course.txt",O_RDWR);
    if(fd == -1)
    {
        perror("error opening file");
        return;
    }
    struct courses c;
    lseek(fd,0,SEEK_SET);
    while (read(fd,&c,sizeof(struct courses)))
    {

        snprintf(buf, sizeof(buf),
                 "Course Name: %s\nCourse ID: %s\nDepartment: %s\nInstructor: %s\nTotal Seats: %d\nCredit: %d\nAvailable Seats: %d\nStatus: %d\n",
                 c.name, c.cid, c.dept, c.teacher, c.seat, c.credit, c.avail, c.status);

        send(client_socket, buf, strlen(buf), 0);
        sleep(0.01);    
    }
    
    return;
}


void enroll_course(int client_socket)
{
    int fd1 = open("data/student.txt",O_RDWR);
    if (fd1 == -1)
    {
        perror("Error opening file");
        return;
    }

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the Course ID you want to enroll: \n");
    send(client_socket, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(buf));
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    char check[6];
    strcpy(check,buf);
    check[bytes_received-1]='\0';
    struct student s;
    lseek(fd1,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd1, &s, sizeof(struct student)) > 0)
    {
        if (strcmp(s.username, username) == 0)
        {
            int count=0;
            for (int i = 0; i < 5; i++) 
            {   
                if(!strcmp(s.course[i], "\0"))
                {
                    break;
                }
                if(!strcmp(s.course[i], check))
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf, "you have already enrolled to this course: \n");
                    send(client_socket, buf, strlen(buf), 0);
                    break;
                }
                count++;
                send(client_socket, s.course[i], sizeof(s.course[i]), 0);
                sleep(0.01);
            }    
            if  (count==5)
            {
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "sorry you have offered more than 5 course\n");
                send(client_socket, buf, strlen(buf), 0);
                break;
            }
            lseek(fd1,-1*sizeof(struct student),SEEK_CUR);
            struct courses c;
            int fd = open("data/course.txt",O_RDWR);
            while (read(fd, &c, sizeof(struct courses)) > 0)
            {
                if (strcmp(c.cid, check) == 0)
                {
                    if(c.avail==0)
                    {
                        memset(buf, 0, sizeof(buf));
                        strcpy(buf, "course seat is filled\n");
                        send(client_socket, buf, strlen(buf), 0);
                        break;
                    }
                    if(c.status)
                    {
                        c.avail--;
                        strcpy(s.course[count],c.cid);
                        break;
                    }
                    else
                    {
                        memset(buf, 0, sizeof(buf));
                        strcpy(buf, "course maybe inactive\n");
                        send(client_socket, buf, strlen(buf), 0);
                        break;
                    }
                }
            }
            lseek(fd,-1*sizeof(struct courses),SEEK_CUR);
            write_lock(fd,-1,sizeof(c));
            write(fd,&c,sizeof(c));
            unlock_file(fd,-1,sizeof(c));
            write_lock(fd1,-1,sizeof(s));
            write(fd1,&s,sizeof(s));
            unlock_file(fd1,-1,sizeof(s));
            return;
        }
    }       
}


void drop_course(int client_socket)
{
    int fd1 = open("data/student.txt",O_RDWR);
    if (fd1 == -1)
    {
        perror("Error opening file");
        return;
    }

    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the Course ID you want to drop: \n");
    send(client_socket, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(buf));
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    char check[6];
    strcpy(check,buf);
    check[bytes_received-1]='\0';
    struct student s;
    lseek(fd1,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd1, &s, sizeof(struct student)) > 0)
    {
        if (strcmp(s.username, username) == 0)
        {
            int count=0;
            for (int i = 0; i < 5; i++) 
            {   
                if(!strcmp(s.course[i], "\0"))
                {
                    break;
                }
                if(!strcmp(s.course[i], check))
                {
                    lseek(fd1,-1*sizeof(struct student),SEEK_CUR);
                    strcpy(s.course[count],"\0");
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf, "course: \n");
                    send(client_socket, buf, strlen(buf), 0);
                    break;
                }
                count++;
            }    
            if  (count==5)
            {
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "sorry you have offered more than 5 course\n");
                send(client_socket, buf, strlen(buf), 0);
                break;
            }
            
            struct courses c;
            int fd = open("data/course.txt",O_RDWR);
            while (read(fd, &c, sizeof(struct courses)) > 0)
            {
                if (strcmp(c.cid, check) == 0)
                {
                    c.avail++;
                    break;
                }
            }
            lseek(fd,-1*sizeof(struct courses),SEEK_CUR);
            write_lock(fd,-1,sizeof(c));
            write(fd,&c,sizeof(c));
            unlock_file(fd,-1,sizeof(c));
            write_lock(fd1,-1,sizeof(s));
            write(fd1,&s,sizeof(s));
            unlock_file(fd1,-1,sizeof(s));
            return;
        }
    }       
}


void view_ecourse(int client_socket)
{
    int fd = open("data/student.txt",O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    struct student s;
    lseek(fd,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd, &s, sizeof(struct student)) > 0)
    {
        if (strcmp(s.username, username) == 0)
        {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "course :\n");
            send(client_socket, buf, strlen(buf), 0);

            for (int i = 0; i < 5; i++) 
            {   
                if(s.course[i]=="\0")
                    break;

                send(client_socket, s.course[i], sizeof(s.course[i]), 0);
                send(client_socket," \n",sizeof(" \n"),0); 
                sleep(0.01);
            }               
            break; 
        }
    }
    close(fd); 
    return;
}


void change_spw(int client_socket)
{
    int fd = open("data/student.txt",O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    
    struct student s;
    lseek(fd,0,SEEK_SET);
    // Read student records from the file one by one and look for a match
    while (read(fd, &s, sizeof(struct student)) > 0)
    {
        if (strcmp(s.username, username) == 0)
        {
            lseek(fd,-1*sizeof(struct student),SEEK_CUR);
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
            strcpy(s.password,buf);
            s.password[strlen(s.password)-1]='\0';

            write_lock(fd,-1,sizeof(s));
            write(fd,&s,sizeof(s));     
            unlock_file(fd,-1,sizeof(s));       
            break; 
        }
        
    }

    close(fd); 
}


void funs(int client_socket,struct sockaddr_in client_address,int choice)
{
    switch (choice)
    {
        case 1:
            view_all_course(client_socket);
            break;

        case 2:
            enroll_course(client_socket);
            break;

        case 3:
            drop_course(client_socket);
            break;

        case 4:
            view_ecourse(client_socket);
            break;

        case 5:
            change_spw(client_socket);
            break;

        default:
            break;
    }
}
