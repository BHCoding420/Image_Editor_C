#include "flood_fill.h"

#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

int pixels_check(pixel_t* p1,pixel_t* p2)
{
    if (p1->r == p2->r && p1->g == p2->g && p1->b == p2->b )
    {
        return 1;
    }
    return 0;
}

void flood(image_t *img, int x, int y, pixel_t *target_color) {
    // Check if the image pointer is NULL or if the target color pointer is NULL
    if (img == NULL || target_color == NULL) {
        return;
    }

    // Check conditions
    if (x < 0 || y < 0 || x >= img->w || y >= img->h || target_color->r < 0 || target_color->r > 255 || target_color->g < 0 || target_color->g > 255 || target_color->b < 0 || target_color->b > 255) {
        return;
    } 

    

    // Get the color of the pixel at (x, y)
    pixel_t current_color = img->img[y * img->w + x];

    // Check if the current pixel has the same color as the target color
    if (pixels_check(&current_color, target_color)) {
        // The current pixel already has the target color, no need to fill
        return;
    }

    // Change the color of the current pixel to the target color
    img->img[y * img->w + x] = *target_color;
    // Recursively flood fill the neighboring pixels
     // Right
    if (x < img->w - 1 && pixels_check(&current_color, &(img->img[y * img->w + x + 1]))) {
        flood(img, x + 1, y, target_color);
    }
    // Down
    if (y < img->h - 1 && pixels_check(&current_color, &(img->img[(y + 1) * img->w + x]))) {
        flood(img, x, y + 1, target_color);
    }
    
    // up
    if (y > 0 && pixels_check(&current_color, &(img->img[(y - 1) * img->w + x]))) {
        flood(img, x, y - 1, target_color);
    }

    

   

    // left
    if (x > 0 && pixels_check(&current_color, &(img->img[y * img->w + x - 1]))) {
        flood(img, x - 1, y, target_color);
    }
}

