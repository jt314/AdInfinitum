#include <stdlib.h>

#include "../inc/image_plane.h"

image_plane_t create_plane(int width, int height) {
  image_plane_t createme;
 
  createme.width = width;
  createme.height = height;

  //Instantiate the 2-D array

  //Create the array of rows
  createme.values = (float**)malloc(sizeof(float*)*height);
 
  int i;
  for(i = 0; i < height; i++) {
    //Create the row
    createme.values[i] = (float*)malloc(sizeof(float)*width);
    
    //Zero the row
    int j;
    for(j = 0; j < width; j++) {
      createme.values[i][j] = 0;
    }
    
  }

  return createme;
}

void destroy_plane(image_plane_t* killme) {
  int i;

  //Free every row making up the histogram
  for(i = 0; i < killme->height; i++) {
    free(killme->values[i]);
  }

  //Now free the histogram
  free(killme->values);
  killme->values = NULL;

}

void plot(image_plane_t* plane, float x, float y) {

  if(x > 1.25 || x < -1.25 || y > 1.25 || y < -1.25) {
    //GET OUT, THIS IS OUTSIDE OUR RANGE!
    return;
  }

  //Now we "cast" from [-1.25, 1.25] to [0, 2.5], then scale down to [0,1]
  double x1 = (x + 1.25)/2.5; 
  double y1 = (y + 1.25)/2.5;

  int i = y1 * plane->height;
  int j = x1 * plane->width;

  //Increment into the histogram and you're done :)
  plane->values[i][j]++;

}
