#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdlib.h>

int main() {
    int width, height, channels;
    unsigned char* image_data = stbi_load("image.jpg", &width, &height, &channels, STBI_rgb);
    system("cls");

    if (image_data == NULL) {
        printf("Unable to load the image\n");
        return -1;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            int pixel_index = index * channels;
            int red = image_data[pixel_index];
            int green = image_data[pixel_index + 1];
            int blue = image_data[pixel_index + 2];
            printf("\033[48;2;%d;%d;%dm  \033[0m", red, green, blue);
        }
        printf("\n");
    }
    stbi_image_free(image_data);

    return 0;
}
