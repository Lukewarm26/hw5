/*
wyls.c
Author: Lucas Eifert
Date: 3/08/22

COSC 3750, Homework 5

This is a simple version of the ls utility.\
*/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void printFile(const char *);
void printDirectory(const char *);
int isDirectory(const char *);
int isFile(const char *);

bool nOption = false;
bool hOption = false;

int main(int argc, char **argv) {

bool locked = false;

    //if there are arguments 
    if(argc > 1) {
        //iterate through the arguments
        for(int i = 1; i < argc; i++) {
            //if argument is an option
            if(argv[i][0] == '-' && locked == false) {
                //for every char in the options
                for(int j = 1; j < strlen(argv[i]); j++) {
                    if(argv[i][j] == 'n') nOption = true;
                    else if(argv[i][j] == 'h') hOption = true;
                    else {
                        printf("Error: -%c option not supported \n", 
                        argv[i][j]);
                        return 0;
                    }
                }
                //if there are no other arguments after options 
                if(i == argc-1) {
                    char dir[4096];
                    printDirectory(getcwd(dir, sizeof(dir)));
                }
            }
            //if the argument is not an option
            else {
                locked = true;
                //if directory exists, print directory 
                if(isDirectory(argv[i]) != 0) {
                    printDirectory(argv[i]);
                }
                //if file exists, print file
                else if(isFile(argv[i]) != 0) {
                    printFile(argv[i]);
                }
                else perror(argv[i]);
            }   
        }
    }
    //if there are no arguments 
    else {
        char dir[4096];
        printDirectory(getcwd(dir, sizeof(dir)));
    }

    if(nOption == true) printf("%s \n", "nnnnnnnnnnn");
    if(hOption == true) printf("%s \n", "hhhhhhhhhhh");
    
}

//returns not 0 if path is a directory
int isDirectory(const char *path) {
   struct stat statStruct;
   if (stat(path, &statStruct) != 0)
       return 0;
   return S_ISDIR(statStruct.st_mode);
}
//returns not 0 if path is a file
int isFile(const char *path) {
   struct stat statStruct;
   if (stat(path, &statStruct) != 0)
       return 0;
   return S_ISREG(statStruct.st_mode);
}

void printDirectory(const char *path) {
    printf("printing %s \n", path);

    struct dirent *direntptr;
    DIR *dir;    

    dir = opendir(path);
    if(dir == NULL) perror(path);
    
    while ((direntptr = readdir(dir)) != NULL) {
            if(strcmp(direntptr -> d_name, ".") == 0 || 
            strcmp(direntptr -> d_name, "..") == 0) continue;
            else printFile(direntptr -> d_name);
        }

    closedir(dir);
    return;
}

void printFile(const char *path) {
    printf("printing %s \n", path);
    
    char permissions[10] = "----------";
    //char 

    struct stat statStruct;

    
    if(stat(path, &statStruct) != 0) perror(path);

    //get permisions for file 
    if(isDirectory(path) != 0) permissions[0] = 'd'; 
    if(statStruct.st_mode & S_IRUSR) permissions[1] = 'r';
    if(statStruct.st_mode & S_IWUSR) permissions[2] = 'w';
    if(statStruct.st_mode & S_IXUSR) permissions[3] = 'x';
    if(statStruct.st_mode & S_IRGRP) permissions[4] = 'r';
    if(statStruct.st_mode & S_IWGRP) permissions[5] = 'w';
    if(statStruct.st_mode & S_IXGRP) permissions[6] = 'x';
    if(statStruct.st_mode & S_IROTH) permissions[7] = 'r';
    if(statStruct.st_mode & S_IWOTH) permissions[8] = 'w';
    if(statStruct.st_mode & S_IXOTH) permissions[9] = 'x';

    printf("%d \n",statStruct.st_uid);

printf("%s \n", permissions);

    struct passwd passwdStruct;
    
    
    printf("%s \n", pw -> pw_name);
 







    return;
}


















