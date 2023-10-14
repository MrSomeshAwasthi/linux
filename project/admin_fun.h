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
    char course[5][6]; 
    int status;
};
struct faculty
{
    char username[10];  
    char password[10];  
    char name[32];
    char dept[32];  
    char designation[20];
    char email[129];  
    char address[129];  
    char course[5][6]; 
    
};
char buf1[1024];

void add_student(int client_socket)
{
    struct student s;
    int fd=open("data/student.txt",O_RDWR|O_APPEND);


    // username
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter username:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,1024);
    int bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.username,buf1);
    s.username[strlen(s.username)-1]='\0';


    // password
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "2. Enter password:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.password,buf1);
    s.password[strlen(s.password)-1]='\0';


    // name
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "3. Enter name:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.name,buf1);
    s.name[strlen(s.name)-1]='\0';

    // age
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "4. Enter age:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    s.age=atoi(buf1);

    // email
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "5. Enter email id:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.email,buf1);
    s.email[strlen(s.email)-1]='\0';


    // address
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "6. Enter address:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.address,buf1);
    s.address[strlen(s.address)-1]='\0';

    // course


    memset(s.course, 0, sizeof(s.course));  // Initialize the courses array
    int num_courses = 0;  // Initialize the number of courses to 0

    while (num_courses < 5)  // You can adjust the limit as needed
    {
        // Input for each course
        memset(buf1, 0, sizeof(buf1));
        snprintf(buf1, sizeof(buf1), "Enter course %d: \n", num_courses + 1);
        send(client_socket, buf1, strlen(buf1), 0);

        memset(buf1, 0, sizeof(buf1));
        bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);

        if (bytes_received < 1)
        {
            memset(buf1, 0, sizeof(buf1));
            strcpy(buf1, "Error\n");
            send(client_socket, buf1, strlen(buf1), 0);
        }
        else
        {
            // Copy the course name to the student's courses array
            strcpy(s.course[num_courses], buf1);
            s.course[num_courses][strlen(s.course[num_courses])-1]='\0';
            num_courses++;
        }
    }
    
    // status
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "8. Enter status:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    s.status=atoi(buf1);


    write(fd,&s,sizeof(s));    

    return;
}


void view_student(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/student.txt", O_RDONLY); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf1, 0, sizeof(buf1));

    // Ask the user to enter the username of the student they want to view

    strcpy(buf1, "Enter the username of the student you want to view: \n");
    send(client_socket, buf1, strlen(buf1), 0);


    
    memset(buf1, 0, sizeof(buf1));
    int bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);

    if (bytes_received < 1)
    {
        // Handle error if no data received from the client
        perror("Error receiving data from client");
    }
    else
    {
        // Copy the received username to the search query
        strncpy(username_to_find, buf1, sizeof(username_to_find));
        username_to_find[9]='\0';
        struct student s;
        int student_found = 0;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &s, sizeof(struct student)) > 0)
        {
            send(client_socket, "1. username :\n", sizeof("1. username :\n"), 0);
            send(client_socket, s.username, sizeof(s.username), 0);

            send(client_socket, "2. password :\n", sizeof("2. password :\n"), 0);
            send(client_socket, s.password, sizeof(s.password), 0);

            send(client_socket, "3. name :\n", sizeof("3. name :\n"), 0);
            send(client_socket, s.name, sizeof(s.name), 0);

            send(client_socket, "4. age :\n", sizeof("4. age :\n"), 0);
            send(client_socket, &s.age, sizeof(s.age), 0);

            send(client_socket, "5. email :\n", sizeof("5. email :\n"), 0);
            send(client_socket, s.email, sizeof(s.email), 0);

            send(client_socket, "6. address :\n", sizeof("6. address :\n"), 0);
            send(client_socket, s.address, sizeof(s.address), 0);

            send(client_socket, "7. status :\n", sizeof("7. status :\n"), 0);
            send(client_socket, s.status, sizeof(s.status), 0)

            // Send each subject in the course array
            send(client_socket, "8. course :\n", sizeof("8. course :\n"), 0);
            for (int i = 0; i < 5; i++) 
            {
                send(client_socket, s.course[i], sizeof(s.course[i]), 0);
            }

            student_found = 1;
            break; // Student found, no need to continue searching
        }

        if (!student_found)
        {
            // Student not found, send an error message to the client
            memset(buf1, 0, sizeof(buf1));
            strcpy(buf1, "Student not found\n");
            send(client_socket, buf1, strlen(buf1), 0);
        }
    }

    close(fd); // Close the file
}


