#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>

int main()
{
    DIR *dr;
    struct dirent *en;
    dr = opendir("."); //open all or present directory
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            printf("%s\n", en->d_name); //print all directory name
        }
        closedir(dr); //close all directory
    }
    return 0;
}


/*
GET THE CURRENT DIRECTORY
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int main() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}
*/