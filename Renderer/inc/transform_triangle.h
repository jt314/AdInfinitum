#ifndef ADINF_INCLUDE_TRANSFORM_TRIANGLE
#define ADINF_INCLUDE_TRANSFORM_TRIANGLE

#include "image_plane.h"

#define NUM_TRANSFORM_OPS 6

typedef struct Transform_Point {
  float x;
  float y;
} transform_point_t;

// These triangles will perform the mathematical magic that generates the fractal images
typedef struct Transform_Triangle {
  // These are the affine coefficients of the transformation
  float a;
  float b;
  float c;
  float d;
  float e;
  float f;
  // Suspected transformation into coordinates:
  // X = (a,d)    Y = (b,e)     Z = (c,f)

  float weight;  // weight value of the transforming triangle

  float transform_weights[NUM_TRANSFORM_OPS]; //weights of the transformations perforemed by transforming triangle

} transform_triangle_t;
 
void set_affines(transform_triangle_t* A, float a, float b, float c, float d, float e, float f);

transform_point_t apply_function(transform_triangle_t triangle, float x, float y);

image_plane_t chaos_game(transform_triangle_t* list, int len, int width, int height);

#endif
