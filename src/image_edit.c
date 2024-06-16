#include "image_edit.h"

#include <stdlib.h>

#include "util.h"

void rotate_counterclockwise(image_t *img) { 
    int temp = img->w;
    img->w = img->h;
    img->h = temp; // width and heignht arw now swapped (tsha2labo)
    pixel_t *new_img = malloc(img->h * img->w * sizeof(pixel_t)); 
    if(new_img == NULL)
    {
        return; //alloc error
    }
    for (int row = 0; row < img->h; row++) {
        for (int col = 0; col < img->w; col++) {
            int transform =  row + img->h  * (img->w - col - 1); //new pos
            new_img[transform].b = img->img[row * img->w + col].b;
            new_img[transform].r = img->img[row * img->w + col].r;
            new_img[transform].g = img->img[row * img->w + col].g;
            
        }
}
    free(img->img);
    img->img= new_img ;
    




}

void rotate_clockwise(image_t *img) {
  
   int temp = img->w;
    img->w = img->h;
    img->h = temp; // width and heignht arw now swapped (tsha2labo)
   pixel_t *new_img  = malloc(img->h * img->w * sizeof(pixel_t)); 
   if(new_img == NULL)
    {
        return;//alloc error
    }
    for (int row = 0; row < img->h; row++) {
        for (int col = 0; col < img->w; col++) {
            int transform =  (img->h - row - 1) + (img->h * col);
            new_img[transform].r = img->img[row * img->w + col].r;
            new_img[transform].g = img->img[row * img->w + col].g;
            new_img[transform].b = img->img[row * img->w + col].b;
        }
    }
    free(img->img);
    img->img= new_img;
   
    


    }

void mirror_horizontal(image_t *img) {
    int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t));
    if (!temp) {
        // handle allocation failure
        return;
    }

    int lptr = 0; // start pointer
    int rptr = w - 1; // end pointer

    while (lptr < rptr) {
        int i = lptr;
        int j = rptr;
        int counter = 0; // do it until

        while (counter < h) {
            *temp = img->img[j];
            img->img[j] = img->img[i];
            img->img[i] = *temp;
            i = i + w;
            j = j + w;
            counter++;
        }

        lptr += 1;
        rptr -= 1;
    }

    free(temp);
}


void mirror_vertical(image_t *img) {
    int w = img->w;
    int h = img->h;
    pixel_t *temp = malloc(sizeof(pixel_t));
    if (!temp) {
        // handle allocation failure
        return;
    }

    int uptr = 0; // start pointer
    int dptr = w * (h - 1); // end pointer

    while (uptr < dptr) {
        int i = uptr;
        int j = dptr;
        int counter = 0;

        while (counter < w) {
            *temp = img->img[j];
            img->img[j] = img->img[i];
            img->img[i] = *temp;
            i = i + 1;
            j = j + 1;
            counter++;
        }

        uptr += w;
        dptr -= w;
    }

    free(temp);
}



void resize(image_t *img, int new_width, int new_height) {
 
  
    int w = img->w;
    int h = img->h;

    
 if (new_width == w && new_height == h) {
    
    return;
 }
    
     if (new_width >= w && new_height < h) {
        pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
        if (!new_img) {
          free(new_img); 
            return;
        }


      
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < w; j++) {
                new_img[i * new_width + j] = img->img[i * w + j];
            }
        } 

        free(img->img);
        img->img = new_img;
        img->w = new_width;
        img->h = new_height;
        return;
    } 

     if (new_width < w && new_height < h) {
         pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
        if (!new_img) {
            
           free(new_img);
            return;
        }

        
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                new_img[i * new_width + j] = img->img[i * w + j];
            }
        }

        free(img->img);
        img->img = new_img;
        img->w = new_width;
        img->h = new_height;
        return;
    }
    
    if (new_width >= w && new_height >= h) {
        pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
        if (!new_img) {
            
           free(new_img);
            return;
        }

        
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                new_img[i * new_width + j] = img->img[i * w + j];
            }
        }

        free(img->img);
        img->img = new_img;
        img->w = new_width;
        img->h = new_height;
        return;
    }

    
   

     
   

 
 if (new_width < w && new_height >= h) {
    pixel_t *new_img = calloc(new_width * new_height, sizeof(pixel_t));
    if (!new_img) {
       
       free(new_img);
        return;
    }

   
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < new_width; j++) {
            new_img[i * new_width + j] = img->img[i * w + j];
        }
    }
  

    free(img->img);
    img->img = new_img;
    img->w = new_width;
    img->h = new_height;
    return;
  } 
  

}
