#include <math.h>
#include <stdlib.h>



#include "../inc/transform_triangle.h"

#define NUM_ITERATIONS 9000000

unsigned int rand_interval(unsigned int min, unsigned int max)
{
  static int seeded = 0;
  if(!seeded) {
    srand(time(NULL));
    seeded = 1;
  }

  int r;
  const unsigned int range = 1 + max - min;
  const unsigned int buckets = RAND_MAX / range;
  const unsigned int limit = buckets * range;

  /* Create equal size buckets all in a row, then fire randomly towards
   * the buckets until you land in one of them. All buckets are equally
   * likely. If you land off the end of the line of buckets, try again. */
    do
      {
        r = rand();
      } while (r >= limit);

    return min + (r / buckets);
}

double rand01()
{
  static int seeded = 0;
  if(!seeded) {
    srand48(time(NULL));
    seeded = 1;
  }

  return drand48()*2-1;

}


void set_affines(transform_triangle_t* A, float a, float b, float c, float d, float e, float f) {
  A->a = a;
  A->b = b;
  A->c = c;
  A->d = d;
  A->e = e;
  A->f = f;

}

transform_point_t apply_variation(float x, float y, int z, float w) {
  float X, Y;

  float r = sqrt(x*x + y*y);
  float THETA = atan2(x,y);
  float PHI = atan2(y,x);

  //printf("BEGIN CALC: x=%f, y=%f\n",x,y);


  switch(z) {
  case 0: //LINEAR
    X = x;
    Y = y;
    break;
  case 1: //SINUSOIDAL
    X = sin(x);
    Y = sin(y);
    break;
  case 2: //SPHERICAL
    X = x/(r*r);
    Y = y/(r*r);
    break;
  case 3: //SWIRL
    X = x*sin(r*r)-y*cos(r*r);
    Y = x*sin(r*r)+y*cos(r*r);
    break;
  case 4: //HORSESHOE
    X = (x+y)*(x-y)/r;
    Y = 2*x*y/r;
    break;
  case 5: //POLAR
    X = THETA/M_PI;
    Y = r-1;
    break;
  default: //ZERO
    x = 0;
    y = 0;
  }

  if(w*X != w*X) X = 0; //if NaN
  if(w*Y != w*Y) Y = 0; //if NaN

  transform_point_t returnme;
  returnme.x = w*X;
  returnme.y = w*Y;

  //printf("FINIS CALC: X=%f, Y=%f\n",X,Y);
  //printf("FINAL CALC: wX=%f, wY=%f\n",returnme.x,returnme.y);

  return returnme;


}

transform_point_t apply_function(transform_triangle_t triangle, float x, float y) {

  transform_point_t returnme;
  returnme.x = 0;
  returnme.y = 0;
 
  float r = sqrt(x*x + y*y);

  int i;
  for(i = 0; i < NUM_TRANSFORM_OPS; i++) {
    transform_point_t addme = apply_variation(triangle.a*x + triangle.b*y + triangle.c, triangle.d*x + triangle.e*y + triangle.f,i,triangle.transform_weights[i]);
    
    returnme.x += addme.x;
    returnme.y += addme.y;

  }
  
  return returnme;


}


image_plane_t chaos_game(transform_triangle_t* list, int len, int width, int height) {
  image_plane_t returnme = create_plane(width,height);

  float x = rand01();
  float y = rand01();
  int z; //loop counter

  for(z = 0; z< NUM_ITERATIONS; z++) {
    //printf("WE ARE AT %d!!\n",z);
    int i = rand_interval(0,len-1);
    //printf("WE ARE AT %d!! AND THE RANDOM NUMBER IS %d!!\n",z,i);
    transform_point_t thepoint = apply_function(list[i],x,y);
    x = thepoint.x;
    y = thepoint.y;

    //printf("Segfault here?? x=%f, y=%f\n",x,y);

    if(z > 20) {
      plot(&returnme,x,y);
    }
   
    //printf("or here???\n");

  }

  return returnme;
}

