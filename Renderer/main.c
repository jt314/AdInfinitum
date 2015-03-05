#include "inc/transform_triangle.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int rend(Transform_Triangle& tri, int num_thread, char[3] output_format, char& output_file, int& x_bound, int& y_bound) {
	pthread_t cpu_thread[num_thread - 1];
	int ctr[num_thread - 1];
	
	printf("Starting Render\n");
	
	
	return 0;
}

