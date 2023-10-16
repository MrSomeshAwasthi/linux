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