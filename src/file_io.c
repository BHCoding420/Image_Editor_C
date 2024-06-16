#include "file_io.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "util.h"

int image_read(image_t *img, FILE *fin) {
    
    int width, height, max_value;  
    width = 0;
    height= 0; 
   
    
    if (fin == NULL) {
      
        return -1; // error case
    }  
    char magic[3];
    fscanf(fin, "%2s ", magic); //read magic
   
    
    if (strcmp(magic, "P3") != 0) {
       
       
        return -1; //error handle
    } 
    fscanf(fin, "%d %d ", &width, &height); //take w and h
    
    if(width < 0 || height < 0){

        return -1;

    }



    fscanf(fin, "%d ", &max_value); //read max
    
     if(max_value != 255)
    {
        return -1;
    }  
    
    pixel_t* pixels= malloc(width* height * sizeof(pixel_t)); //space to fill pixels

    if (pixels == NULL) {
       
       free(pixels);
        return -1;
    }

   
    for (int i = 0;i < width * height;i++)
    {
         
        fscanf(fin, "%d %d %d ", &pixels[i].r,&pixels[i].g,&pixels[i].b); //read pixels r,g,b and add to pixels
        if(pixels[i].r < 0 || pixels[i].r>255|| pixels[i].g < 0 || pixels[i].g>255 || pixels[i].b < 0 || pixels[i].b>255){

            return -1;
        }
         
    } 
   
     
    img->h = height; 
    img->w = width;
    img->img = pixels;
    return 0;
}

void image_write(const image_t *img, FILE *fout) {
  

    fprintf(fout, "P3 %d %d %d ", img->w, img->h,255); //write the values forst
    int counter = 0; //to distinguish when to seperate

    for (int i = 0; i < img->w * img->h; i++) {
        fprintf(fout, " %d %d %d ", img->img[i].r, img->img[i].g, img->img[i].b); //write pixls
        if (counter % img->w == 0 ) 
        {
            fprintf(fout," ");
            
        }
        counter++;




}
}

void image_free(image_t *img){
    if (img->img != NULL) {
        free(img->img);
    }
    img->w = 0;
    img->h = 0;
    img->img = NULL;
}