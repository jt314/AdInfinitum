#ifndef ADINF_INCLUDE_TRANSFORM_TRIANGLE
#define ADINF_INCLUDE_TRANSFORM_TRIANGLE

#define NUM_TRANSFORM_OPS 10

// This type is an enum for all the fractal operations that we can apply to our points.
typedef enum Transform_Operations {
  LINEAR_3D,
  SINUSOIDAL,
  SPHERICAL,
  SWIRL,
  HORSESHOE,
  POLAR,
  DISC,
  SPIRAL,
  HYPERBOLIC,
  SQUARE
} transform_operation_t;
  
} transform_operation_t;

// These triangles will perform the mathematical magic that generates the fractal images
typedef struct Transform_Triangle {
  float x_coord; // X coordinate of the transforming triangle
  float y_coord; // Y coordinate of the transforming triangle
  float o_coord; // origin coord of the transforming triangle
  float weight;  // weight value of the transforming triangle

  float[NUM_TRANSFORM_OPS] transform_weights; //weights of the transformations perforemed by transforming triangle

} transform_triangle_t;



#endif
