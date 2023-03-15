#include "parser.h"



int parsline(char* filename) {

    FILE* file = fopen(filename, "r");
    fpos_t pos;
    data_t data;
    char tmp;
    char* currline;
    size_t len;
    char* buff_line;


    len = 128;
    buff_line = NULL;
    currline = NULL;
    data.count_of_facets = 0;
    data.count_of_vertexes = 0;

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
    int v = 1, f = 1;
    while (!feof(file))
    {
        tmp = getc(file);
        if ('v' == tmp ) {
            for(int j = 0; j < data.count_of_vertexes ; ++j) 
                fscanf(file, " %lf ", &data.matrix_3d.matrix[v][j]);
            ++v;
            }
        if ('f' == tmp) {
            getline(&currline, &len, file);
            buff_line = malloc(len);
            for(int i = 0; currline[i] != '\0'; ++i) buff_line[i] = currline[i]; 
            init_polygon(&data, buff_line, f, len);
            ++f;
            free(buff_line);
        }
    }
    
    free(currline);
    printf("%d %d\n", data.count_of_facets, data.count_of_vertexes);
    destroy_data(&data);

    fclose(file);
}


void init_data(data_t* data) {
    //подсчет с 1

    data->matrix_3d.rows = data->count_of_vertexes + 1;
    data->matrix_3d.cols = 3;
    data->matrix_3d.matrix = (double**) malloc(sizeof(double*) * data->matrix_3d.rows);
    data->matrix_3d.matrix[0] = malloc(sizeof(double) *  data->matrix_3d.cols * data->matrix_3d.rows);
    for(int i = 1; i < data->matrix_3d.rows; ++i)
        data->matrix_3d.matrix[i] = data->matrix_3d.matrix[0] + i * data->matrix_3d.cols;
    
    data->polygons = malloc(sizeof(polygon_t) * (data->count_of_facets + 1));
    
}


void init_polygon(data_t* data, char* line, int index ,size_t len) {

    int count = 1;
    char* buff_line = NULL;
    buff_line =  malloc(strlen(line) + 1);
    char* tmp = NULL;
    char* delim = " ";

    strcpy(buff_line, line);
    strtok(buff_line, delim); 
    for(; strtok(NULL, delim) != NULL ; ++count);
    
    data->polygons[index].numbers_of_vertexes_in_facets = count;
    data->polygons[index].vertexes = malloc(sizeof(int) * count);

    strcpy(buff_line, line);
    tmp = strtok(buff_line, delim);
    printf("f = (%d) ", index);
    for (int i = 0; i < data->polygons[index].numbers_of_vertexes_in_facets; ++i){
        data->polygons[index].vertexes[i] = atoi(tmp);
        printf("|%d| ",data->polygons[index].vertexes[i]);
        tmp = strtok(NULL, delim);
    }
    free(tmp);
    free(buff_line);
    printf("\n");
}

void destroy_data(data_t * data) {
    
    
    for(int i = 0; i <= data->count_of_facets; ++i) 
        free(data->polygons[i].vertexes);
    free(data->polygons);
    free(data->matrix_3d.matrix[0]);
    free(data->matrix_3d.matrix);    
}
