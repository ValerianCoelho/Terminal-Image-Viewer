#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include "options.h"
#include <conio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 40

int main() {
    DIR *dr; // Directory pointer
    char header[40] = {"Select an Image :-"}; // Header message
    struct dirent *en; // Directory entry pointer
    
    dr = opendir("."); // Open current directory
    chdir("./Images"); // Change current directory

    label:
        dr = opendir("."); // After changing the directory, this line reopens the current directory. It refreshes the directory stream to reflect the updated directory context.
    if (dr) {
        char options[MAX_FILES][MAX_FILENAME_LENGTH]; // Array to store file names
        int fileCount = 0; // Counter for file names
        int skipFirstFile = 1; // Flag to skip the first file
    
        // Read directory entries and store file names
        while ((en = readdir(dr)) != NULL && fileCount < MAX_FILES) {
            if (skipFirstFile) {
                skipFirstFile = 0;
                continue;
            }
            strncpy(options[fileCount], en->d_name, MAX_FILENAME_LENGTH - 1);
            options[fileCount][MAX_FILENAME_LENGTH - 1] = '\0';
            fileCount++;
        }
    
        int choice = ReturnChoice(header, options, fileCount, 1) - 1; // Get user's choice
    
        if (strcmp(options[choice], "..") == 0) {
            chdir(".."); // Move up to parent directory
            goto label; // Jump to the label to continue the loop
        } else if (strchr(options[choice], '.') != NULL) {
            char directory[MAX_FILENAME_LENGTH] = "./"; // Directory path for selected file
            strcat(directory, options[choice]);
    
            int width, height, channels;
            const char *filePath = directory;
            unsigned char *image_data = stbi_load(filePath, &width, &height, &channels, STBI_rgb); // Load image data
    
            system("cls"); // Clear the console
    
            if (image_data == NULL) {
                printf("Unable to load the image\n"); // Error handling if image loading fails
            } else {
                // Print the image pixels
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        int index = i * width + j;
                        int pixel_index = index * channels;
                        int red = image_data[pixel_index];
                        int green = image_data[pixel_index + 1];
                        int blue = image_data[pixel_index + 2];
                        printf("\033[48;2;%d;%d;%dm  \033[0m", red, green, blue); // Print colored pixel
                    }
                    printf("\n"); // Move to the next line after printing a row
                }
                stbi_image_free(image_data); // Free the loaded image data
            }
    
            getch(); // Wait for a key press
            goto label; // Jump to the label to continue the loop
        } else {
            char directory[MAX_FILENAME_LENGTH] = "./"; // Directory path for selected folder
            strcat(directory, options[choice]);
            chdir(directory); // Change directory to the selected folder
            goto label; // Jump to the label to continue the loop
        }
    }
    return 0;
}
