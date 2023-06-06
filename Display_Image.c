#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include "Options.h"

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 20

int main()
{
    DIR *dr;
    char header[40] = {"Choose one of the following options :-"};
    struct dirent *en;

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    dr = opendir(cwd); // open all or present directory
    if (dr) {
        char options[MAX_FILES][MAX_FILENAME_LENGTH];
        int fileCount = 0;
        
        while ((en = readdir(dr)) != NULL && fileCount < MAX_FILES) {
                strncpy(options[fileCount], en->d_name, MAX_FILENAME_LENGTH - 1);
                options[fileCount][MAX_FILENAME_LENGTH - 1] = '\0'; // Ensure null termination
                fileCount++;
        }
        closedir(dr); // close all directory
        int choice = ReturnChoice(header, options, fileCount, 1);
        // Print the filenames
        for (int i = 0; i < fileCount; i++) {
            printf("%s\n", options[i]);
        }
    }
    return 0;
}