void add_faculty(int client_socket)
{
    struct faculty f;
    int fd=open("data/faculty.txt",O_RDWR|O_APPEND);


    
    // username
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "1. Enter username:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,1024);
    int bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(f.username,buf1);
    f.username[strlen(f.username)-1]='\0';


    // password
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "2. Enter password:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(f.password,buf1);
    f.password[strlen(f.password)-1]='\0';


    // name
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "3. Enter name:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(f.name,buf1);
    f.name[strlen(f.name)-1]='\0';

    // dept
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "4. Enter dept:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    s.age=atoi(buf1);

    // email
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "5. Enter email id:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.email,buf1);
    s.email[strlen(s.email)-1]='\0';


    // address
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "6. Enter address:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    strcpy(s.address,buf1);
    s.address[strlen(s.address)-1]='\0';

    // course


    memset(s.course, 0, sizeof(s.course));  // Initialize the courses array
    int num_courses = 0;  // Initialize the number of courses to 0

    while (num_courses < 5)  // You can adjust the limit as needed
    {
        // Input for each course
        memset(buf1, 0, sizeof(buf1));
        snprintf(buf1, sizeof(buf1), "Enter course %d: \n", num_courses + 1);
        send(client_socket, buf1, strlen(buf1), 0);

        memset(buf1, 0, sizeof(buf1));
        bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);

        if (bytes_received < 1)
        {
            memset(buf1, 0, sizeof(buf1));
            strcpy(buf1, "Error\n");
            send(client_socket, buf1, strlen(buf1), 0);
        }
        else
        {
            // Copy the course name to the student's courses array
            strcpy(s.course[num_courses], buf1);
            s.course[num_courses][strlen(s.course[num_courses])-1]='\0';
            num_courses++;
        }
    }
    
    // status
    memset(buf1, 0, sizeof(buf1));
    strcpy(buf1, "8. Enter status:\n");
    send(client_socket,buf1,strlen(buf1),0);
    memset(buf1,0,sizeof(buf1));
    bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);
    if(bytes_received<1)
    {
        memset(buf1, 0, sizeof(buf1));
        strcpy(buf1,"Error\n");
        send(client_socket,buf1,strlen(buf1),0);
    }
    s.status=atoi(buf1);


    write(fd,&s,sizeof(s));    

    return;
}


void view_faculty(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/student.txt", O_RDONLY); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf1, 0, sizeof(buf1));

    // Ask the user to enter the username of the student they want to view

    strcpy(buf1, "Enter the username of the student you want to view: \n");
    send(client_socket, buf1, strlen(buf1), 0);


    
    memset(buf1, 0, sizeof(buf1));
    int bytes_received = recv(client_socket, buf1, sizeof(buf1), 0);

    if (bytes_received < 1)
    {
        // Handle error if no data received from the client
        perror("Error receiving data from client");
    }
    else
    {
        // Copy the received username to the search query
        strncpy(username_to_find, buf1, sizeof(username_to_find));
        username_to_find[9]='\0';
        struct student s;
        int student_found = 0;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &s, sizeof(struct student)) > 0)
        {
            
            send(client_socket, s.username, sizeof(s.username), 0);
            send(client_socket, s.password, sizeof(s.password), 0);
            send(client_socket, s.name, sizeof(s.name), 0);
            send(client_socket, &s.age, sizeof(s.age), 0);
            send(client_socket, s.email, sizeof(s.email), 0);
            send(client_socket, s.address, sizeof(s.address), 0);

            // Send each subject in the course array
            for (int i = 0; i < 5; i++) 
            {
                send(client_socket, s.course[i], sizeof(s.course[i]), 0);
            }

            student_found = 1;
            break; // Student found, no need to continue searching
        }

        if (!student_found)
        {
            // Student not found, send an error message to the client
            memset(buf1, 0, sizeof(buf1));
            strcpy(buf1, "Student not found\n");
            send(client_socket, buf1, strlen(buf1), 0);
        }
    }

    close(fd); // Close the file
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
            add_faculty(client_socket);
            break;

        case 4:
            view_faculty(client_socket);
            break;


        default:
            break;
    }
}
