#ifndef ADINF_INCLUDE_IMAGE_PLANE
#define ADINF_INCLUDE_IMAGE_PLANE


typedef struct Image_Plane {
  int width; //The width of the image to be generated
  int height; //The height of the image to be generated

  // This is where the magic is stored.
  // The pixel (x,y) is at values[y][x]
  float** values;
} image_plane_t;


// This function will create and instantiate an Image Plane
image_plane_t create_plane(int width, int height);

// This function will de-allocate and destroy an Image Plane
// WARNING!!! THIS DOES NOT free() THE STRUCT ITSELF!!!
// THE REASON IT DOES NOT IS SO THAT SEGMENTATION FAULTS
// DO NOT HAPPEN WHEN DESTROYING PLANES ON THE STACK!!!
void destroy_plane(image_plane_t* killme);

// This function will be used by the renderer to register
// points "hit" when playing the Chaos Game.
void plot(image_plane_t* plane, float x, float y);

#endif
