#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    int width, height, channels;
    unsigned char* image_data = stbi_load("image.jpg", &width, &height, &channels, STBI_rgb);

    if (image_data == NULL) {
        printf("Unable to load the image\n");
        return -1;
    }

    // Iterate over each pixel of the image
    for (int i = 0; i < width * height; ++i) {
        int pixel_index = i * channels;
        int red = image_data[pixel_index];
        int green = image_data[pixel_index + 1];
        int blue = image_data[pixel_index + 2];
        
        // Print the RGB values
        printf("Pixel %d: R=%d, G=%d, B=%d\n", i, red, green, blue);
    }

    stbi_image_free(image_data);
    return 0;
}
