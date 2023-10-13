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
1. add student
2. view student detail
3. add faculty
4. view faculty detail
5. activate student
6. deactivate student
7. modify student detail
8. modify faculty detail
9. logout and exit
*/

// struct course
// {
//     char sub1;
//     char 
// };
struct student
{
    char username[10];  
    char password[10];  
    char name[32];
    int age;  
    char email[129];  
    char address[129];  
    // Add an array to store course subjects (assuming they are strings)
    char course[5][32];  // Assuming 5 subjects, each with a name up to 31 characters
    // struct course{sub1,sub2,sub3,sub4,sub5};
};
char buf1[1024],buf2[1024];

void add_student(int client_socket)
{
    struct student s;
    int fd=open("data/student.txt",O_RDWR);


    // username
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter username:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf2,0,1024);
    int bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.username,buf2);


    // password
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter password:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf2,0,sizeof(buf2));
    bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);
    if(bytes_received<1)
    {
        memset(buf2, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.password,buf2);


    // name
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter name:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf2,0,sizeof(buf2));
    bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);
    if(bytes_received<1)
    {
        memset(buf2, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.name,buf2);

    // age
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter age:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf2,0,sizeof(buf2));
    bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);
    if(bytes_received<1)
    {
        memset(buf2, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    s.age=atoi(buf2);

    // email
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter email id:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf2,0,sizeof(buf2));
    bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);
    if(bytes_received<1)
    {
        memset(buf2, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.email,buf2);


    // address
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter address:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf2,0,sizeof(buf2));
    bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);
    if(bytes_received<1)
    {
        memset(buf2, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.address,buf2);

    // course


    memset(s.course, 0, sizeof(s.course));  // Initialize the courses array
    int num_courses = 0;  // Initialize the number of courses to 0

    while (num_courses < 5)  // You can adjust the limit as needed
    {
        // Input for each course
        memset(buf1, 0, sizeof(buf1));
        snprintf(buf1, sizeof(buf1), "Enter course %d: \n", num_courses + 1);
        send(client_socket, buf1, strlen(buf1), 0);

        memset(buf2, 0, sizeof(buf2));
        bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);

        if (bytes_received < 1)
        {
            memset(buf2, 0, sizeof(buf1));
            strcpy(buf1, "Error\n");
            send(client_socket, buf1, strlen(buf1), 0);
        }
        else
        {
            // Copy the course name to the student's courses array
            strcpy(s.course[num_courses], buf2);
            num_courses++;
        }
    }

    write(fd,&s,sizeof(s));    


    close(fd);
}

void view_student(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/student.txt", O_RDWR);

    // Ask the user to enter the username of the student they want to view
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "Enter the username of the student you want to view: \n");
    send(client_socket, buf1, strlen(buf1), 0);

    memset(buf2, 0, sizeof(buf2));
    int bytes_received = recv(client_socket, buf2, sizeof(buf2), 0);

    if (bytes_received < 1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1, "Error\n");
        send(client_socket, buf1, strlen(buf1), 0);
    }  
    else
    {
        strcpy(username_to_find, buf2);

        struct student s;
        int read_bytes;

        // Read student records from the file one by one and look for a match
        while (read(fd, &s, sizeof(struct student)) > 0)
        {
            if (strcmp(s.username, username_to_find) == 0)
            {
                // Send student details back to the client
                send(client_socket, &s, sizeof(struct student), 0);
                break;
            }
        }

        if (read_bytes <= 0)
        {
            // Student not found, send an error message to the client
            memset(buf1, 0, sizeof(buf1));
            strcpy(buf1, "Student not found\n");
            send(client_socket, buf1, strlen(buf1), 0);
        }
    }

    close(fd);
}
void fun(int client_socket,struct sockaddr_in client_address,int choice)
{
    switch (choice)
    {
    case 1:
        add_student(client_socket);
        break;

    case 2:
        view_student(client_socket);
        break;

    case 3:
        /* show menu*/
        
        break;

    default:
        break;
    }
}