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
void init_polygon(data_t* data, char *line, size_t len, int );

int main(){
    parsline("test.obj");
    return 0;
}




int parsline(char* filename) {

    FILE* file = fopen(filename, "r");
    fpos_t pos;
    data_t data;
    char tmp;
    char *currline = NULL;
    size_t len;


    data.count_of_facets = 1;
    data.count_of_vertexes = 1;
    fgetpos(file, &pos);
    

    
    while(!feof(file)) {
        tmp = getc(file);
        if ('v' == tmp)
            data.count_of_vertexes += 1;
        if ('f' == tmp) 
            data.count_of_facets += 1;
    }
    printf("%d %d\n", data.count_of_facets, data.count_of_vertexes);
    fsetpos(file, &pos);

    init_data(&data);
    int v = 1, f =1;
    while (!feof(file))
    {
        tmp = getc(file);
        if ('v' == tmp ) {
            for(int j = 1; j < data.count_of_vertexes ; ++j) {
                fscanf(file, " %lf ", &data.matrix_3d.matrix[v][j]);
                printf("%lf ",  data.matrix_3d.matrix[v][j]);
            }
            ++v;
            }
        if ('f' == tmp) {
            getline(&currline, &len, file);
            init_polygon(&data, currline, len, f);
            ++f;
        }
  
    }
    
    fclose(file);
    printf("%d %d\n", data.count_of_facets, data.count_of_vertexes);
}


void init_data(data_t* data) {
    //подсчет с 1

    data->matrix_3d.rows = data->count_of_vertexes;
    data->matrix_3d.cols = 3;
    data->matrix_3d.matrix = (double**) malloc(sizeof(double*) * data->matrix_3d.rows
                                             + sizeof(double) * data->matrix_3d.rows * data->matrix_3d.cols);
    for(int i = 1; i < data->matrix_3d.rows; ++i)
        data->matrix_3d.matrix[i] = (double*) data->matrix_3d.matrix + i*(sizeof(double*)) ;
    
    data->polygons = malloc(sizeof(polygon_t*) * data->count_of_facets);
}


void init_polygon(data_t* data, char *line, size_t len, int index) {

    char* currline = NULL;
    int count = 1;
    char* buff_line = malloc(len);
    char* tmp;
    strcpy(buff_line, line);
    strtok(buff_line, " "); 
    for(; strtok(NULL, " ") != NULL ; ++count);
    data->polygons[index].numbers_of_vertexes_in_facets = count;
    data->polygons[index].vertexes = malloc(sizeof(int) * data->polygons[index].numbers_of_vertexes_in_facets);
    strcpy(buff_line, line);
    tmp = strtok(buff_line, " ");
    //for(; (tmp = strtok(NULL, " ")) != NULL ; data->polygons[index]. = atof(tmp));
    for (int i = 0; i < data->polygons[index].numbers_of_vertexes_in_facets; ++i){
        data->polygons[index].vertexes[i] = atoi(tmp);
        strtok(NULL, " ");
    }

}