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

// #ifndef auth
// #define auth

// // Define the struct
// struct globalauth {
//     char username[10];  
//     char password[10];  
// };

// // extern struct globalauth g;

// #endif // 