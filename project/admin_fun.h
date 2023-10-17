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

char buf[1024];

void add_student(int client_socket)
{
    struct student s;
    int fd=open("data/student.txt",O_RDWR|O_APPEND);


    // username
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "1. Enter username:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,1024);
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(s.username,buf);
    s.username[strlen(s.username)-1]='\0';


    // password
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "2. Enter password:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(s.password,buf);
    s.password[strlen(s.password)-1]='\0';


    // name
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "3. Enter name:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(s.name,buf);
    s.name[strlen(s.name)-1]='\0';

    // age
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "4. Enter age:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    s.age=atoi(buf);

    // email
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "5. Enter email id:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(s.email,buf);
    s.email[strlen(s.email)-1]='\0';


    // address
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "6. Enter address:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(s.address,buf);
    s.address[strlen(s.address)-1]='\0';

    // course

    // Initialize the courses array
    memset(s.course, 0, sizeof(s.course));  

    // status
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "8. Enter status:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    s.status=atoi(buf);


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


void add_faculty(int client_socket)
{
    struct faculty f;
    int fd=open("data/faculty.txt",O_RDWR|O_APPEND);


    
    // username
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "1. Enter username:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,1024);
    int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.username,buf);
    f.username[strlen(f.username)-1]='\0';


    // password
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "2. Enter password:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.password,buf);
    f.password[strlen(f.password)-1]='\0';


    // name
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "3. Enter name:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.name,buf);
    f.name[strlen(f.name)-1]='\0';

    // dept
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "4. Enter dept:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.dept,buf);
    f.dept[strlen(f.dept)-1]='\0';

    // address
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "5. Enter designation:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.designation,buf);
    f.designation[strlen(f.designation)-1]='\0';

    // email
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "5. Enter email id:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.email,buf);
    f.email[strlen(f.email)-1]='\0';


    // address
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "6. Enter address:\n");
    send(client_socket,buf,strlen(buf),0);
    memset(buf,0,sizeof(buf));
    bytes_received = recv(client_socket, buf, sizeof(buf), 0);
    if(bytes_received<1)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf,"Error\n");
        send(client_socket,buf,strlen(buf),0);
    }
    strcpy(f.address,buf);
    f.address[strlen(f.address)-1]='\0';

    // course
 
    memset(f.course, 0, sizeof(f.course));  // Initialize the courses array

    write(fd,&f,sizeof(f));    

    return;
}


void view_faculty(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/faculty.txt", O_RDONLY); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));

    // Ask the user to enter the username of the student they want to view

    strcpy(buf, "Enter the username of the faculty you want to view: \n");
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
        struct faculty f;
        int faculty_found = 0;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &f, sizeof(struct faculty)) > 0)
        {
            if (strcmp(f.username, username_to_find) == 0)
            {
                //send(client_socket, &s, sizeof(struct student), 0);
                snprintf(buf, sizeof(buf), "\n1. username : %s\n2. password : %s\n3. name : %s\n4. dept : %s\n5. email : %s\n6. address : %s\n7. designation : %s\n8. course :\n", f.username,f.password,f.name,f.dept,f.email,f.address,f.designation);
                send(client_socket, buf, strlen(buf), 0);
                // Send each subject in the course array
                for (int i = 0; i < 5; i++) 
                {
                    if(f.course[i]=="\0")
                        break;

                    send(client_socket, f.course[i], sizeof(f.course[i]), 0);
                    sleep(0.5);
                }
                faculty_found = 1;
                break; // faculty found, no need to continue searching
            }
        }

        if (!faculty_found)
        {
            // faculty not found, send an error message to the client
            memset(buf, 0, sizeof(buf));
            strcpy(buf, "faculty not found\n");
            send(client_socket, buf, strlen(buf), 0);
        }
    }

    close(fd); // Close the file
}


void activate(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/student.txt", O_RDWR); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the username of the student you want to activate: \n");
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
                lseek(fd,-1*sizeof(struct student),SEEK_CUR);
                s.status=1;
                send(client_socket,"done\n",strlen("done\n"),0);
                write(fd,&s,sizeof(s));  
                break;
            }
        }
    }
}


void deactivate(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/student.txt", O_RDWR); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the username of the student you want to activate: \n");
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
                lseek(fd,-1*sizeof(struct student),SEEK_CUR);
                s.status=0;
                send(client_socket,"done\n",strlen("done\n"),0);
                write(fd,&s,sizeof(s));  
                break;
            }
        }
    }
}


void modify_stud(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/student.txt", O_RDWR); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the username of the student you want to modify: \n");
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
                lseek(fd,-1*sizeof(struct student),SEEK_CUR);
                // name
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "3. Enter name:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(s.name,buf);
                s.name[strlen(s.name)-1]='\0';

                // age
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "4. Enter age:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                s.age=atoi(buf);

                // email
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "5. Enter email id:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(s.email,buf);
                s.email[strlen(s.email)-1]='\0';


                // address
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "6. Enter address:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(s.address,buf);
                s.address[strlen(s.address)-1]='\0';
                write(fd,&s,sizeof(s));  
                break;
            }
        }
    }
}


void modify_fac(int client_socket)
{
    char username_to_find[10];
    int fd = open("data/faculty.txt", O_RDWR); 
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Enter the username of the professor you want to modify: \n");
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
        struct faculty f;
        lseek(fd,0,SEEK_SET);
        // Read student records from the file one by one and look for a match
        while (read(fd, &f, sizeof(struct faculty)) > 0)
        {
            //printf("namee%sfind%s\n",s.username,username_to_find);
            if (strcmp(f.username, username_to_find) == 0)
            {
                lseek(fd,-1*sizeof(struct faculty),SEEK_CUR);

                // name
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "3. Enter name:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(f.name,buf);
                f.name[strlen(f.name)-1]='\0';

                // dept
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "4. Enter dept:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(f.dept,buf);
                f.dept[strlen(f.dept)-1]='\0';

                // address
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "5. Enter designation:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(f.designation,buf);
                f.designation[strlen(f.designation)-1]='\0';

                // email
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "5. Enter email id:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(f.email,buf);
                f.email[strlen(f.email)-1]='\0';


                // address
                memset(buf, 0, sizeof(buf));
                strcpy(buf, "6. Enter address:\n");
                send(client_socket,buf,strlen(buf),0);
                memset(buf,0,sizeof(buf));
                bytes_received = recv(client_socket, buf, sizeof(buf), 0);
                if(bytes_received<1)
                {
                    memset(buf, 0, sizeof(buf));
                    strcpy(buf,"Error\n");
                    send(client_socket,buf,strlen(buf),0);
                }
                strcpy(f.address,buf);
                f.address[strlen(f.address)-1]='\0';

                
                write(fd,&f,sizeof(f));  
                break;
            }
        }
    }
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

        case 5:
            activate(client_socket);
            break;

        case 6:
            deactivate(client_socket);
            break;
        
        case 7:
            modify_stud(client_socket);
            break;

        case 8:
            modify_fac(client_socket);
            break;

        default:
            break;
    }
}
