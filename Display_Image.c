#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include "Options.h"

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 20

int main() {
    DIR *dr;
    char header[40] = {"Choose one of the following options :-"};
    struct dirent *en;
    char cwd[PATH_MAX];

    label: 
    // getcwd(cwd, sizeof(cwd));
    dr = opendir(".");
    if (dr) {
        char options[MAX_FILES][MAX_FILENAME_LENGTH];
        int fileCount = 0;
        int skipFirstFile = 1; // Set this to 0 if you want to read the first file
        
        while ((en = readdir(dr)) != NULL && fileCount < MAX_FILES) {
            if (skipFirstFile) {
                skipFirstFile = 0;
                continue; // Skip the first file
            }
            strncpy(options[fileCount], en->d_name, MAX_FILENAME_LENGTH - 1);
            options[fileCount][MAX_FILENAME_LENGTH - 1] = '\0';
            fileCount++;
        }
        
        int choice = ReturnChoice(header, options, fileCount, 1) - 1;
        // Perform further processing with the chosen option

        if (strcmp(options[choice], "..") == 0) {
        chdir("..");
        goto label;
        printf("Removing the last folder\n");
        }
        else if (strchr(options[choice], '.') != NULL) {
            // Print it's a file extension
            // Implement the logic to handle file extensions
            printf("It's a file extension\n");
        }
        else {
            char directory[40] = "./";
            // printf("%s", strcat(directory, options[choice]));
            // exit(0);
            strcat(directory, options[choice]);
            chdir(directory);
            goto label;
            printf("It's a folder\n");
        }
    }
    return 0;
}


// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #include <stdlib.h>

// int main() {
//     int width, height, channels;
//     const char* filePath = "D:/Valerian/Coding/C/Personal Projects/Terminal Image Viewer/image.jpg";
//     unsigned char* image_data = stbi_load(filePath, &width, &height, &channels, STBI_rgb);
//     system("cls");

//     if (image_data == NULL) {
//         printf("Unable to load the image\n");
//         return -1;
//     }

//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++) {
//             int index = i * width + j;
//             int pixel_index = index * channels;
//             int red = image_data[pixel_index];
//             int green = image_data[pixel_index + 1];
//             int blue = image_data[pixel_index + 2];
//             printf("\033[48;2;%d;%d;%dm  \033[0m", red, green, blue);
//         }
//         printf("\n");
//     }
//     stbi_image_free(image_data);

//     return 0;
// }
