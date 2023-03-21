#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct facets {
	int *vertexes;
	int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;


typedef struct data {
	int count_of_vertexes;
	int count_of_facets;
	matrix_t matrix_3d;
    polygon_t *polygons;
} data_t;


void init_data(data_t* data);
int parsline(char* filename,data_t* data);
void init_polygon(data_t* data, char *line, int index);
void destroy_data(data_t * data);
