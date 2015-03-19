
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "inc/transform_triangle.h"
#include "inc/image_plane.h"

/*
int rend(Transform_Triangle& tri, int num_thread, char[3] output_format, char& output_file, int& x_bound, int& y_bound) {
	pthread_t cpu_thread[num_thread - 1];
	int ctr[num_thread - 1];
	
	printf("Starting Render\n");
	
	
	return 0;
}
*/

int main(int argc, char** argv) {

  transform_triangle_t gaskets[3];

  transform_triangle_t* A = gaskets; //loop start
  transform_triangle_t* B = gaskets+2; //loop bound

  //Code F0: x,y => x/2,y/2
  set_affines(A,0.5,0,0,0,0.5,0);
  A++; //increment
  set_affines(A,0.5,0,0.5,0,0.5,0);
  A--; //reset;
  set_affines(B,0.5,0,0,0,0.5,0.5);

  //Now to make sure the weights make sense
  for(A;A<=B; A++) {
    int i;
    A->transform_weights[0] = 1;
    for(i = 1; i < NUM_TRANSFORM_OPS; i++) {
      A->transform_weights[i] = 0;
    }
  }

  image_plane_t map = chaos_game(gaskets,3,1000,1000);

  printf("THE VALUE OF THE THING IS %f\n",map.values[1][1]);

  writePGM(&map,"TESTFILE.pgm");
  
  destroy_plane(&map);

  return 0;
}
