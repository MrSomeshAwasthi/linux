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

struct courses
{
    char name[32];
    char cid[6];
    char dept[32];
    char teacher[32];
    int seat;
    int credit;
    int avail;
    int status;
};

void view_course(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/course.txt", O_RDONLY); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the username of the student you want to view: \n");
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
        struct student s;
        int student_found = 0;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &s, sizeof(struct student)) > 0)
        {
            //printf("namee%sfind%s\n",s.username,username_to_find);
            if (strcmp(s.username, username_to_find) == 0)
            {
                // printf("%d:%d:%s:%s:%s:%s:%s\n",s.age,s.status,s.username,s.password,s.name,s.email,s.address);
                //send(client_socket, &s, sizeof(struct student), 0);
                snprintf(buf, sizeof(buf), "\n1. username : %s\n2. password : %s\n3. name : %s\n4. age : %d\n5. email : %s\n6. address : %s\n7. status : %d\n8. course :\n", s.username,s.password,s.name,s.age,s.email,s.address,s.status);
                send(client_socket, buf, strlen(buf), 0);
                //send(client_socket, "\n8. course :\n", sizeof("8. course :\n"), 0);
                for (int i = 0; i < 5; i++) 
                {   
                    if(s.course[i]=="\0")
                        break;

                    send(client_socket, s.course[i], sizeof(s.course[i]), 0);
                    sleep(0.5);
                }
                student_found = 1;
                break; // Student found, no need to continue searching
            }

        }

        if (!student_found)
        {
            // Student not found, send an error message to the client
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "Student not found\n");
            send(client_socket, buf, strlen(buf), 0);
        }
    }

    close(fd); // Close the file
}


void add_course(int client_socket)
{}


void remove_course(int client_socket)
{}


void update_course(int client_socket)
{}


void change_pw(int client_socket)
{}


void funp(int client_socket,struct sockaddr_in client_address,int choice)
{
    switch (choice)
    {
        case 1:
            //struct globalauth g;
            printf("uname: %s    and  pw :  %s\n",username,password);
            //view_course(client_socket);
            break;

        case 2:
            add_course(client_socket);
            break;

        case 3:
            remove_course(client_socket);
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
